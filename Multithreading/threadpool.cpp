#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <cmath>

using namespace std;
mutex g_mtx;

template <typename T>
class blockingQueue
{
private:
    mutex _mtx;
    condition_variable _cond;
    int _max_size;
    queue<T> _q;
public:
    blockingQueue(int max_size) : _max_size(max_size){}
    void push(T t)
    {
        unique_lock<mutex> lock(_mtx);

        _cond.wait(lock, [this](){ return _q.size() < _max_size; });
        _q.push(t);

        lock.unlock();
        _cond.notify_one();
    }

    T front()
    {
        unique_lock<mutex> lock(_mtx);

        _cond.wait(lock, [this](){ return !_q.empty();});

        return _q.front();
    }

    void pop()
    {
        unique_lock<mutex> lock(_mtx);
        _cond.wait(lock, [this](){ return !_q.empty(); });
        
        _q.pop();

        lock.unlock();
        _cond.notify_one();
    }

    int size()
    {
        lock_guard<mutex> lock(_mtx);
        return _q.size();
    }
};

int work(int id)
{
    unique_lock<mutex> lock(g_mtx);
    cout << "Starting " << id << endl;
    lock.unlock();

    int seconds = int((5.0 * rand())/RAND_MAX + 2);
    this_thread::sleep_for(chrono::seconds(seconds));
    return id;
}

int main()
{
    blockingQueue<shared_future<int>> vi(2);

    thread t([&](){
        for(int i = 0; i < 20; i++){
        shared_future <int> f = async(launch::async, work, i);
        vi.push(f);
    }
    });

    for(int i = 0; i < 20; i++)
    {
        shared_future<int> f = vi.front();
        int value = f.get();
        vi.pop();
        cout << "Returned : " << value << endl;
    }

    t.join();
    return 0;
}