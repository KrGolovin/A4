#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <stdexcept>
#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include "common/rectangle.hpp"
#include "common/circle.hpp"
#include "common/triangle.hpp"
#include "common/composite-shape.hpp"
#include "common/polygon.hpp"
#include "common/matrix.hpp"

const double ACCURACY = 1e-8;

BOOST_AUTO_TEST_SUITE(TestRectangle)

  BOOST_AUTO_TEST_CASE(TestInvalidWidth)
  {
    const double width = -5.0;
    const double height = 10.0;
    const golovin::point_t basePoint{0.0, 0.0};

    BOOST_CHECK_THROW(golovin::Rectangle rectangle(basePoint, width, height), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestInvalidHeight)
  {
    const double width = 5.0;
    const double height = -10.0;
    const golovin::point_t basePoint{0.0, 0.0};

    BOOST_CHECK_THROW(golovin::Rectangle rectangle(basePoint, width, height), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestMovingInPoint)
  {
    const golovin::point_t basePoint{0.0, 0.0};
    const golovin::point_t endPoint{10.0, -10.0};
    const double width = 5.0;
    const double height = 10.0;

    golovin::Rectangle rectangle(basePoint, width, height);
    rectangle.move(endPoint);

    BOOST_CHECK_CLOSE_FRACTION(rectangle.getPos().x, endPoint.x, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getPos().y, endPoint.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestMovingByOffset)
  {
    const double dX = 2.0;
    const double dY = -2.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    golovin::Rectangle rectangle(basePoint, width, height);
    rectangle.move(dX, dY);

    BOOST_CHECK_CLOSE(rectangle.getPos().x, basePoint.x + dX, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getPos().y, basePoint.y + dY, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestRightArea)
  {
    const double width = 5.0;
    const double height = 10.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double rightArea = 50.0;

    golovin::Rectangle rectangle(basePoint, width, height);

    BOOST_CHECK_CLOSE(rectangle.getArea(), rightArea, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfRectangleAfterMovingInPoint)
  {
    const double baseWidth = 5.0;
    const double baseHeight = 10.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const golovin::point_t endPoint{10.0, -10.0};

    golovin::Rectangle rectangle(basePoint, baseWidth, baseHeight);
    double width = rectangle.getFrameRect().width;
    double height = rectangle.getFrameRect().height;
    rectangle.move(endPoint);

    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, width, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, height, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfRectangleAfterMovingByOffset)
  {
    const double width = 2.0;
    const double height = 4.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double dX = 2.0;
    const double dY = -2.0;

    golovin::Rectangle rectangle(basePoint, width, height);
    rectangle.move(dX, dY);

    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, width, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, height, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfAreaAfterMovingInPoint)
  {
    const double baseWidth = 5.0;
    const double baseHeight = 10.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const golovin::point_t endPoint{10.0, -10.0};

    golovin::Rectangle rectangle(basePoint, baseWidth, baseHeight);
    double area = rectangle.getArea();
    rectangle.move(endPoint);

    BOOST_CHECK_CLOSE(rectangle.getArea(), area, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfAreaAfterMovingByOffset)
  {
    const double width = 2.0;
    const double height = 4.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double dX = 2.0;
    const double dY = -2.0;

    golovin::Rectangle rectangle(basePoint, width, height);
    double area = rectangle.getArea();
    rectangle.move(dX, dY);

    BOOST_CHECK_CLOSE(rectangle.getArea(), area, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvalidScale)
  {
    const double width = 2.0;
    const double height = 4.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double scaleValue = -2.0;

    golovin::Rectangle rectangle(basePoint, width, height);

    BOOST_CHECK_THROW(rectangle.scale(scaleValue), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRightAreaAfterScale)
  {
    const double width = 2.0;
    const double height = 4.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double scaleValue = 2.0;

    golovin::Rectangle rectangle(basePoint, width, height);
    double area = rectangle.getArea();
    rectangle.scale(scaleValue);

    BOOST_CHECK_CLOSE(rectangle.getArea(), area * scaleValue * scaleValue, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestCenterAfterScale)
  {
    const double width = 2.0;
    const double height = 4.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double scaleValue = 2.0;

    golovin::Rectangle rectangle(basePoint, width, height);
    rectangle.scale(scaleValue);

    BOOST_CHECK_CLOSE(rectangle.getPos().x, basePoint.x, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getPos().y, basePoint.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestFrameRectangleAfterRorate)
  {
    const double width = 2.0;
    const double height = 4.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double angle = 90;

    golovin::Rectangle rectangle(basePoint, width, height);
    rectangle.rotate(angle);

    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, width, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, height, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getPos().x, basePoint.x, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getPos().y, basePoint.y, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestCircle)

  BOOST_AUTO_TEST_CASE(TestInvalidRadius)
  {
    const double radius = -5.0;
    const golovin::point_t basePoint{0.0, 0.0};

    BOOST_CHECK_THROW(golovin::Circle circle(basePoint, radius), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestMovingInPoint)
  {
    const golovin::point_t basePoint{0.0, 0.0};
    const golovin::point_t endPoint{10.0, -10.0};
    const double radius = 5.0;

    golovin::Circle circle(basePoint, radius);
    circle.move(endPoint);

    BOOST_CHECK_CLOSE(circle.getPos().x, endPoint.x, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getPos().y, endPoint.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestMovingByOffset)
  {
    const double dX = 2.0;
    const double dY = -2.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double radius = 5.0;

    golovin::Circle circle(basePoint, radius);
    circle.move(dX, dY);

    BOOST_CHECK_CLOSE(circle.getPos().x, basePoint.x + dX, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getPos().y, basePoint.y + dY, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestRightArea)
  {
    const golovin::point_t basePoint{0.0, 0.0};
    const double radius = 1.0;
    const double rightArea = M_PI;

    golovin::Circle circle(basePoint, radius);

    BOOST_CHECK_CLOSE(circle.getArea(), rightArea, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfCircleAfterMovingInPoint)
  {
    const double baseRadius = 5.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const golovin::point_t endPoint{10.0, -10.0};

    golovin::Circle circle(basePoint, baseRadius);
    double width = circle.getFrameRect().width;
    double height = circle.getFrameRect().height;
    circle.move(endPoint);

    BOOST_CHECK_CLOSE(circle.getFrameRect().width, width, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, height, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfCircleAfterMovingByOffset)
  {
    const double baseRadius = 5.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double dX = 2.0;
    const double dY = -2.0;

    golovin::Circle circle(basePoint, baseRadius);
    double width = circle.getFrameRect().width;
    double height = circle.getFrameRect().height;
    circle.move(dX, dY);

    BOOST_CHECK_CLOSE(circle.getFrameRect().width, width, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, height, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfAreaAfterMovingInPoint)
  {
    const double radius = 5.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const golovin::point_t endPoint{10.0, -10.0};

    golovin::Circle circle(basePoint, radius);
    double area = circle.getArea();
    circle.move(endPoint);

    BOOST_CHECK_CLOSE(circle.getArea(), area, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfAreaAfterMovingByOffset)
  {
    const double radius = 5.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double dX = 2.0;
    const double dY = -2.0;

    golovin::Circle circle(basePoint, radius);
    double area = circle.getArea();
    circle.move(dX, dY);

    BOOST_CHECK_CLOSE(circle.getArea(), area, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvalidScale)
  {
    const double radius = 5.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double scaleValue = -2.0;

    golovin::Circle circle(basePoint, radius);

    BOOST_CHECK_THROW(circle.scale(scaleValue), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRightAreaAfterScale)
  {
    const double radius = 5.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double scaleValue = 2.0;

    golovin::Circle circle(basePoint, radius);
    double area = circle.getArea();
    circle.scale(scaleValue);

    BOOST_CHECK_CLOSE(circle.getArea(), area * scaleValue * scaleValue, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestCenterAfterScale)
  {
    const double radius = 5.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double scaleValue = 2.0;

    golovin::Circle circle(basePoint, radius);
    circle.scale(scaleValue);

    BOOST_CHECK_CLOSE(circle.getPos().x, basePoint.x, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getPos().y, basePoint.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestFrameRectangleAfterRorate)
  {
    const double radius = 5.0;
    const golovin::point_t basePoint{0.0, 0.0};
    const double angle = 90;

    golovin::Circle circle(basePoint, radius);
    circle.rotate(angle);

    BOOST_CHECK_CLOSE(circle.getFrameRect().height, radius * 2, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, radius * 2, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getPos().x, basePoint.x, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getPos().y, basePoint.y, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestTriangle)

  BOOST_AUTO_TEST_CASE(TestInvalidPoints)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{2.0, 2.0};

    BOOST_CHECK_THROW(golovin::Triangle triangle(pointA, pointB, pointC), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestMovingInPoint)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    const golovin::point_t endPoint{10.0, -10.0};

    golovin::Triangle triangle(pointA, pointB, pointC);
    triangle.move(endPoint);

    BOOST_CHECK_CLOSE(triangle.getPos().x, endPoint.x, ACCURACY);
    BOOST_CHECK_CLOSE(triangle.getPos().y, endPoint.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestMovingByOffset)
  {
    const double dX = 2.0;
    const double dY = -2.0;
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    golovin::Triangle triangle(pointA, pointB, pointC);
    const golovin::point_t basePoint = triangle.getPos();
    triangle.move(dX, dY);

    BOOST_CHECK_CLOSE(triangle.getPos().x, basePoint.x + dX, ACCURACY);
    BOOST_CHECK_CLOSE(triangle.getPos().y, basePoint.y + dY, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestRightArea)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{0.0, 2.0};
    const golovin::point_t pointC{1.0, 0.0};
    const double rightArea = 1;

    golovin::Triangle triangle(pointA, pointB, pointC);

    BOOST_CHECK_CLOSE(triangle.getArea(), rightArea, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfTriangleAfterMovingInPoint)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};
    const golovin::point_t endPoint{10.0,-10.0};

    golovin::Triangle triangle(pointA, pointB, pointC);
    double width = triangle.getFrameRect().width;
    double height = triangle.getFrameRect().height;
    triangle.move(endPoint);

    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, width, ACCURACY);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, height, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfTriangleAfterMovingByOffset)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};
    const double dX = 2.0;
    const double dY = -2.0;

    golovin::Triangle triangle(pointA, pointB, pointC);
    double width = triangle.getFrameRect().width;
    double height = triangle.getFrameRect().height;
    triangle.move(dX, dY);

    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, width, ACCURACY);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, height, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfAreaAfterMovingInPoint)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};
    const golovin::point_t endPoint{10.0, -10.0};

    golovin::Triangle triangle(pointA, pointB, pointC);
    double area = triangle.getArea();
    triangle.move(endPoint);

    BOOST_CHECK_CLOSE(triangle.getArea(), area, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfAreaAfterMovingByOffset)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};
    const double dX = 2.0;
    const double dY = -2.0;

    golovin::Triangle triangle(pointA, pointB, pointC);
    double area = triangle.getArea();
    triangle.move(dX, dY);

    BOOST_CHECK_CLOSE(triangle.getArea(), area, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvalidScale)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};
    const double scaleValue = -2.0;

    golovin::Triangle triangle(pointA, pointB, pointC);

    BOOST_CHECK_THROW(triangle.scale(scaleValue), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRightAreaAfterScale)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};
    const double scaleValue = 2.0;

    golovin::Triangle triangle(pointA, pointB, pointC);
    double area = triangle.getArea();
    triangle.scale(scaleValue);

    BOOST_CHECK_CLOSE(triangle.getArea(), area * scaleValue * scaleValue, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestRightCenterAfterScale)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};
    const double scaleValue = 2.0;

    golovin::Triangle triangle(pointA, pointB, pointC);
    golovin::point_t center = triangle.getPos();
    triangle.scale(scaleValue);

    BOOST_CHECK_CLOSE(triangle.getPos().x, center.x, ACCURACY);
    BOOST_CHECK_CLOSE(triangle.getPos().y, center.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestFrameRectangleAfterRorate)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};
    const double angle = 90;

    golovin::Triangle triangle(pointA, pointB, pointC);
    const double width = triangle.getFrameRect().width;
    const double height = triangle.getFrameRect().height;
    triangle.rotate(angle);

    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, width, ACCURACY);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, height, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(TestDeleteFigures)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    golovin::CompositeShape::shapePointer rectangle =
    std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
    std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
    std::make_shared<golovin::Triangle>(pointA, pointB, pointC);
    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);
    compositeShape.popBack();
    compositeShape.popBack();
    compositeShape.popBack();
    BOOST_CHECK_THROW(compositeShape.popBack(), std::logic_error);
  }

  BOOST_AUTO_TEST_CASE(TestCompositeShapeCopyAssigmentOperator)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    golovin::CompositeShape::shapePointer rectangle =
    std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
    std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
    std::make_shared<golovin::Triangle>(pointA, pointB, pointC);
    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);

    golovin::CompositeShape copyCompositeShape = compositeShape;
    golovin::rectangle_t compositeShapeFrameRect = compositeShape.getFrameRect();
    golovin::rectangle_t copyCompositeShapeFrameRect = copyCompositeShape.getFrameRect();
    double compositeShapeArea = compositeShape.getArea();
    double copyCompositeShapeArea = copyCompositeShape.getArea();

    BOOST_CHECK_CLOSE(compositeShapeFrameRect.pos.x, copyCompositeShapeFrameRect.pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeFrameRect.pos.y, copyCompositeShapeFrameRect.pos.y, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeFrameRect.width, copyCompositeShapeFrameRect.width, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeFrameRect.height, copyCompositeShapeFrameRect.height, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeArea, copyCompositeShapeArea, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestCompositeShapeMoveAssigmentOperator)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    golovin::CompositeShape::shapePointer rectangle =
    std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
    std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
    std::make_shared<golovin::Triangle>(pointA, pointB, pointC);
    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);

    golovin::rectangle_t compositeShapeFrameRect = compositeShape.getFrameRect();
    double compositeShapeArea = compositeShape.getArea();

    golovin::CompositeShape newCompositeShape = std::move(compositeShape);

    golovin::rectangle_t newCompositeShapeFrameRect = newCompositeShape.getFrameRect();
    double newCompositeShapeArea = newCompositeShape.getArea();

    BOOST_CHECK_CLOSE(compositeShapeFrameRect.pos.x, newCompositeShapeFrameRect.pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeFrameRect.pos.y, newCompositeShapeFrameRect.pos.y, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeFrameRect.width, newCompositeShapeFrameRect.width, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeFrameRect.height, newCompositeShapeFrameRect.height, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeArea, newCompositeShapeArea, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestCompositeShapeCopyConstructor)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    golovin::CompositeShape::shapePointer rectangle =
    std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
    std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
    std::make_shared<golovin::Triangle>(pointA, pointB, pointC);
    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);

    golovin::CompositeShape copyCompositeShape(compositeShape);
    golovin::rectangle_t compositeShapeFrameRect = compositeShape.getFrameRect();
    golovin::rectangle_t copyCompositeShapeFrameRect = copyCompositeShape.getFrameRect();
    double compositeShapeArea = compositeShape.getArea();
    double copyCompositeShapeArea = copyCompositeShape.getArea();

    BOOST_CHECK_CLOSE(compositeShapeFrameRect.pos.x, copyCompositeShapeFrameRect.pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeFrameRect.pos.y, copyCompositeShapeFrameRect.pos.y, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeFrameRect.width, copyCompositeShapeFrameRect.width, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeFrameRect.height, copyCompositeShapeFrameRect.height, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeArea, copyCompositeShapeArea, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestCompositeShapeMoveConstructor)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    golovin::CompositeShape::shapePointer rectangle =
    std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
    std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
    std::make_shared<golovin::Triangle>(pointA, pointB, pointC);
    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);

    golovin::rectangle_t compositeShapeFrameRect = compositeShape.getFrameRect();
    double compositeShapeArea = compositeShape.getArea();

    golovin::CompositeShape newCompositeShape(std::move(compositeShape));

    golovin::rectangle_t newCompositeShapeFrameRect = newCompositeShape.getFrameRect();
    double newCompositeShapeArea = newCompositeShape.getArea();

    BOOST_CHECK_CLOSE(compositeShapeFrameRect.pos.x, newCompositeShapeFrameRect.pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeFrameRect.pos.y, newCompositeShapeFrameRect.pos.y, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeFrameRect.width, newCompositeShapeFrameRect.width, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeFrameRect.height, newCompositeShapeFrameRect.height, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShapeArea, newCompositeShapeArea, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestCompositeShapeInvalidPushingElement)
  {
          golovin::CompositeShape testCompositeShape;

  BOOST_CHECK_THROW(testCompositeShape.pushBack(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestEmptyCompositeShapeFrameRect)
  {
    golovin::CompositeShape compositeShape;

    BOOST_CHECK_THROW(compositeShape.getFrameRect(), std::logic_error);
  }
  BOOST_AUTO_TEST_CASE(TestCompositeShapeArea)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    golovin::CompositeShape::shapePointer rectangle =
    std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
    std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
    std::make_shared<golovin::Triangle>(pointA, pointB, pointC);
    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);

    double expectedArea = rectangle->getArea() + circle->getArea() + triangle->getArea();

    BOOST_CHECK_CLOSE(compositeShape.getArea(), expectedArea, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfCompositeShapeAfterMovingInPoint)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    const golovin::point_t endPoint{10.0, -10.0};

    golovin::CompositeShape::shapePointer rectangle =
      std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
      std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
      std::make_shared<golovin::Triangle>(pointA, pointB, pointC);

    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);
    golovin::rectangle_t baseRectangle = compositeShape.getFrameRect();
    compositeShape.move(endPoint);

    BOOST_CHECK_CLOSE(compositeShape.getPos().x, endPoint.x, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShape.getPos().y, endPoint.y, ACCURACY);

    BOOST_CHECK_CLOSE(baseRectangle.width, compositeShape.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(baseRectangle.height, compositeShape.getFrameRect().height, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfCompositeShapeAfterMovingByOffset)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    const double dX = 2.0;
    const double dY = -2.0;

    golovin::CompositeShape::shapePointer rectangle =
      std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
      std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
      std::make_shared<golovin::Triangle>(pointA, pointB, pointC);

    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);
    golovin::rectangle_t baseRectangle = compositeShape.getFrameRect();
    compositeShape.move(dX, dY);

    BOOST_CHECK_CLOSE(compositeShape.getPos().x, baseRectangle.pos.x + dX, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShape.getPos().y, baseRectangle.pos.y + dY, ACCURACY);

    BOOST_CHECK_CLOSE(baseRectangle.width, compositeShape.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(baseRectangle.height, compositeShape.getFrameRect().height, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfCompositeShapeAreaAfterMovingInPoint)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    const golovin::point_t endPoint{10.0, -10.0};

    golovin::CompositeShape::shapePointer rectangle =
      std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
      std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
      std::make_shared<golovin::Triangle>(pointA, pointB, pointC);

    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);

    double baseArea = compositeShape.getArea();

    compositeShape.move(endPoint);

    BOOST_CHECK_CLOSE(baseArea, compositeShape.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfCompositeShapeAreaAfterMovingByOffset)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    const double dX = 2.0;
    const double dY = -2.0;

    golovin::CompositeShape::shapePointer rectangle =
      std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
      std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
      std::make_shared<golovin::Triangle>(pointA, pointB, pointC);

    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);

    double baseArea = compositeShape.getArea();

    compositeShape.move(dX, dY);

    BOOST_CHECK_CLOSE(baseArea, compositeShape.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvalidScalingCoefficient)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    const double coefficient = -2.0;

    golovin::CompositeShape::shapePointer rectangle =
      std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
      std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
      std::make_shared<golovin::Triangle>(pointA, pointB, pointC);

    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);

    BOOST_CHECK_THROW(compositeShape.scale(coefficient), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestCompositeShapeAreaAfterScale)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    const double coefficient = 2.0;

    golovin::CompositeShape::shapePointer rectangle =
      std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
      std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
      std::make_shared<golovin::Triangle>(pointA, pointB, pointC);

    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);
    double baseArea = compositeShape.getArea();
    compositeShape.scale(coefficient);

    BOOST_CHECK_CLOSE(baseArea * coefficient * coefficient, compositeShape.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestCompositeShapeInvalidIndex)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    golovin::CompositeShape::shapePointer rectangle =
      std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
      std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
      std::make_shared<golovin::Triangle>(pointA, pointB, pointC);
    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);

    BOOST_CHECK_THROW(compositeShape[-1], std::out_of_range);
    BOOST_CHECK_THROW(compositeShape[3], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(TestIndexTreatment)
  {
    const golovin::point_t basePointOfRectangle{0.0, 0.0};
    const double width = 5.0;
    const double height = 10.0;

    const golovin::point_t basePointOfCircle{1.1, 1.1};
    const double radius = 5.0;

    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{0.0, 2.0};

    golovin::CompositeShape::shapePointer rectangle =
      std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
      std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape::shapePointer triangle =
      std::make_shared<golovin::Triangle>(pointA, pointB, pointC);
    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    compositeShape.pushBack(triangle);

    double areaOfRectangle = rectangle->getArea();
    double areaOfCircle = circle->getArea();
    double areaOfTriangle = triangle->getArea();

    BOOST_CHECK_CLOSE(areaOfRectangle, compositeShape[0]->getArea(), ACCURACY);
    BOOST_CHECK_CLOSE(areaOfCircle, compositeShape[1]->getArea(), ACCURACY);
    BOOST_CHECK_CLOSE(areaOfTriangle, compositeShape[2]->getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestFrameRectangleAfterRorate)
  {
    const golovin::point_t basePointOfRectangle{1.1, 1.1};
    const double width = 5.5;
    const double height = 5.5;

    const golovin::point_t basePointOfCircle{5.5, 5.5};
    const double radius = 1.1;

    const double angle = 90;

    golovin::CompositeShape::shapePointer rectangle =
            std::make_shared<golovin::Rectangle>(basePointOfRectangle, width, height);
    golovin::CompositeShape::shapePointer circle =
            std::make_shared<golovin::Circle>(basePointOfCircle, radius);
    golovin::CompositeShape compositeShape;
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(circle);
    const double widthOfShape = compositeShape.getFrameRect().width;
    const double heightOfShape = compositeShape.getFrameRect().height;
    compositeShape.rotate(angle);

    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, widthOfShape, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, heightOfShape, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestPolygon)

  BOOST_AUTO_TEST_CASE(SmallCountOfPoints)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};

    golovin::point_t points[] = {pointA, pointB};

    BOOST_CHECK_THROW(golovin::Polygon(points, 2), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(TestZeroArea)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{1.0, 1.0};
    const golovin::point_t pointC{2.0, 2.0};

    golovin::point_t points[] = {pointA, pointB, pointC};

    BOOST_CHECK_THROW(golovin::Polygon(points, 3), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestNotConvex)
  {
    const golovin::point_t pointA{0.0, 0.0};
    const golovin::point_t pointB{0.0, 5.0};
    const golovin::point_t pointC{5.0, 5.0};
    const golovin::point_t pointD{1.0, 4.0};

    golovin::point_t points[] = {pointA, pointB, pointC, pointD};

    BOOST_CHECK_THROW(golovin::Polygon(points, 4), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestMovingInPoint)
  {
    const golovin::point_t pointA{-1, 1};
    const golovin::point_t pointB{2.0, 5.0};
    const golovin::point_t pointC{5.0, 4.0};
    const golovin::point_t pointD{4.0, 2.0};
    const golovin::point_t endPoint{1.0, 1.0};

    golovin::point_t points[] = {pointA, pointB, pointC, pointD};
    golovin::Polygon polygon(points, 4);
    polygon.move(endPoint);

    BOOST_CHECK_CLOSE(polygon.getPos().x, endPoint.x, ACCURACY);
    BOOST_CHECK_CLOSE(polygon.getPos().y, endPoint.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestMovingByOffset)
  {
    const double dX = 2.0;
    const double dY = -2.0;
    const golovin::point_t pointA{-1, 1};
    const golovin::point_t pointB{2.0, 5.0};
    const golovin::point_t pointC{5.0, 4.0};
    const golovin::point_t pointD{4.0, 2.0};

    golovin::point_t points[] = {pointA, pointB, pointC, pointD};
    golovin::Polygon polygon(points, 4);
    const golovin::point_t basePoint = polygon.getPos();
    polygon.move(dX, dY);

    BOOST_CHECK_CLOSE(polygon.getPos().x, basePoint.x + dX, ACCURACY);
    BOOST_CHECK_CLOSE(polygon.getPos().y, basePoint.y + dY, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestRightArea)
  {
    const golovin::point_t pointA{-1, 1};
    const golovin::point_t pointB{2.0, 5.0};
    const golovin::point_t pointC{5.0, 4.0};
    const golovin::point_t pointD{4.0, 2.0};

    golovin::point_t points[] = {pointA, pointB, pointC, pointD};
    golovin::Polygon polygon(points, 4);

    BOOST_CHECK_CLOSE(polygon.getArea(), 12, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfPolygonAfterMovingInPoint)
  {
    const golovin::point_t pointA{-1, 1};
    const golovin::point_t pointB{2.0, 5.0};
    const golovin::point_t pointC{5.0, 4.0};
    const golovin::point_t pointD{4.0, 2.0};
    const golovin::point_t endPoint{1.0, 1.0};

    golovin::point_t points[] = {pointA, pointB, pointC, pointD};
    golovin::Polygon polygon(points, 4);
    double width = polygon.getFrameRect().width;
    double height = polygon.getFrameRect().height;
    polygon.move(endPoint);

    BOOST_CHECK_CLOSE(polygon.getFrameRect().width, width, ACCURACY);
    BOOST_CHECK_CLOSE(polygon.getFrameRect().height, height, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfPolygonAfterMovingByOffset)
  {
    const golovin::point_t pointA{-1, 1};
    const golovin::point_t pointB{2.0, 5.0};
    const golovin::point_t pointC{5.0, 4.0};
    const golovin::point_t pointD{4.0, 2.0};
    const double dX = 2.0;
    const double dY = -2.0;

    golovin::point_t points[] = {pointA, pointB, pointC, pointD};
    golovin::Polygon polygon(points, 4);
    double width = polygon.getFrameRect().width;
    double height = polygon.getFrameRect().height;
    polygon.move(dX, dY);

    BOOST_CHECK_CLOSE(polygon.getFrameRect().width, width, ACCURACY);
    BOOST_CHECK_CLOSE(polygon.getFrameRect().height, height, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfAreaAfterMovingInPoint)
  {
    const golovin::point_t pointA{-1, 1};
    const golovin::point_t pointB{2.0, 5.0};
    const golovin::point_t pointC{5.0, 4.0};
    const golovin::point_t pointD{4.0, 2.0};
    const golovin::point_t endPoint{1.0, 1.0};

    golovin::point_t points[] = {pointA, pointB, pointC, pointD};
    golovin::Polygon polygon(points, 4);
    double area = polygon.getArea();
    polygon.move(endPoint);

    BOOST_CHECK_CLOSE(polygon.getArea(), area, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvarianceOfAreaAfterMovingByOffset)
  {
    const golovin::point_t pointA{-1, 1};
    const golovin::point_t pointB{2.0, 5.0};
    const golovin::point_t pointC{5.0, 4.0};
    const golovin::point_t pointD{4.0, 2.0};
    const double dX = 2.0;
    const double dY = -2.0;

    golovin::point_t points[] = {pointA, pointB, pointC, pointD};
    golovin::Polygon polygon(points, 4);
    double area = polygon.getArea();
    polygon.move(dX, dY);

    BOOST_CHECK_CLOSE(polygon.getArea(), area, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestInvalidScale)
  {
    const golovin::point_t pointA{-1, 1};
    const golovin::point_t pointB{2.0, 5.0};
    const golovin::point_t pointC{5.0, 4.0};
    const golovin::point_t pointD{4.0, 2.0};
    const double scaleValue = -2.0;

    golovin::point_t points[] = {pointA, pointB, pointC, pointD};
    golovin::Polygon polygon(points, 4);

    BOOST_CHECK_THROW(polygon.scale(scaleValue), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRightAreaAfterScale)
  {
    const golovin::point_t pointA{-1, 1};
    const golovin::point_t pointB{2.0, 5.0};
    const golovin::point_t pointC{5.0, 4.0};
    const golovin::point_t pointD{4.0, 2.0};
    const double scaleValue = 2.0;

    golovin::point_t points[] = {pointA, pointB, pointC, pointD};
    golovin::Polygon polygon(points, 4);
    const double area = polygon.getArea();
    polygon.scale(scaleValue);

    BOOST_CHECK_CLOSE(polygon.getArea(), area * scaleValue * scaleValue, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestRightCenterAfterScale)
  {
    const golovin::point_t pointA{-1, 1};
    const golovin::point_t pointB{2.0, 5.0};
    const golovin::point_t pointC{5.0, 4.0};
    const golovin::point_t pointD{4.0, 2.0};
    const double scaleValue = 2.0;

    golovin::point_t points[] = {pointA, pointB, pointC, pointD};
    golovin::Polygon polygon(points, 4);
    golovin::point_t center = polygon.getPos();
    polygon.scale(scaleValue);

    BOOST_CHECK_CLOSE(polygon.getPos().x, center.x, ACCURACY);
    BOOST_CHECK_CLOSE(polygon.getPos().y, center.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(TestFrameRectangleAfterRorate)
  {
    const golovin::point_t pointA{-1, 1};
    const golovin::point_t pointB{2.0, 5.0};
    const golovin::point_t pointC{5.0, 4.0};
    const golovin::point_t pointD{4.0, 2.0};
    const double angle = 90;

    golovin::point_t points[] = {pointA, pointB, pointC, pointD};
    golovin::Polygon polygon(points, 4);
    const double width = polygon.getFrameRect().width;
    const double height = polygon.getFrameRect().height;
    polygon.rotate(angle);

    BOOST_CHECK_CLOSE(polygon.getFrameRect().height, width, ACCURACY);
    BOOST_CHECK_CLOSE(polygon.getFrameRect().width, height, ACCURACY);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixShapeTest)

  BOOST_AUTO_TEST_CASE(MatrixShapeConstructor)
  {
    golovin::Rectangle rectangle({1.1, 2.2}, 4.0, 2.0);
    golovin::MatrixShape matrix;
    matrix.addShape(std::make_shared<golovin::Rectangle>(rectangle));
    BOOST_CHECK_CLOSE(matrix[0][0]->getArea(), rectangle.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(MatrixShapeDoNewLine)
  {
    golovin::Rectangle rectangle({1.1, 2.0}, 4, 2);
    golovin::Triangle triangle({1.1, 1.1}, {6.2, 5.1}, {10.2, 3.2});
    golovin::MatrixShape matrix;
    matrix.addShape(std::make_shared<golovin::Rectangle>(rectangle));
    matrix.addShape(std::make_shared<golovin::Triangle>(triangle));
    BOOST_CHECK_CLOSE(matrix[1][0]->getArea(), triangle.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(MatrixShapeDoNewColumns)
  {
    golovin::Rectangle rectangle({6.2, 3.1}, 4.2, 2.1);
    golovin::Circle circle({20.0, 20.0}, 1);
    golovin::MatrixShape matrix;
    matrix.addShape(std::make_shared<golovin::Rectangle>(golovin::point_t{6.2, 3.1}, 4.2, 2.1));
    matrix.addShape(std::make_shared<golovin::Circle>(golovin::point_t{20.0, 20.0}, 1));
    BOOST_CHECK_CLOSE(matrix[0][1]->getArea(), circle.getArea(), ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

