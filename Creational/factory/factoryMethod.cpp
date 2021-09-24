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
    Point(float x, float y) : x(x), y(y) {}

public:
    float x, y;

    static Point NewCartesian(float x, float y)
    {
        return {x, y};
    }

    static Point NewPolar(float r, float theta)
    {
        return {r * cos(theta), r * sin(theta)};
    }

    friend ostream &operator<<(ostream &os, const Point &point)
    {
        os << "x " << point.x << " y " << point.y << endl;
        return os;
    }
};

int main(int argc, const char **argv)
{
    auto p = Point::NewCartesian(5, M_PI_4);
    cout << p << endl;
    return 0;
}