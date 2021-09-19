#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

/**
 * @brief Using atomic to make accessesing, increments and copy backs to int 
 *        'behavate atomically', so we don't run into shared access problem
 * 
 * @return int 
 */
int main()
{
    atomic<int> count = 0;
    const int ITERATIONS = 1E6;

    thread t1([&count](){
        for(int i = 0; i < ITERATIONS; i++){
            ++count;
        }
    });
    thread t2([&count](){
        for(int i = 0; i < ITERATIONS; i++){
            ++count;
        }
    });


    t1.join();
    t2.join();

    cout << count << endl;
}