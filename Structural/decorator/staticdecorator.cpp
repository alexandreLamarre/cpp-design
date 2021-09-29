/** @brief Static Decorator
 * @file staticdecorator.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-29
 * 
 * @copyright Copyright (c) 2021
 * 
 * 
 * @warning Requires C++20
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

// Use Mixin inheritance (specific c++ feature),  perfect forwarding

template <typename T>
concept isAShape = std::is_base_of<Shape, T>::value; //concept to check typename is a Shape

template <isAShape T>
struct ColoredShape2 : T
{
    string color;

    ColoredShape2() {}

    template <typename... Args>
    ColoredShape2(const string &color, Args... args) : T(std::forward<Args>(args)...), color(color) {}
    string str() const override
    {
        ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};

template <isAShape T>
struct TransparentShape2 : T
{
    uint8_t transparency;

    TransparentShape2() {}

    template <typename... Args>
    TransparentShape2(uint8_t transparency, Args... args) : T(std::forward<Args>(args)...), transparency(transparency) {}
    string str() const override
    {
        ostringstream oss;
        oss << T::str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f << "% transparency";
        return oss.str();
    }
};

int main(int argc, const char **argv)
{
    ColoredShape2<Circle> greenCircle{"green", 5};
    cout << greenCircle.str() << endl;

    TransparentShape2<ColoredShape2<Square>> blueInvisbleSquare(0, "blue", 10);
    cout << blueInvisbleSquare.str() << endl;
    blueInvisbleSquare.color = "light blue";
    blueInvisbleSquare.side = 21;
    cout << blueInvisbleSquare.str() << endl;
    return 0;
}