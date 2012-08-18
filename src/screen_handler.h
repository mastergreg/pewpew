/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : screen_handler.h

* Purpose :

* Creation Date : 02-11-2011

* Last Modified : Wed 02 Nov 2011 09:46:27 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef SCREEN_HANDLER_H
#define SCREEN_HANDLER_H


class screen_handler
{
protected:
    int WINDOW_SIZEY;
    int WINDOW_SIZEX;
    void *font;
    void *tinyFont;
    virtual void playStick();
public:
    screen_handler();
    virtual void display();
    virtual void reshape(int w,int h);
    virtual void idleMouseFunction(int x,int y);
    virtual void mouseFunction(int btn,int state,int x,int y);
    virtual void keyboardFunction(unsigned char key,int x, int y);
    virtual void specialKeyboardFunction(int key,int x, int y);
    virtual void keyboardReleaseFunction(unsigned char key,int x, int y);

};






#endif
