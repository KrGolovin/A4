#ifndef A4_LAYER_HPP
#define A4_LAYER_HPP

#include <memory>
#include "shape.hpp"

namespace golovin
{
  class Layer
  {
  public:
    typedef std::shared_ptr<Shape> shapePointer;
    typedef std::unique_ptr<shapePointer[]> shapeArray;

    Layer(const Layer &);

    Layer(Layer &&) noexcept;

    Layer(const shapeArray &array, size_t size);

    ~Layer() = default;

    Layer& operator=(const Layer &);

    Layer& operator=(Layer &&) noexcept;

    shapePointer operator[](size_t index) const;

    size_t getSize() const noexcept;

  private:
    size_t size_;
    shapeArray array_;
  };
}


#endif //A4_LAYER_HPP
