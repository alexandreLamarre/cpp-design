/** @brief Dynamic Decorator
 * 
 * @file decorator.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Shape
{
    virtual string str() const = 0;
};

struct Circle : Shape
{
    float radius;

    Circle() {}

    Circle(float radius) : radius(radius) {}

    void resize(float factor)
    {
        radius *= factor;
    }

    string str() const override
    {
        ostringstream oss;
        oss << "A circle with radius " << radius;
        return oss.str();
    }
};

struct Square : Shape
{
    float side;

    Square() {}
    Square(float side) : side(side) {}

    string str() const override
    {
        ostringstream oss;
        oss << "A square with side " << side;
        return oss.str();
    }
};

struct ColoredShape : Shape
{
    Shape &shape;
    string color;

    ColoredShape(Shape &shape, const string &color) : shape(shape), color(color) {}

    string str() const override
    {
        ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

struct TransparentShape : Shape
{
    Shape &shape;
    uint8_t transparency;

    TransparentShape(Shape &shape, uint8_t transparency) : shape(shape), transparency(transparency) {}

    string str() const override
    {
        ostringstream oss;
        oss << shape.str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f << "% transparency";
        return oss.str();
    }
};

int main(int argc, const char **argv)
{
    Square square{5};
    ColoredShape redSquare(square, "red");
    cout << square.str() << endl
         << redSquare.str() << endl;

    TransparentShape mySquare(redSquare, 51);
    cout << mySquare.str() << endl;
    return 0;
}