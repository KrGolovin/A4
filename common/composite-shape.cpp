#include "composite-shape.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <exception>
#include <string>
#include "base-types.hpp"

golovin::CompositeShape::CompositeShape():
  size_(0),
  capacity_(1),
  array_(std::make_unique<shapePointer[]>(capacity_))
{}

golovin::CompositeShape::CompositeShape(const CompositeShape &src):
  size_(src.size_),
  capacity_(src.size_),
  array_(std::make_unique<shapePointer[]>(src.size_))
{
  for (size_t i = 0; i < src.size_; ++i)
  {
    array_[i] = src.array_[i];
  }
}

golovin::CompositeShape::CompositeShape(CompositeShape &&src) noexcept:
  size_(src.size_),
  capacity_(src.capacity_),
  array_(std::move(src.array_))
{
  src.size_ = 0;
  src.capacity_ = 0;
}

golovin::CompositeShape& golovin::CompositeShape::operator=(const CompositeShape &src)
{
  if (this != &src)
  {
    shapeArray tmpArray = std::make_unique<shapePointer[]>(src.size_);
    size_ = src.size_;
    capacity_= src.size_;
    for (size_t i = 0; i < src.size_; ++i)
    {
      tmpArray[i] = src.array_[i];
    }
    array_.swap(tmpArray);
  }
  return *this;
}

golovin::CompositeShape& golovin::CompositeShape::operator=(CompositeShape &&src) noexcept
{
  if (this != &src)
  {
    size_ = src.size_;
    capacity_ = src.size_;
    array_ = std::move(src.array_);
    src.size_ = 0;
    src.capacity_ = 0;
  }
  return *this;
}

golovin::CompositeShape::shapePointer &golovin::CompositeShape::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Index is out of range");
  }
  return array_[index];
}

void golovin::CompositeShape::pushBack(const golovin::CompositeShape::shapePointer &newElement)
{
  if (newElement == nullptr)
  {
    throw std::invalid_argument("Empty pointer");
  }

  if (size_ == capacity_)
  {
    shapeArray tmp(std::make_unique<shapePointer[]>(2 * capacity_));
    for (size_t i = 0; i < size_; ++i)
    {
      tmp[i] = array_[i];
    }
    array_.swap(tmp);
    capacity_ *= 2;
  }
  array_[size_++] = newElement;
}

void golovin::CompositeShape::popBack()
{
  if (size_ == 0)
  {
    throw std::logic_error("Array is empty");
  }
  array_[--size_].reset();
}

double golovin::CompositeShape::getArea() const noexcept
{
  double sum = 0.0;
  for (size_t i = 0; i < size_; ++i)
  {
    sum += array_[i]->getArea();
  }
  return sum;
}

golovin::rectangle_t golovin::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    throw std::logic_error("Array is empty");
  }
  size_t index = 0;
  try
  {
    rectangle_t rectangle = array_[0]->getFrameRect();
    double minX = rectangle.pos.x - rectangle.width / 2.0;
    double maxX = rectangle.pos.x + rectangle.width / 2.0;
    double minY = rectangle.pos.y - rectangle.height / 2.0;
    double maxY = rectangle.pos.y + rectangle.height / 2.0;
    for (index = 1; index < size_; ++index)
    {
      rectangle_t curr = array_[index]->getFrameRect();
      minX = std::min(minX, curr.pos.x - curr.width / 2.0);
      maxX = std::max(maxX, curr.pos.x + curr.width / 2.0);
      minY = std::min(minY, curr.pos.y - curr.height / 2.0);
      maxY = std::max(maxY, curr.pos.y + curr.height / 2.0);
    }
    return {std::abs(maxX - minX), std::abs(maxY - minY),
        {(maxX + minX) / 2.0, (maxY + minY) / 2.0}};
  }
  catch (const std::exception &e)
  {
    std::throw_with_nested(std::logic_error("Failed to perform operation for shape at index " + std::to_string(index)));
  }
}

void golovin::CompositeShape::scale(double coefficient)
{
  if(coefficient <= 0.0)
  {
    throw std::invalid_argument("Scaling coefficient is not positive");
  }
  for (size_t i = 0; i < size_; i++)
  {
    const point_t center = getFrameRect().pos;
    double dX = array_[i]->getFrameRect().pos.x - center.x;
    double dY = array_[i]->getFrameRect().pos.y - center.y;
    array_[i]->move(center.x + dX * coefficient, center.y + dY * coefficient);
    array_[i]->scale(coefficient);
  }
}

void golovin::CompositeShape::move(const golovin::point_t & destinationPoint)
{
  double dx = destinationPoint.x - getFrameRect().pos.x;
  double dy = destinationPoint.y - getFrameRect().pos.y;
  move(dx, dy);
}

void golovin::CompositeShape::move(double dX, double dY) noexcept
{
  for (size_t i = 0; i < size_; ++i)
  {
    array_[i]->move(dX, dY);
  }
}

bool golovin::CompositeShape::isEmpty() const noexcept
{
  return (size_ == 0);
}

golovin::point_t golovin::CompositeShape::getPos() const
{
  return getFrameRect().pos;
}

void golovin::CompositeShape::rotate(double angle)
{
  const double PI_IN_DEGREES = 180.0;
  const double angleRadian = angle * (M_PI / PI_IN_DEGREES);
  const double sinAngle = std::sin(angleRadian);
  const double cosAngle = std::cos(angleRadian);
  point_t centerShape = getFrameRect().pos;
  for (size_t i = 0; i < size_; ++i)
  {
    point_t currCenter = array_[i]->getFrameRect().pos;
    const double deltaX = centerShape.x + (currCenter.x - centerShape.x) * cosAngle - (currCenter.y - centerShape.y) * sinAngle;
    const double deltaY = centerShape.y + (currCenter.y - centerShape.y) * cosAngle - (currCenter.x - centerShape.x) * sinAngle;
    array_[i]->move({deltaX, deltaY});
    array_[i]->rotate(angle);
  }
}

size_t golovin::CompositeShape::getSize() const noexcept
{
  return size_;
}

void golovin::CompositeShape::print(std::ostream &out) const
{
  out << "CompositeShape ";
}