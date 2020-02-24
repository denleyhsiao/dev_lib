#ifndef __DEV_LIB_MATH_HELPER_H__
#define __DEV_LIB_MATH_HELPER_H__

#include "dev_lib/decimal_comparer.h"
#include <cmath>

class MathHelper
{
public:
  template <typename T>
  static T distance(T startX, T startY, T endX, T endY, T rad);
  template <typename T>
  static T distance(T offsetX, T offsetY, T rad);
  template <typename T>
  static T yaw(T startX, T startY, T endX, T endY);
  template <typename T>
  static T velocity(T startX, T startY, T endX, T endY, float escapeTime);
  static float rad2Degree(float rad);
  static float degree2Rad(float degree);
  static float getX(float range, float azimuthRad);
  static float getY(float range, float azimuthRad);

public:
  static const float PI;
  static const float PI2;
};

template <typename T>
inline T MathHelper::distance(T startX, T startY, T endX, T endY, T rad)
{
  return distance(startX - endX, startY - endY, rad);
}

template <typename T>
inline T MathHelper::distance(T offsetX, T offsetY, T rad)
{
  return std::sqrt(offsetX * offsetX + offsetY * offsetY - 2 * offsetX * offsetY * cos(rad));
}

template <typename T>
inline T MathHelper::yaw(T startX, T startY, T endX, T endY)
{
  if(DecimalComparer::isEqual(endX, startX))
    return (DecimalComparer::isGreat(endY, startY) ? PI2 : -PI2);

  T result = atan((endY - startY) / (endX - startX));
  if(DecimalComparer::isLess(endX, startX))
    result += PI;
  else if(DecimalComparer::isLess(endY, startY))
    result += PI + PI;
  return result;
}

template <typename T>
T MathHelper::velocity(T startX, T startY, T endX, T endY, float escapeTime)
{
  T motionDistance = distance(startX, startY, endX, endY, PI2);
  return motionDistance / escapeTime;
}

#endif
