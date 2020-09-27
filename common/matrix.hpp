#ifndef A4_MATRIX_HPP
#define A4_MATRIX_HPP

#include <ostream>
#include "shape.hpp"
#include "layer.hpp"
#include "composite-shape.hpp"

namespace golovin
{
  class MatrixShape
  {
  public:
    typedef std::shared_ptr<Shape> shapePointer;
    typedef std::unique_ptr<shapePointer[]> shapeArray;

    MatrixShape();

    MatrixShape(const MatrixShape &);

    MatrixShape(MatrixShape &&) noexcept;

    explicit MatrixShape(const CompositeShape &);

    ~MatrixShape() = default;

    MatrixShape& operator=(const MatrixShape &);

    MatrixShape& operator=(MatrixShape &&) noexcept;

    Layer operator[](size_t index) const;

    void addShape(const shapePointer &);

    void print( std::ostream &) const;

    size_t getSize() const;
  private:
    size_t rows_;
    size_t cols_;
    shapeArray array_;

    static bool isOverlapped(const shapePointer &first, const shapePointer &second);
  };
}

#endif //A4_MATRIX_HPP
