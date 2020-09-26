#include "polygon.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>

const double ACCURACY = 1e-8;

golovin::Polygon::Polygon(const Polygon &src):
  size_(src.size_),
  array_(std::make_unique<point_t[]>(src.size_))
{
  for (size_t i = 0; i < src.size_; ++i)
  {
    array_[i] = src.array_[i];
  }
}

golovin::Polygon::Polygon(Polygon &&src) noexcept:
  size_(src.size_),
  array_(std::move(src.array_))
{
  src.size_ = 0;
}

golovin::Polygon::Polygon(const point_t array[], const size_t size):
  size_(size)
{
  if (size_ < 3)
  {
    throw std::invalid_argument("Polygon must be at least 3 points");
  }
  if (array == nullptr)
  {
    throw std::invalid_argument("Null pointer received");
  }
  array_ = std::make_unique<golovin::point_t[]>(size_);
  for (size_t i = 0; i < size_; ++i)
  {
    array_[i] = array[i];
  }
  if (getArea() < ACCURACY)
  {
    throw std::invalid_argument("The shape must have an area");
  }
  bool rightTurn = false;
  bool leftTurn = false;
  for (size_t i = 0; i < size_; ++i)
  {
    size_t j = (i + 1) % size_;
    size_t k = (i + 2) % size_;
    double composition = (array_[j].x - array_[i].x) * (array_[k].y - array_[j].y)
        - (array_[j].y - array_[i].y) * (array_[k].x - array_[j].x);
    if (composition > 0)
    {
      leftTurn = true;
    }
    else if (composition < 0)
    {
      rightTurn = true;
    }
    if (rightTurn && leftTurn)
    {
      throw std::invalid_argument("Poligon must be convex");
    }
  }
}

golovin::Polygon &golovin::Polygon::operator=(const Polygon &src)
{
  if (this != &src)
  {
    size_ = src.size_;
    std::unique_ptr<point_t[]> tmpArray(std::make_unique<golovin::point_t[]>(size_));
    for (size_t i = 0; i < size_; ++i)
    {
      tmpArray[i] = src.array_[i];
    }
    array_.swap(tmpArray);
  }
  return *this;
}

golovin::Polygon &golovin::Polygon::operator=(Polygon &&src) noexcept
{
  if (this != &src)
  {
    size_ = src.size_;
    array_ = std::move(src.array_);
    src.size_ = 0;
  }
  return *this;
}

double golovin::Polygon::getArea() const noexcept
{
  double area = 0.0;
  for (size_t i = 0; i < size_; ++i)
  {
    area += (array_[i].x * array_[(i + 1) % size_].y - array_[i].y * array_[(i + 1) % size_].x);
  }
  return std::fabs(area) / 2;
}

golovin::rectangle_t golovin::Polygon::getFrameRect() const noexcept
{
  double minX = array_[0].x;
  double maxX = array_[0].x;
  double minY = array_[0].y;
  double maxY = array_[0].y;
  for (size_t i = 1; i < size_; ++i)
  {
    point_t curr = array_[i];
    minX = std::min(minX, curr.x);
    maxX = std::max(maxX, curr.x);
    minY = std::min(minY, curr.y);
    maxY = std::max(maxY, curr.y);
  }
  return {std::abs(maxX - minX), std::abs(maxY - minY),
      {(maxX + minX) / 2, (maxY + minY) / 2}};
}

void golovin::Polygon::scale(double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument("Scale coefficient must be > 0");
  }
  point_t basePoint = getPos();
  for (size_t i = 0; i < size_; ++i)
  {
    array_[i].x *= coefficient;
    array_[i].y *= coefficient;
  }
  move(basePoint);
}

void golovin::Polygon::move(const point_t &destinationPoint) noexcept
{
  move(destinationPoint.x - getPos().x, destinationPoint.y - getPos().y);
}

void golovin::Polygon::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < size_; ++i)
  {
    array_[i].x += dx;
    array_[i].y += dy;
  }
}

golovin::point_t golovin::Polygon::getPos() const noexcept
{
  double posX = 0.0;
  double posY = 0.0;
  for (size_t i = 0; i < size_; ++i)
  {
    posX += array_[i].x;
    posY += array_[i].y;
  }
  return {posX / size_, posY / size_};
}

void golovin::Polygon::rotate(double angle) noexcept
{
  const double PI_IN_DEGREES = 180.0;
  const double angleRadian = angle * (M_PI / PI_IN_DEGREES);
  const double sinAngle = std::sin(angleRadian);
  const double cosAngle = std::cos(angleRadian);
  const point_t center = getPos();
  for (size_t i = 0; i < size_; ++i)
  {
    array_[i] = {center.x + (array_[i].x - center.x) * cosAngle - (array_[i].y - center.y) * sinAngle,
        center.y + (array_[i].y - center.y) * cosAngle + (array_[i].x - center.x) * sinAngle};
  }
}

void golovin::Polygon::print(std::ostream &out) const
{
  out << "CompositeShape ";
}
