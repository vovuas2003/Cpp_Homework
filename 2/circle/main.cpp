#include <iostream>
#include "point.h"
using std::cout;
using std::endl;


class Circle
{
private:
	Point mCenter;
	float mRadius;

public:
    Circle(const Point& acenter, float aradius)
    {
        mCenter = acenter;
        mRadius = aradius;
    }

    Circle()
    {
        mCenter = {0, 0};
        mRadius = 1.0f;
    }

    Circle(const Circle& circle)
    {
        mCenter = circle.mCenter;
        mRadius = circle.mRadius;
    }

    Point getCenter() const
    {
        return mCenter;
    }

    float getRadius() const
    {
        return mRadius;
    }

    void setCenter(Point c)
    {
        mCenter = c;
    }

    void setRadius(float r)
    {
        float res = r;
        if (res < 0) {
            res = 0;
        }
        mRadius = res;
    }

    float getArea() const
    {
        return 3.1415926535 * mRadius * mRadius;
    }

    float getDistance(const Point& p) const
    {
        float ro = mCenter.distance(p) - mRadius;
        if (ro < 0) {
            ro *= -1;
        }
        return ro;
    }

    bool isColliding(const Circle& c) const
    {
        bool f = false;
        float ab = mCenter.distance(c.mCenter);
        float d = mRadius - c.mRadius;
        if (d < 0) {
            d *= -1;
        }
        if ((ab > d) && (ab < (mRadius + c.mRadius))) {
            f = true;
        }
        return f;
    }

    void move(const Point& p)
    {
        mCenter = mCenter + p;
    }
};

int main()
{
	Point p = {7, -1};
	Point q = {-4, 2};
	cout << "Point p = " << p << endl;
	cout << "Point q = " << q << endl;
	cout << "p + q = " << p + q << endl;


	Circle a {{4, 1}, 3};
	Circle b;

	cout << "Circle a: center: " << a.getCenter() << " radius: " << a.getRadius() << endl;
	cout << "Circle b: center: " << b.getCenter() << " radius: " << b.getRadius() << endl;

	cout << "Area of a = " << a.getArea() << endl;
	cout << "Distance from point p to circle a = " << a.getDistance(p) << endl;



	cout << "Collisions:" << endl;
	if (a.isColliding(b))
		cout << "Yes, a is colliding b" << endl;
	else
		cout << "No, a isn't colliding b" << endl;



	cout << "Moving b by {1, 1}:" << endl;
	b.move({1, 1});
	if (a.isColliding(b))
		cout << "Yes, a is colliding b" << endl;
	else
		cout << "No, a isn't colliding b" << endl;



}
