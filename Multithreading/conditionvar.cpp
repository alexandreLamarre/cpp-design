#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

/**
 * @brief Naive thread waiting
 * 
 * @return int exit status
 */
int main()
{
    condition_variable condition;
    mutex mtx;
    bool ready = false;

    thread t1([&](){
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout << "t1 acquiring lock" << endl;
        unique_lock<mutex> lock(mtx);
        cout << "t1 acquired lock" << endl;
        ready = true;
        lock.unlock();
        cout << "t1 released the lock" << endl;
        condition.notify_one();
    });

    t1.join();
    cout << "Mean thread acquiring lock" << endl;
    unique_lock<mutex> lock(mtx);
    cout << "Main thread acquired lock" << endl;
    cout << "Waiting for lock" << endl;
    condition.wait(lock, [&](){ return ready; });
    cout << "Done waiting for the lock" << endl;

    cout << "ready " << ready << endl;

    return 0;
}