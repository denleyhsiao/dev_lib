#include "dev_lib/math_helper.h"

const float MathHelper::PI = 3.1415926;
const float MathHelper::PI2 = PI + PI;

float MathHelper::rad2Degree(float rad)
{
  return (rad * 180. / PI) ;
}

float MathHelper::degree2Rad(float degree)
{
  return (degree * PI / 180.) ;
}