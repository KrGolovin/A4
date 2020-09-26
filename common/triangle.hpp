#ifndef A1_TRIANGLE_HPP
#define A1_TRIANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"
namespace golovin {
  class Triangle : public Shape
  {
  public:
    Triangle(const point_t &a, const point_t &b, const point_t &c);

    double getArea() const noexcept override;

    void move(const point_t &) noexcept override;

    void move(double dX, double dY) noexcept override;

    void scale(double) override;

    rectangle_t getFrameRect() const noexcept override;

    point_t getPos() const noexcept override;

    void rotate(double) noexcept override;

    void print(std::ostream &) const override;
  private:
    point_t a_;
    point_t b_;
    point_t c_;
  };
}

#endif //A1_TRIANGLE_HPP
