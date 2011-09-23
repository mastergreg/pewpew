#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "joystick.h"

static int joystick_fd = -1;
static wwvi_js_event js_state;

int open_joystick()
{
  joystick_fd = open(JOYSTICK_DEVNAME, O_RDONLY | O_NONBLOCK); /* read write for force feedback? */
  if (joystick_fd < 0)
    return joystick_fd;

  /* maybe ioctls to interrogate features here? */

  return joystick_fd;
}

int read_joystick_event(struct js_event *jse)
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
  close(joystick_fd);
}


int get_joystick_status(wwvi_js_event *my_js_out)
{
  int rc;
  struct js_event jse;
  if (joystick_fd < 0)
    return -1;
  for(int i =0;i< 32;i++)
  {
    js_state.button[i]=0;
    //need to clear buttons state
  }
  // memset(wjse, 0, sizeof(*wjse));
  while ((rc = read_joystick_event(&jse) == 1)) 
  {
    jse.type &= ~JS_EVENT_INIT; /* ignore synthetic events */
    if (jse.type == JS_EVENT_AXIS) 
    {
      switch (jse.number) 
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
      if (jse.number < 32) {
        switch (jse.value) {
          case 0:
          case 1: 
            my_js_out->button[jse.number] = jse.value;
            js_state.button[jse.number] = jse.value;
            break;
          default:
            break;
        }
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

