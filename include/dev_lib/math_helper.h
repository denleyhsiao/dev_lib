#ifndef __DEV_LIB_MATH_HELPER_H__
#define __DEV_LIB_MATH_HELPER_H__

class MathHelper
{
public:
  template <typename T>
  static T distance(T startX, T startY, T endX, T endY, T rad);
  template <typename T>
  static T distance(T offsetX, T offsetY, T rad);
  static float rad2Degree(float rad);
  static float degree2Rad(float degree);

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
  return sqrt(offsetX * offsetX + offsetY * offsetY - 2 * offsetX * offsetY * cos(rad));
}

#endif
