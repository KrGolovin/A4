#include "layer.hpp"

golovin::Layer::Layer(const Layer &src):
  size_(src.size_),
  array_(std::make_unique<shapePointer[]>(src.size_))
{
  for (size_t i = 0; i < src.size_; ++i)
  {
    array_[i] = src.array_[i];
  }
}

golovin::Layer::Layer(Layer &&src) noexcept:
  size_(src.size_),
  array_(std::move(src.array_))
{
  src.size_ = 0;
}

golovin::Layer::Layer(const shapeArray &array, size_t size):
  size_(size),
  array_(std::make_unique<shapePointer[]>(size_))
{
  for (size_t i = 0; i < size_; ++i)
  {
    array_[i] = array[i];
  }
}

golovin::Layer &golovin::Layer::operator=(const Layer &src)
{
  if (this != &src)
  {
    size_ = src.size_;
    shapeArray tmpArray(std::make_unique<shapePointer[]>(size_));
    for (size_t i = 0; i < size_; ++i)
    {
      tmpArray[i] = src.array_[i];
    }
    array_.swap(tmpArray);
  }
  return *this;
}

golovin::Layer &golovin::Layer::operator=(Layer &&src) noexcept
{
  if (this != &src)
  {
    size_ = src.size_;
    array_ = std::move(src.array_);
    src.size_ = 0;
  }
  return *this;
}

size_t golovin::Layer::getSize() const noexcept
{
  return size_;
}

golovin::Layer::shapePointer golovin::Layer::operator[](size_t index) const
{
  if ((index >= size_) || (index < 0))
  {
    throw std::out_of_range("Index is out of range");
  }
  return array_[index];
}
