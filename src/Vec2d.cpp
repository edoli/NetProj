/*
 * Vec2d.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: daniel
 */

#include <cassert>
#include "Vec2d.hpp"

//////////////////
// Constructors //
//////////////////
Vec2d::Vec2d(double value)
{
  x = y = value;
}


Vec2d::Vec2d(double x, double y)
{
  this->x = x;
  this->y = y;
}


Vec2d::Vec2d(const Vec2d& v)
{
  x = v.x;
  y = v.y;
}


////////////////
// Inspectors //
////////////////
double Vec2d::operator[](size_t index) const
{
  assert(index < 2);
  return data[index];
}


double& Vec2d::operator[](size_t index)
{
  assert(index < 2);
  return data[index];
}



///////////////
// Operators //
///////////////
Vec2d& Vec2d::operator=(const Vec2d& v)
{
  _assign(v);
  return *this;
}


bool Vec2d::operator==(const Vec2d& v) const
{
  return (x == v.x) && (y == v.y);
}


bool Vec2d::operator!=(const Vec2d& v) const
{
  return (x != v.x) || (y != v.y);
}


Vec2d Vec2d::operator+(const Vec2d& v) const
{
  return Vec2d(x + v.x, y + v.y);
}


Vec2d Vec2d::operator-(const Vec2d& v) const
{
  return Vec2d(x - v.x, y - v.y);
}


Vec2d Vec2d::operator*(const Vec2d& v) const
{
  return Vec2d(x * v.x, y * v.y);
}


Vec2d Vec2d::operator*(double scale) const
{
  return Vec2d(x * scale, y * scale);
}


Vec2d Vec2d::operator/(const Vec2d& v) const
{
  return Vec2d(x / v.x, y / v.y);
}


Vec2d Vec2d::operator/(double scale) const
{
  return Vec2d(x / scale, y / scale);
}


Vec2d& Vec2d::operator+=(const Vec2d& v)
{
  x += v.x;
  y += v.y;
  return *this;
}


Vec2d& Vec2d::operator-=(const Vec2d& v)
{
  x -= v.x;
  y -= v.y;
  return *this;
}


Vec2d& Vec2d::operator*=(const Vec2d& v)
{
  x *= v.x;
  y *= v.y;
  return *this;
}


Vec2d& Vec2d::operator*=(double scale)
{
  x *= scale;
  y *= scale;
  return *this;
}


Vec2d& Vec2d::operator/=(const Vec2d& v)
{
  x /= v.x;
  y /= v.y;
  return *this;
}


Vec2d& Vec2d::operator/=(double scale)
{
  x /= scale;
  y /= scale;
  return *this;
}



///////////////
// Modifiers //
///////////////
double Vec2d::dot(const Vec2d& v) const
{
  return x*v.x + y*v.y;
}


double Vec2d::squared_length(void) const
{
  return dot(*this);
}


double Vec2d::length(void) const
{
  return sqrt(squared_length());
}


double Vec2d::squared_distance(const Vec2d& v) const
{
  return (*this - v).squared_length();
}


double Vec2d::distance(const Vec2d& v) const
{
  return sqrt(squared_distance(v));
}


Vec2d Vec2d::normalize(void) const
{
  return *this / length();
}



/////////////////////
// Private Methods //
/////////////////////
void Vec2d::_assign(const Vec2d& v)
{
  x = v.x;
  y = v.y;
}


void Vec2d::_swap(Vec2d& v)
{
  std::swap(x, v.x);
  std::swap(y, v.y);
}


