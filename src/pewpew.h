/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : pewpew.h

* Purpose :

* Creation Date : 20-10-2011

* Last Modified : Sun 23 Oct 2011 11:36:45 AM EEST

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#ifndef PEWPEW_H
#define PEWPEW_H

#include "level.h"
#include "menu.h"
static void mytimer(int v);
void end(void);
void end_0(void);
void run(void);
void gpause(void);
void info_action(void);
void option_action(void);
void display(void);
void reshape(int w, int h);
void kbRelF(unsigned char key,int x,int y);
void kbF(unsigned char key, int x, int y);
void skbF(int key, int x, int y);
void mIdleF(int x, int y);
void mF(int btn,int state,int x, int y);


#endif
