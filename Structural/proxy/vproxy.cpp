#include <iostream>
#include <string>

using namespace std;

struct Image
{
    virtual void draw() = 0;
};

struct BitMap : Image
{
    BitMap(const string &filename)
    {
        cout << "Loading bitmap from " << filename << endl;
    }

    void draw() override
    {
        cout << "Drawing bitmap " << endl;
    }
};

struct LazyBitMap : Image
{
    LazyBitMap(const string &filename) : filename(filename)
    {
    }

    void draw() override
    {
        if (!bmp)
        {
            bmp = new BitMap(filename);
        }
        bmp->draw();
    }

private:
    string filename;
    BitMap *bmp{nullptr};
};

int main(int argc, const char **argv)
{
    //BitMap and LazyBitMap are interchangeable in this case
    LazyBitMap bpm{"pokemon.png"};
    bpm.draw();
    return 0;
}