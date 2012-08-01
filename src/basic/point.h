/*
 * This file is a part of railroad-diagram-generator
 *
 * Copyright (C) 2012 xStone <chen_fu_hua@126.com>
 *
 * This program is free software; you can redestribute it and/or modify it
 * under terms of GNU General Public License by Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY. See GPL for more details.
 */

#ifndef POINT_H_
#define POINT_H_

class Point {

public:
    /*!
     *  Constructs a null point with coordinates (0, 0).
     */
    Point()
        : x_(0), y_(0) {}

    /*!
     *  Constructs a point with the given coordinates (\e x,\e y).
     */
    Point(int x, int y)
        : x_(x), y_(y) {}

    /*!
     *  Sets the x coordinate of this point to the given \e x coordinate.
     */
    void setX(int x) { x_ = x; }

    /*!
     *  Returns the x coordinate of this point.
     */
    int getX()const { return x_; }

    /*!
     *  Sets the y coordinate of this point to the given \e y coordinate.
     */
    void setY(int y) { y_ = y; }

    /*!
     *  Returns the y coordinate of this point.
     */
    int getY()const { return y_; }

private:
    int x_;
    int y_;

public:
    /*!
     *  Returns a Point object that is the sum of the given points \e p1 and \e p2;
     *  each component is added separately.
     */
    friend Point operator+(const Point& p1, const Point& p2)
    {
        return Point(p1.x_ + p2.x_, p1.y_ + p2.y_);
    }

    /*!
     *  Returns a Point object that is formed by subtracting \e p2 from \e p1;
     *  each component is subtracted separately.
     */
    friend Point operator-(const Point& p1, const Point& p2)
    {
        return Point(p1.x_ - p2.x_, p1.y_ - p2.y_);
    }

    /*!
     *  Returns true if \e p1 and \e p2 are equal; otherwise returns false.
     */
    friend bool operator==(const Point& p1, const Point& p2)
    {
        return p1.x_ == p2.x_ && p1.y_ == p2.y_;
    }

};

#endif // POINT_H_
