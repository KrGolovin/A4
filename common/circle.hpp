#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace golovin
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t &, double);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void scale(double) override;

    void move(const point_t &) noexcept override;

    void move(double dX, double dY) noexcept override;

    point_t getPos() const noexcept override;

    void rotate(double) noexcept override;

    void print(std::ostream &) const override;

  private:
    point_t center_;
    double radius_;
  };
}
#endif
