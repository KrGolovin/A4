#include "triangle.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>

const double ACCURACY = 1e-8;

golovin::Triangle::Triangle(const point_t & a, const point_t & b, const point_t & c):
  a_(a),
  b_(b),
  c_(c)
{
  if (getArea() < ACCURACY)
  {
    throw std::invalid_argument("All points lie on one straight line");
  }
}

double golovin::Triangle::getArea() const noexcept
{
  return std::abs(a_.x * (b_.y - c_.y) + b_.x * (c_.y - a_.y) + c_.x * (a_.y - b_.y)) / 2.0;
}

golovin::rectangle_t golovin::Triangle::getFrameRect() const noexcept
{
  const double minX = std::min(std::min(a_.x, b_.x), c_.x);
  const double minY = std::min(std::min(a_.y, b_.y), c_.y);
  const double maxX = std::max(std::max(a_.x, b_.x), c_.x);
  const double maxY = std::max(std::max(a_.y, b_.y), c_.y);
  return {std::abs(maxX - minX), std::abs(maxY - minY), {(maxX + minX) / 2, (maxY + minY) / 2}};
}

void golovin::Triangle::move(const point_t &destinationPoint) noexcept
{
  const double deltaX = destinationPoint.x - getPos().x;
  const double deltaY = destinationPoint.y - getPos().y;
  move(deltaX, deltaY);
}

void golovin::Triangle::move(double dX, double dY) noexcept
{
  a_.x += dX;
  b_.x += dX;
  c_.x += dX;
  a_.y += dY;
  b_.y += dY;
  c_.y += dY;
}

golovin::point_t golovin::Triangle::getPos() const noexcept
{
  return {(a_.x + b_.x + c_.x) / 3, (a_.y + b_.y + c_.y) / 3};
}

void golovin::Triangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("The incoming coefficient of the scalability must be > 0");
  }
  point_t basePoint = getPos();
  a_.x *= coefficient;
  a_.y *= coefficient;
  b_.x *= coefficient;
  b_.y *= coefficient;
  c_.x *= coefficient;
  c_.y *= coefficient;
  move(basePoint);
}

void golovin::Triangle::rotate(double angle) noexcept
{
  const double PI_IN_DEGREES = 180.0;
  const double angleRadian = angle * (M_PI / PI_IN_DEGREES);
  const double sinAngle = std::sin(angleRadian);
  const double cosAngle = std::cos(angleRadian);
  const point_t center = getPos();
  a_ = {center.x + (a_.x - center.x) * cosAngle - (a_.y - center.y) * sinAngle,
      center.y + (a_.y - center.y) * cosAngle + (a_.x - center.x) * sinAngle};
  b_ = {center.x + (b_.x - center.x) * cosAngle - (b_.y - center.y) * sinAngle,
      center.y + (b_.y - center.y) * cosAngle + (b_.x - center.x) * sinAngle};
  c_ = {center.x + (c_.x - center.x) * cosAngle - (c_.y - center.y) * sinAngle,
      center.y + (c_.y - center.y) * cosAngle + (c_.x - center.x) * sinAngle};
}

void golovin::Triangle::print(std::ostream &out) const
{
  out << "Triangle ";
}
