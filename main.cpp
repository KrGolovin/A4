#include <iostream>
#include <stdexcept>
#include <exception>
#include "common/rectangle.hpp"
#include "common/circle.hpp"
#include "common/triangle.hpp"
#include "common/composite-shape.hpp"
#include "common/polygon.hpp"
#include "common/matrix.hpp"

void printException(const std::exception& e, int level = 0)
{
  std::cerr <<  "Level " << std::to_string(level) << " exception: " << e.what() << '\n';
  try
  {
    std::rethrow_if_nested(e);
  }
  catch(const std::exception& e)
  {
    printException(e, level+1);
  }
}


int main()
{
  const int COUNT_OF_FIGURES = 4;
  golovin::CompositeShape figures;
  figures.pushBack(std::make_shared<golovin::Rectangle>(golovin::point_t{100, 110}, 2, 5));
  figures.pushBack(std::make_shared<golovin::Circle>(golovin::point_t{1, 1}, 1));
  figures.pushBack(std::make_shared<golovin::Triangle>(golovin::point_t{0, 0}, golovin::point_t{0, 1}, golovin::point_t{2, 0}));
  golovin::point_t points[] = {{-1, 1}, {2, 5}, {5, 4}, {4, 2}};
  figures.pushBack(std::make_shared<golovin::Polygon>(points, 4));
  std::string names[] = {"Rectangle", "Circle", "Triangle", "Polygon"};

  for (int i = 0; i < COUNT_OF_FIGURES; i++)
  {
    std::cout << names[i] << ": \n";
    std::cout << "Area of " << names[i] << " is " << figures[i]->getArea() << "\n";
    figures[i]->scale(2);
    std::cout << "Area of " << names[i] << " after scalability 2x is " << figures[i]->getArea() << "\n";
    std::cout << "Frame Rectangle position of " << names[i] << " is (" << figures[i]->getFrameRect().pos.x << "; "
              << figures[i]->getFrameRect().pos.y << ")\n";
    std::cout << "Width frame Rectangle of " << names[i] << " is " << figures[i]->getFrameRect().width
              << " and height is " << figures[i]->getFrameRect().height << "\n";
    figures[i]->move({1, 2});
    std::cout << "Position " << names[i] << " after moving in {1, 2} is (" << figures[i]->getPos().x << "; "
              << figures[i]->getPos().y << ")\n";
    figures[i]->move(1, 2);
    std::cout << "Position " << names[i] << " after moving to offset (1, 2) is (" << figures[i]->getPos().x
              << "; " << figures[i]->getPos().y << ")\n";
    figures[i]->rotate(90);
    std::cout << "Frame Rectangle position of " << names[i] << " after rotate(90) is (" << figures[i]->getFrameRect().pos.x << "; "
              << figures[i]->getFrameRect().pos.y << ")\n";
    std::cout << "Width frame Rectangle of " << names[i] << " after rotate(90) is " << figures[i]->getFrameRect().width
              << " and height is " << figures[i]->getFrameRect().height << "\n\n";

  }
  std::string name = "CompositeShape";
  std::cout << name << ": \n";
  std::cout << "Area of " << name << " is " << figures.getArea() << "\n";
  figures.scale(2);
  std::cout << "Area of " << name << " after scalability 2x is " << figures.getArea() << "\n";
  std::cout << "Frame Rectangle position of " << name << " is (" << figures.getFrameRect().pos.x << "; "
            << figures.getFrameRect().pos.y << ")\n";
  std::cout << "Width frame Rectangle of " << name << " is " << figures.getFrameRect().width
            << " and height is " << figures.getFrameRect().height << "\n";
  figures.move({1, 2});
  std::cout << "Position " << name << " after moving in {1, 2} is (" << figures.getPos().x << "; "
            << figures.getPos().y << ")\n";
  figures.move(1, 2);
  std::cout << "Position " << name << " after moving to offset (1, 2) is (" << figures.getPos().x
            << "; " << figures.getPos().y << ")\n";
  figures.rotate(90);
  std::cout << "Frame Rectangle position of " << name << " after rotate(90) is (" << figures.getFrameRect().pos.x << "; "
            << figures.getFrameRect().pos.y << ")\n";
  std::cout << "Width frame Rectangle of " << name << " after rotate(90) is " << figures.getFrameRect().width
            << " and height is " << figures.getFrameRect().height << "\n\n";

  figures[0]->move({100, 100});
  golovin::MatrixShape matrix(figures);
  matrix.print(std::cout);

  figures.popBack();
  std::cout << ((figures.isEmpty()) ? "Is empty" : "Isn't empty") << '\n';
  figures.popBack();
  std::cout << ((figures.isEmpty()) ? "Is empty" : "Isn't empty") << '\n';
  figures.popBack();
  std::cout << ((figures.isEmpty()) ? "Is empty" : "Isn't empty") << '\n';
  figures.popBack();
  std::cout << ((figures.isEmpty()) ? "Is empty" : "Isn't empty") << '\n';
  try
  {
    figures.pushBack(std::make_shared<golovin::CompositeShape>());
    figures.getFrameRect();
    return 0;
  }
  catch (const std::exception &e)
  {
    printException(e);
    return 0;
  }
  return 0;
}
