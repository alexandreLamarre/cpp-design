#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>

using namespace std;

/**
 * @brief Use's euler's sum for calculating pi
 * 
 * @param terms number of terms in the sum
 * @return double : approximation of pi
 */
double calculate_pi(int terms)
{
    double sum = 0.0;
    
    if (terms < 1)
    {
        throw runtime_error("Terms cannot be less than 1");
    }

    for (int i = 0; i < terms; i++)
    {
        int sign = i % 2 == 0? 1 : -1;
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }

    return sum * 4;
}

/**
 * @brief Main function testing promise / future /exception
 * 
 * @return int exit status
 */
int main()
{
    promise<double> prom;

    auto do_calc = [&](int terms) {
        try
        {
            auto result = calculate_pi(terms);
            prom.set_value(result);
        }
        catch(...)
        {
            prom.set_exception(current_exception());
        }
    };

    thread t1(do_calc, 1E10);

    future<double> future = prom.get_future();

    try 
    {
        cout << setprecision(15) << future.get() << endl;
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }

    t1.join();

    return 0;
}