#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

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

int main(){
    blockingQueue<int> qu(5);
    thread t1([&](){
        for(int i = 0; i < 10; i++)
        {
            qu.push(i);
            cout << "pushing " << i << endl;
            cout << "queue size is " << qu.size() << endl;
        }
    });
    thread t2([&](){
        for(int i = 0; i < 10; i++)
        {
            auto item = qu.front();
            qu.pop();
            cout << "consumed " << item << endl;
        }
    });

    t1.join();
    t2.join();

    return 0;
}