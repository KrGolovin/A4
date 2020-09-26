#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace golovin
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t &, double width, double height);

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
    double width_;
    double height_;
    double angle_;
  };
}

#endif
