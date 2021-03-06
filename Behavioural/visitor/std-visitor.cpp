#include <iostream>
#include <string>
#include <variant>

using namespace std;

struct AddressPrinter
{
    void operator()(const string &house_name) const
    {
        cout << "A house called " << house_name << "\n";
    }
    void operator()(const int house_number) const
    {
        cout << "House number " << house_number << "\n";
    }
};

int main(int argc, const char **argv)
{
    variant<string, int> house;
    // house = 123;
    house = "Montefiore Castle";
    AddressPrinter ap;
    //std::visit(ap, house);
    std::visit([](auto &arg)
               {
                   using T = decay_t<decltype(arg)>;

                   if constexpr (is_same_v<T, string>)
                   {
                       cout << "A house called " << arg << "\n";
                   }
                   else
                   {
                       cout << "House number " << arg << "\n";
                   }
               },
               house);
    return 0;
}