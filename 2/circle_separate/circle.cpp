#include <iostream>
#include "point.h"
#include "circle.h"

Circle::Circle(const Point& acenter, float aradius)
    {
        mCenter = acenter;
        mRadius = aradius;
    }

Circle::Circle()
    {
        mCenter = {0, 0};
        mRadius = 1.0f;
    }

Circle::Circle(const Circle& circle)
    {
        mCenter = circle.mCenter;
        mRadius = circle.mRadius;
    }

    Point Circle::getCenter() const
    {
        return mCenter;
    }

    float Circle::getRadius() const
    {
        return mRadius;
    }

    void Circle::setCenter(Point c)
    {
        mCenter = c;
    }

    void Circle::setRadius(float r)
    {
        float res = r;
        if (res < 0) {
            res = 0;
        }
        mRadius = res;
    }

    float Circle::getArea() const
    {
        return 3.1415926535 * mRadius * mRadius;
    }

    float Circle::getDistance(const Point& p) const
    {
        float ro = mCenter.distance(p) - mRadius;
        if (ro < 0) {
            ro *= -1;
        }
        return ro;
    }

    bool Circle::isColliding(const Circle& c) const
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

    void Circle::move(const Point& p)
    {
        mCenter = mCenter + p;
    }
