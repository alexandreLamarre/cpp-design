#include <iostream>
#include <vector>

using namespace std;

class Rectangle
{
protected:
    int width, height;
public:
    Rectangle(int width, int height) : width(width), height(height) {}

    int getWidth() const {
        return width;
    }

    virtual void setWidth(int width) {
        Rectangle::width = width;
    }

    int getHeight() const {
        return height;
    }

    virtual void setHeight(int height) {
        Rectangle::height = height;
    }

    int area() const {return width * height;}
};

void process(Rectangle& r)
{
    int w  = r.getWidth();
    r.setHeight(10);

    cout << "expected area = " << (w*10)
        << ", got " << r.area() << endl;
}

/**
 * This implementation violates the Liskov principle:
 *  Can't process square as a Rectangle
 *
 *  Want to be able to substitute derived classes anywhere
 *  the original class is used
 */
class Square : public Rectangle
{
public:
    Square(int size): Rectangle(size, size) {}

    void setWidth(int width) override {
        this->width = this->height = height;
    }

    void setHeight(int height) override {
        this->width = this->height = height;
    }
};

int main(){
    Rectangle r{3,4};
    process(r);

    Square s{5};
    process(s);
    return 0;
}