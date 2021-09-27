#include <iostream>
using namespace std;

// Shapes - circle, square
// Renderer - raster, vector

struct Renderer
{
    virtual void renderCircle(float x, float y, float radius) = 0;
};

struct VectorRenderer : Renderer
{
    void renderCircle(float x, float y, float radius) override
    {
        cout << "Rasterizing a circle of radius " << radius << endl;
    }
};

struct RasterRenderer : Renderer
{
    void renderCircle(float x, float y, float radius) override
    {
        cout << "Drawing a vector circle of radius " << radius << endl;
    }
};

struct Shape
{
protected:
    Renderer &renderer;
    Shape(Renderer &renderer) : renderer(renderer) {}

public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

struct Circle : Shape
{
    Circle(Renderer &renderer, float x, float y, float radius) : Shape(renderer), x{x}, y{y}, radius{radius} {}
    float x, y, radius;
    void draw() override
    {
        renderer.renderCircle(x, y, radius);
    }

    void resize(float factor) override
    {
        radius *= factor;
    }
};

int main(int argc, const char **argv)
{
    RasterRenderer rr;
    Circle rasterCircle{rr, 5, 5, 5};
    rasterCircle.draw();
    rasterCircle.resize(2);
    rasterCircle.draw();
    return 0;
}