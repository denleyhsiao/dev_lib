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

float MathHelper::getX(float range, float azimuthRad)
{
  return range * cos(azimuthRad);
}

float MathHelper::getY(float range, float azimuthRad)
{
  return range * sin(azimuthRad);
}

float MathHelper::getMid(float start, float end)
{
  return (start + end) / 2.0;
}

std::pair<float, float> MathHelper::convert(float x, float y, float azimuthRad)
{
  float tempX = getY(x, azimuthRad) - getX(y, azimuthRad);
  float tempY = getX(x, azimuthRad) + getY(y, azimuthRad);
  return std::make_pair(tempX, tempY);
}
