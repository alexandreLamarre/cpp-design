// visitor examples for design patterns c++ book
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

struct Expression
{
    virtual void print(ostringstream &oss) = 0;
};

struct DoubleExpression : Expression
{
    double value;
    explicit DoubleExpression(const double value)
        : value{value} {}

    void print(ostringstream &oss) override
    {
        oss << value;
    }
};

struct AdditionExpression : Expression
{
    Expression *left, *right;

    AdditionExpression(Expression *const left, Expression *const right)
        : left{left}, right{right} {}

    ~AdditionExpression()
    {
        delete left;
        delete right;
    }

    void print(ostringstream &oss) override
    {
        oss << "(";
        left->print(oss);
        oss << "+";
        right->print(oss);
        oss << ")";
    }
};
struct ExpressionPrinter
{
    ostringstream oss;
    void print(Expression *e)
    {
        if (auto de = dynamic_cast<DoubleExpression *>(e))
        {
            oss << de->value;
        }
        else if (auto ae = dynamic_cast<AdditionExpression *>(e))
        {
            oss << "(";
            print(ae->left);
            oss << "+";
            print(ae->right);
            oss << ")";
        }
    }

    string str() const
    {
        return oss.str();
    }
};
int main()
{
    auto e = new AdditionExpression{
        new DoubleExpression{1},
        new AdditionExpression{
            new DoubleExpression{2},
            new DoubleExpression{3}}};
    ExpressionPrinter ep;
    ep.print(e);
    cout << ep.str() << endl;
}