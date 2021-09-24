#include <cmath>
#include <iostream>

using namespace std;

enum class PointType
{
    cartesian,
    polar
};

class Point
{
private:
    //friend class PointFactory; // Violates the Open/Closed Principle
    //Point(float x, float y) : x(x), y(y) {}

public:
    Point(float x, float y) : x(x), y(y) {}
    float x, y;

    friend ostream &operator<<(ostream &os, const Point &point)
    {
        os << "x " << point.x << " y " << point.y << endl;
        return os;
    }
};

struct PointFactory
{
    static Point NewCartesian(float x, float y)
    {
        return {x, y};
    }

    static Point NewPolar(float r, float theta)
    {
        return {r * cos(theta), r * sin(theta)};
    }
};

int main(int argc, const char **argv)
{
    auto p = PointFactory::NewPolar(1, 1);
    cout << p << endl;
    return 0;
}