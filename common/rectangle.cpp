#include "rectangle.hpp"
#include <cmath>
#include <stdexcept>

golovin::Rectangle::Rectangle(const point_t &center, double width, double height):
  center_(center),
  width_(width),
  height_(height),
  angle_(0.0)
{
  if ((width_ <= 0.0) || (height_ <= 0.0))
  {
    throw std::invalid_argument("The incoming sides of the rectangle must be > 0");
  }
}

double golovin::Rectangle::getArea() const noexcept
{
  return width_ * height_;
}

golovin::rectangle_t golovin::Rectangle::getFrameRect() const noexcept
{
  const double PI_IN_DEGREES = 180.0;
  const double angleRadian = angle_ * (M_PI / PI_IN_DEGREES);
  const double sinAngle = std::fabs(std::sin(angleRadian));
  const double cosAngle = std::fabs(std::cos(angleRadian));
  const double frameWidth = height_ * sinAngle + width_ * cosAngle;
  const double frameHeight = height_ * cosAngle + width_ * sinAngle;
  return {frameWidth, frameHeight, center_};
}

void golovin::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("The incoming coefficient of the scalability must be > 0");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}

void golovin::Rectangle::move(const point_t &destinationPoint) noexcept
{
  center_ = destinationPoint;
}

void golovin::Rectangle::move(double dX, double dY) noexcept
{
  center_.x += dX;
  center_.y += dY;
}

golovin::point_t golovin::Rectangle::getPos() const noexcept
{
  return getFrameRect().pos;
}

void golovin::Rectangle::rotate(double angle) noexcept
{
  const double FULL_TURN = 360.0;
  angle_ = std::fmod(angle_ + angle, FULL_TURN);
}

void golovin::Rectangle::print(std::ostream &out) const
{
  out << "Rectangle ";
}