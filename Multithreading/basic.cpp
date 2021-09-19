#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

/**
 * @brief New workload for a thread
 * 
 */
void work()
{
    for(int i = 0; i < 10; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "Loop" << i << endl;
    }
}

/**
 * @brief Unordered (non-synced, non-locked) threading workload
 * 
 * @return int exit status
 */
int main()
{
    thread t1(work);
    thread t2(work);

    t1.join();
    t2.join();

    return 0;
}