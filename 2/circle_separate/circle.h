#include "point.h"

class Circle
{
private:
	Point mCenter;
	float mRadius;

public:
    Circle(const Point& acenter, float aradius);
    Circle();
    Circle(const Circle& circle);
    Point getCenter() const;
    float getRadius() const;
    void setCenter(Point c);
    void setRadius(float r);
    float getArea() const;
    float getDistance(const Point& p) const;
    bool isColliding(const Circle& c) const;
    void move(const Point& p);
};
