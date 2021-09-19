#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

/**
 * @brief Using mutexes to control access to shared memory in threads
 * 
 * @return int exit status
 */
int main()
{
    int count = 0;
    const int ITERATIONS = 1E6;

    mutex mtx;

    auto func = [&](){
        for(int i = 0; i < ITERATIONS; i++){
            mtx.lock();
            ++count;
            mtx.unlock();
        }
    };

    thread t1(func);
    thread t2(func);


    t1.join();
    t2.join();

    cout << count << endl;
}