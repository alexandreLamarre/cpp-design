#include <string>
#include <iostream>

using namespace std;

struct Pingable
{
    virtual wstring ping(const wstring &message) = 0;
};

struct Pong : Pingable
{
    wstring ping(const wstring &message) override
    {
        return message + L"pong";
    }
};

void tryit(Pingable &pp)
{
    wcout << pp.ping(L"ping") << "\n";
}

int main(int argc, const char **argv)
{
    Pong pp;
    for (size_t i = 0; i < 3; i++)
    {
        tryit(pp);
    }
    return 0;
}