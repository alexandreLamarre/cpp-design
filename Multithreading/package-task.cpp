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
    packaged_task<double(int)> task1(calculate_pi);

    future<double> future1 = task1.get_future();

    thread t1(move(task1), 1E8);
    try
    {
        double result = future1.get();
        cout << setprecision(15) << result << endl;
    }
    catch(const exception &e)
    {
        cout << "ERROR!" << e.what() << endl;
    }

    t1.join();
    return 0;
}