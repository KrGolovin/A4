#ifndef A4_POLYGON_HPP
#define A4_POLYGON_HPP
#include <memory>
#include "shape.hpp"
#include "base-types.hpp"

namespace golovin
{
  class Polygon : public Shape
  {
  public:

    Polygon(const Polygon &);

    Polygon(Polygon &&) noexcept;

    Polygon(const point_t array[], size_t size);

    ~Polygon() = default;

    Polygon& operator=(const Polygon &);

    Polygon& operator=(Polygon &&) noexcept;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void scale(double) override;

    void move(const point_t &) noexcept override;

    void move(double dx, double dy) noexcept override;

    point_t getPos() const noexcept override;

    void rotate(double) noexcept override;

    void print(std::ostream &) const override;
  private:
    std::unique_ptr<point_t[]> array_;
    size_t size_;
  };
}

#endif //A4_POLYGON_HPP
