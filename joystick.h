/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : joystick.h

 * Purpose :

 * Creation Date : 22-09-2011

 * Last Modified : Fri 23 Sep 2011 09:21:36 AM EEST

 * Created By : Greg Liras <gregliras@gmail.com>

 _._._._._._._._._._._._._._._._._._._._._.*/

#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define JOYSTICK_DEVNAME "/dev/input/js0"
#define JOYSTICK_DEVNAME_FF "/dev/input/event7"

#define JS_EVENT_BUTTON         0x01
#define JS_EVENT_AXIS           0x02    /* joystick moved */
#define JS_EVENT_INIT           0x80  


struct js_event {
    unsigned int time; /* event timestamp in milliseconds */
    short value; /* value */
    unsigned char type; /* event type */
    unsigned char code; /* axis/button number */
    };
typedef struct js_event js_event;

struct wwvi_js_event 
{
  int button[32];
  int stick1_x;
  int stick1_y;
  int stick2_x;
  int stick2_y;
};

typedef struct wwvi_js_event wwvi_js_event;






extern int rumble();
extern int open_joystick();
extern int read_joystick_event(js_event *jse);
extern void set_joystick_y_axis(int axis);
extern void set_joystick_x_axis(int axis);
extern void close_joystick();
extern int get_joystick_status(wwvi_js_event *);

#endif
