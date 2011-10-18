#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>
#define COS_THETA 0.997564050259824247613162680
#define SIN_THETA 0.069756473744125300775958835
#define SPEED_MAX 5000 
#define SPEED_MIN 20 
class vector2D
{
  private:
    double x;
    double y;
    int remaining_deg;
    int remaining_inc;
  public:
    vector2D();
    vector2D(double a,double b,int rd,int ri);
    void increase_vector(vector2D v);
    void set_vector(vector2D v);
    void scale(double a,double b);
    void vincrease();
    void vdecrease();
    void soft_scale();
    void increase_reset();
    void soft_rotate();
    void rotate_reset();
    void rotater();
    void rotatel();
    double length();
    double distance(vector2D );
    double getX();
    double getY();
    int getRD();
    int getRI();

};
#endif


