#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "joystick.h"

static int joystick_fd = -1;
static int joystick_fd_ff = -1;
static wwvi_js_event js_state;
static struct ff_effect feedback;
static struct input_event play;

int open_joystick()
{
  joystick_fd = open(JOYSTICK_DEVNAME, O_RDONLY | O_NONBLOCK); /* read write for force feedback? */
  if (joystick_fd < 0)
    return joystick_fd;

  /* maybe ioctls to interrogate features here? */

	joystick_fd_ff = open(JOYSTICK_DEVNAME_FF, O_RDWR);
  //set sine effect
	feedback.type = FF_PERIODIC;
	feedback.id = -1;
	feedback.u.periodic.waveform = FF_SINE;
	feedback.u.periodic.period = 0.1*0x100;	/* 0.1 second */
	feedback.u.periodic.magnitude = 0x4000;	/* 0.5 * Maximum magnitude */
	feedback.u.periodic.offset = 0;
	feedback.u.periodic.phase = 0;
	feedback.direction = 0x4000;	/* Along X axis */
	feedback.u.periodic.envelope.attack_length = 0x100;
	feedback.u.periodic.envelope.attack_level = 0;
	feedback.u.periodic.envelope.fade_length = 0x100;
	feedback.u.periodic.envelope.fade_level = 0;
	feedback.trigger.button = 0;
	feedback.trigger.interval = 0;
	feedback.replay.length = 1000;  /* 1 seconds */
	feedback.replay.delay = 0;


  return joystick_fd;
}

int rumble()
{
	if (ioctl(joystick_fd_ff, EVIOCSFF, &feedback) == -1) {
		perror("Upload effects[0]");
	}
  play.type = EV_FF;
  play.code = feedback.id;
  play.value = 1;
  if (write(joystick_fd_ff,(const void*) &play,sizeof(play)) == -1)
  {
    perror("Error in FF");
    exit(42);
  }
  return 0;
}
int read_joystick_event(js_event *jse)
{
  int bytes;

  bytes = read(joystick_fd, jse, sizeof(*jse)); 

  if (bytes == -1)
    return 0;

  if (bytes == sizeof(*jse))
    return 1;

  printf("Unexpected bytes from joystick:%d\n", bytes);

  return -1;
}
void close_joystick()
{
  close(joystick_fd_ff);
  close(joystick_fd);
}


int get_joystick_status(wwvi_js_event *my_js_out)
{
  int rc;
  js_event jse;
  if (joystick_fd < 0)
    return -1;
  //for(int i =0;i< 32;i++)
  {
    //js_state.button[i]=0;
    //need to clear buttons state
  }
  // memset(wjse, 0, sizeof(*wjse));
  while ((rc = read_joystick_event(&jse) == 1)) 
  {
    jse.type &= ~JS_EVENT_INIT; /* ignore synthetic events */
    if (jse.type == JS_EVENT_AXIS) 
    {
      switch (jse.code) 
      {
        case 0: js_state.stick1_x = jse.value;
                break;
        case 1: js_state.stick1_y = jse.value;
                break;
        case 2: js_state.stick2_x = jse.value;
                break;
        case 3: js_state.stick2_y = jse.value;
                break;
        default:
                break;
      }
    } else if (jse.type == JS_EVENT_BUTTON) {
      if (jse.code < 32) {
          my_js_out->button[jse.code] = jse.value;
          js_state.button[jse.code] = jse.value;
      }
    }
  }
  my_js_out->stick1_x = js_state.stick1_x;
  my_js_out->stick1_y = js_state.stick1_y;
  my_js_out->stick2_x = js_state.stick2_x;
  my_js_out->stick2_y = js_state.stick2_y;
  // printf("%d\n", wjse->stick1_y);
  return 0;
}

