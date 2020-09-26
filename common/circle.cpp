#include "circle.hpp"
#include <cmath>
#include <stdexcept>

golovin::Circle::Circle(const point_t &center, double radius):
  center_(center),
  radius_(radius)
{
  if (radius_ <= 0.0)
  {
    throw std::invalid_argument("The incoming raduis of the circle must be > 0");
  }
}

double golovin::Circle::getArea() const noexcept
{
  return M_PI * std::pow(radius_, 2);
}

golovin::rectangle_t golovin::Circle::getFrameRect() const noexcept
{
  return {2 * radius_, 2 * radius_, center_};
}

void golovin::Circle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("The incoming coefficient of the scalability must be > 0");
  }
  radius_ *= coefficient;
}

void golovin::Circle::move(const point_t &destinationPoint) noexcept
{
  center_ = destinationPoint;
}

void golovin::Circle::move(double dX, double dY) noexcept
{
  center_.x += dX;
  center_.y += dY;
}

golovin::point_t golovin::Circle::getPos() const noexcept
{
  return getFrameRect().pos;
}

void golovin::Circle::rotate(double) noexcept
{}

void golovin::Circle::print(std::ostream &out) const
{
  out << "Circle ";
}
