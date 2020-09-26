#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"
#include "base-types.hpp"
namespace golovin {
  class CompositeShape : public Shape
  {
  public:
    typedef std::shared_ptr<Shape> shapePointer;
    typedef std::unique_ptr<shapePointer[]> shapeArray;

    CompositeShape();

    CompositeShape(const CompositeShape &);

    CompositeShape(CompositeShape &&) noexcept;

    ~CompositeShape() override = default;

    CompositeShape& operator=(const CompositeShape &);

    CompositeShape& operator=(CompositeShape &&) noexcept;

    shapePointer& operator[](size_t) const;

    void pushBack(const shapePointer &);

    void popBack();

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const override;

    void scale(double) override;

    void move(const point_t &) override;

    void move(double dX, double dY) noexcept override;

    bool isEmpty() const noexcept;

    point_t getPos() const override;

    size_t getSize() const noexcept;

    void rotate(double) override;

    void print(std::ostream &) const override;
  private:
    size_t size_;
    size_t capacity_;
    shapeArray array_;
  };
}
#endif //A3_COMPOSITE_SHAPE_HPP
