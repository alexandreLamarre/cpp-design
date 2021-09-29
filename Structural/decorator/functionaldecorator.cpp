#include <iostream>
#include <string>
#include <functional>

using namespace std;

struct Logger
{
    function<void()> func;
    string name;
    Logger(const function<void()> &func, const string &name) : func(func), name(name) {}

    void operator()() const
    {
        cout << "Entering " << name << endl;
        func();
        cout << "Exiting " << name << endl;
    }
};

template <typename Func>
struct Logger2
{
    Func func;
    string name;
    Logger2(Func &func, const string &name) : func(func), name(name) {}

    void operator()() const
    {
        cout << "Entering " << name << endl;
        func();
        cout << "Exiting " << name << endl;
    }
};

/**
 * @brief Lets you infer the type of func from argument
 * 
 * @tparam Func 
 * @param func 
 * @param name 
 * @return auto 
 */
template <typename Func>
auto make_logger2(Func func, const string &name)
{
    return Logger2<Func>{func, name};
}

double add(double a, double b)
{
    cout << a << " + " << b << " = " << (a + b) << endl;
    return a + b;
}

template <typename>
struct Logger3;

template <typename R, typename... Args>
struct Logger3<R(Args...)>
{
    function<R(Args...)> func;
    string name;

    Logger3(const function<R(Args...)> &func, const string &name) : func(func), name(name) {}
    R operator()(Args... args)
    {
        cout << "Entering " << name << endl;
        R result = func(args...);
        cout << "Exiting" << name << endl;
        return result;
    }
};

template <typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const string &name)
{
    return Logger3<R(Args...)>(
        function<R(Args...)>(func),
        name);
}

int main(int argc, const char **argv)
{
    Logger([]()
           { cout << "Hello" << endl; },
           "Hello function");

    auto log = make_logger2([]()
                            { cout << "Hello" << endl; },
                            "Hello function");
    log();

    auto logged_add = make_logger3(add, "Add");
    auto result = logged_add(2, 3);
    cout << "Final result " << result << endl;
    return 0;
}