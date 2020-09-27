#include "matrix.hpp"
#include <cmath>

golovin::MatrixShape::MatrixShape():
  rows_(1),
  cols_(1),
  array_(std::make_unique<shapePointer[]>(1))
{
  array_[0] = nullptr;
}

golovin::MatrixShape::MatrixShape(const MatrixShape &src):
  rows_(src.rows_),
  cols_(src.cols_),
  array_(std::make_unique<shapePointer[]>(cols_ * rows_))
{
  for (size_t i = 0; i < cols_ * rows_; ++i)
  {
    array_[i] = src.array_[i];
  }
}

golovin::MatrixShape::MatrixShape(MatrixShape &&src) noexcept:
  rows_(src.rows_),
  cols_(src.cols_),
  array_(std::move(src.array_))
{
  src.rows_ = 0;
  src.cols_ = 0;
}

golovin::MatrixShape::MatrixShape(const CompositeShape &cShape):
  MatrixShape()
{
  if (cShape.isEmpty())
  {
    throw std::invalid_argument("Composite shape must be not empty");
  }
  for (size_t i = 0; i < cShape.getSize(); ++i)
  {
    addShape(cShape[i]);
  }
}

golovin::MatrixShape &golovin::MatrixShape::operator=(const MatrixShape &src)
{
  if (this != &src)
  {
    shapeArray tmpArray = std::make_unique<shapePointer[]>(rows_ * cols_);
    rows_ = src.rows_;
    cols_= src.cols_;
    for (size_t i = 0; i < (rows_ * cols_); ++i)
    {
      tmpArray[i] = src.array_[i];
    }
    array_.swap(tmpArray);
  }
  return *this;
}

golovin::MatrixShape &golovin::MatrixShape::operator=(MatrixShape &&src) noexcept
{
  if (this != &src)
  {
    rows_ = src.rows_;
    cols_ = src.cols_;
    array_ = std::move(src.array_);
    src.rows_ = 0;
    src.cols_ = 0;
  }
  return *this;
}

void golovin::MatrixShape::addShape(const shapePointer &shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Null pointer received");
  }
  size_t currRow = 0;
  bool isPlace = false;
  for (size_t i = 0; i < rows_; ++i)
  {
    if (isPlace)
    {
      break;
    }
    for (size_t j = 0; (j < cols_); ++j)
    {
      if (array_[i * cols_ + j] == nullptr)
      {
        isPlace = true;
        break;
      }
      if (isOverlapped(array_[i * cols_ + j], shape))
      {
        ++currRow;
        break;
      }
    }
  }
  if (currRow == rows_)
  {
    shapeArray tmpArray = std::make_unique<shapePointer[]>(cols_ * (++rows_));
    for (size_t i = 0; i < (rows_ - 1) * cols_; ++i)
    {
      tmpArray[i] = array_[i];
    }
    for (size_t i = 0; i < cols_; ++i)
    {
      tmpArray[(rows_ - 1) * cols_ + i] = nullptr;
    }
    array_.swap(tmpArray);
  }
  for (size_t i = 0; i < cols_; ++i)
  {
    if (!array_[currRow * cols_ + i])
    {
      array_[currRow * cols_ + i] = shape;
      return;
    }
  }
  shapeArray tmpArray = std::make_unique<shapePointer[]>((++cols_) * rows_);
  for (size_t i = 0; i < rows_; ++i)
  {
    for (size_t j = 0; j < (cols_ - 1); ++j)
    {
      tmpArray[i * cols_ + j] = array_[i * cols_ + j];
    }
    tmpArray[i * cols_ + (cols_ - 1)] = nullptr;
  }
  array_.swap(tmpArray);
  array_[currRow * cols_ + (cols_ - 1)] = shape;
}

bool golovin::MatrixShape::isOverlapped(const shapePointer &first, const shapePointer &second)
{
  if (!first || !second)
  {
    return false;
  }
  else
  {
    const double distanceX = std::fabs(first->getFrameRect().pos.x - second->getFrameRect().pos.x);
    const double distanceY = std::fabs(first->getFrameRect().pos.y - second->getFrameRect().pos.y);
    const double sumWidth = ((first->getFrameRect().width + second->getFrameRect().width) / 2);
    const double sumHeight = ((first->getFrameRect().height + second->getFrameRect().height) / 2);
    return (distanceX < sumWidth) && (distanceY < sumHeight);
  }

}

golovin::Layer golovin::MatrixShape::operator[](const size_t index) const
{
  if ((index >= rows_) || (index < 0))
  {
    throw std::out_of_range("Index is out of range");
  }
  shapeArray tmpArray(std::make_unique<shapePointer[]>(cols_));
  for (size_t i = 0; i < cols_; ++i)
  {
    tmpArray[i] = array_[index * cols_ + i];
  }
  return Layer(tmpArray, rows_);
}

void golovin::MatrixShape::print(std::ostream &out) const
{
  for (size_t i = 0; i < rows_; ++i)
  {
    out << "Layer " + std::to_string(i) + " : ";
    for (size_t j = 0; j < cols_; ++j)
    {
      if (!array_[i * cols_ + j])
      {
        break;
      }
      array_[i * cols_ + j]->print(out);
    }
    out << "\n";
  }
}
