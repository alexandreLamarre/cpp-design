/**
 * @file classic-visitor.cpp
 * @author your name (you@domain.com)
 * @brief Double dispatcher approach 
 * @version 0.1
 * @date 2021-10-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct DoubleExpression;
struct AdditionExpression;
struct SubstractionExpression;

struct ExpressionVisitor
{
    virtual void visit(DoubleExpression *de) = 0;
    virtual void visit(AdditionExpression *ae) = 0;
    virtual void visit(SubstractionExpression *se) = 0;
};

struct ExpressionPrinter : ExpressionVisitor
{
    ostringstream oss;
    string str() const { return oss.str(); }
    void visit(DoubleExpression *de) override;
    void visit(AdditionExpression *ae) override;
    void visit(SubstractionExpression *se) override;
};

struct Expression
{
    virtual void accept(ExpressionVisitor *visitor) = 0;
};

struct DoubleExpression : Expression
{
    double value;
    explicit DoubleExpression(const double value)
        : value{value} {}

    void accept(ExpressionVisitor *visitor) override
    {
        visitor->visit(this);
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

    void accept(ExpressionVisitor *visitor) override
    {
        visitor->visit(this);
    }
};

struct SubstractionExpression : Expression
{
    Expression *left, *right;

    SubstractionExpression(Expression *const left, Expression *const right)
        : left{left}, right{right} {}

    ~SubstractionExpression()
    {
        delete left;
        delete right;
    }

    void accept(ExpressionVisitor *visitor) override
    {
        visitor->visit(this);
    }
};

void ExpressionPrinter::visit(DoubleExpression *de)
{
    oss << de->value;
}

void ExpressionPrinter::visit(AdditionExpression *ae)
{
    bool needBraces = dynamic_cast<SubstractionExpression *>(ae->right);
    if (needBraces)
        oss << "(";
    ae->left->accept(this);
    oss << " + ";
    ae->right->accept(this);
    if (needBraces)
        oss << ")";
}

void ExpressionPrinter::visit(SubstractionExpression *se)
{
    bool needBraces = dynamic_cast<SubstractionExpression *>(se->right);
    if (needBraces)
        oss << "(";
    se->left->accept(this);
    oss << " - ";
    se->right->accept(this);
    if (needBraces)
        oss << ")";
}
int main(int argc, const char **argv)
{
    auto e = new AdditionExpression{
        new DoubleExpression{1},
        new SubstractionExpression{
            new DoubleExpression{2},
            new DoubleExpression{3}}};
    ExpressionPrinter ep;
    ep.visit(e);
    cout << ep.str() << endl;
    return 0;
}