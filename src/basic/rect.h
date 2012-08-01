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

#ifndef RECT_H_
#define RECT_H_

#include "point.h"

class Rect {

public:
    /*!
     *  Constructs a null rectangle.
     */
    Rect()
        : top_left_(Point(0, 0)), bottom_right_(Point(0, 0)) {}

    /*!
     *  Constructs a rectangle with the given \e top_left and \e bottom_right corners.
     */
    Rect(const Point& top_left, const Point& bottom_right)
        : top_left_(top_left), bottom_right_(bottom_right) {}

    /*!
     *  Constructs a rectangle with (\e x,\e y) as its top-left corner and the given \e width and \e height.
     */
    Rect(int x, int y, int width, int height)
        : top_left_(Point(x, y)),
          bottom_right_(Point(x + width, y + height)) {}

    /*!
     *  Set the top-left corner of the rectangle to the given \e position.
     *  May change the size, but will never change the bottom-right corner of the rectangle.
     */
    void setTopLeft(const Point& position) { top_left_ = position; }

    /*!
     *  Sets the top edge of the rectangle to the given \e y coordinate.
     *  May change the height, but will never change the bottom edge of the rectangle.
     */
    void setTop(int y) { top_left_.setY(y); }

    /*!
     *  Sets the left edge of the rectangle to the given \e x coordinate.
     *  May change the width, but will never change the right edge of the rectangle.
     */
    void setLeft(int x) { top_left_.setX(x); }

    /*!
     *  Set the bottom-right corner of the rectangle to the given \e position.
     *  May change the size, but will never change the top-left corner of the rectangle.
     */
    void setBottomRight(const Point& position) { bottom_right_ = position; }

    /*!
     *  Sets the bottom edge of the rectangle to the given \e y coordinate.
     *  May change the height, but will never change the top edge of the rectangle.
     */
    void setBottom(int y) { bottom_right_.setY(y); }

    /*!
     *  Sets the right edge of the rectangle to the given \e x coordinate.
     *  May change the width, but will never change the left edge of the rectangle.
     */
    void setRight(int x) { bottom_right_.setX(x); }

    /*!
     *  Returns the position of the rectangle's top-left corner.
     */
    const Point& getTopLeft()const { return top_left_; }

    /*!
     *  Returns the y-coordinate of the rectangle's top edge.
     */
    int getTop()const { return top_left_.getY(); }

    /*!
     *  Returns the x-coordinate of the rectangle's left edge.
     */
    int getLeft()const { return top_left_.getX(); }

    /*!
     *  Returns the position of the rectangle's bottom-right corner.
     */
    const Point& getBottomRight()const { return bottom_right_; }

    /*!
     *  Returns the y-coordinate of the rectangle's bottom edge.
     */
    int getBottom()const { return bottom_right_.getY(); }

    /*!
     *  Returns the x-coordinate of the rectangle's right edge.
     */
    int getRight()const { return bottom_right_.getX(); }

    /*!
     *  Moves the rectangle, leaving the top-left corner at the given \e position.
     *  The rectangle's size is unchanged.
     */
    void moveTopLeftTo(const Point& position)
    {
        bottom_right_ = bottom_right_ - top_left_ + position;
        top_left_     = position;
    }

    /*!
     *  Moves the rectangle vertically, leaving the rectangle's top edge at the given \e y coordinate.
     *  The rectangle's size is unchanged.
     */
    void moveTopTo(int y)
    {
        bottom_right_.setY(bottom_right_.getY() - top_left_.getY() + y);
        top_left_.setY(y);
    }

    /*!
     *  Moves the rectangle horizontally, leaving the rectangle's left edge at the given \e x coordinate.
     *  The rectangle's size is unchanged.
     */
    void moveLeftTo(int x)
    {
        bottom_right_.setX(bottom_right_.getX() - top_left_.getX() + x);
        top_left_.setX(x);
    }

    /*!
     *  Moves the rectangle, leaving the bottom-right corner at the given \e position.
     *  The rectangle's size is unchanged.
     */
    void moveBottomRightTo(const Point& position)
    {
        top_left_     = top_left_ - bottom_right_ + position;
        bottom_right_ = position;
    }

    /*!
     *  Moves the rectangle vertically, leaving the rectangle's bottom edge at the given \e y coordinate.
     *  The rectangle's size is unchanged.
     */
    void moveBottomTo(int y)
    {
        top_left_.setY(top_left_.getY() - bottom_right_.getY() + y);
        bottom_right_.setY(y);
    }

    /*!
     *  Moves the rectangle horizontally, leaving the rectangle's right edge at the given \e x coordinate.
     *  The rectangle's size is unchanged.
     */
    void moveRightTo(int x)
    {
        top_left_.setX(top_left_.getX() - bottom_right_.getX() + x);
        bottom_right_.setX(x);
    }

    /*!
     *  Sets the width of the rectangle to the given \e width.
     *  The right edge is changed, but not the left one.
     */
    void setWidth(int width) { setRight(getLeft() + width); }

    /*!
     *  Returns the width of the rectangle.
     */
    int getWidth()const { return getRight() - getLeft(); }

    /*!
     *  Sets the height of the rectangle to the given \e height.
     *  The bottom edge is changed, but not the top one.
     */
    void setHeight(int height) { setBottom(getTop() + height); }

    /*!
    *  Returns the height of the rectangle.
    */
    int getHeight()const { return getBottom()- getTop(); }

private:
    Point top_left_;
    Point bottom_right_;

};

#endif // RECT_H_
