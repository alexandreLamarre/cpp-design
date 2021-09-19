#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

/**
 * @brief Work function with pass by reference
 * 
 * @param count variable to increment
 * @param mtx mutex
 */
void work(int &count, mutex &mtx){

    for(int i = 0; i < 1E6; i++)
    {
        lock_guard<mutex> guard(mtx);
        ++count;
    }

}

/**
 * @brief 
 * 
 * @return int 
 */
int main(){
    int count = 0;
    mutex mtx;

    thread t1(work, ref(count), ref(mtx));
    thread t2(work, ref(count), ref(mtx));

    t1.join();
    t2.join();

    cout << count << endl;
}