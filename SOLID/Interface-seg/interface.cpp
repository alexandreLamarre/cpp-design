//
// Created by Alexandre Lamarre on 2021-09-17.
//

#include <iostream>
#include <string>

using namespace std;


struct Document;

// struct IMachine
// {
//     virtual void print(Document& doc) = 0;
//     virtual void scan(Document &doc) = 0;
//     virtual void fax(Document &doc) = 0;
// };

// struct MFP : IMachine
// {
//     void print(Document &doc) override {

//     }
//     void scan(Document &doc) override {

//     }
//     void fax(Document &doc) override {

//     }
// }

// struct Scanner : IMachine
// {
//     void print(Document &doc) override {

//     }
//     void scan(Document &doc) override {
//         // ok
//     }
//     void fax(Document &doc) override {

//     }
// }

struct IPrinter
{
    virtual void print(Document& doc) = 0;
};

struct IScanner
{
    virtual void scan(Document& doc) = 0;
};

struct IFax
{
    virtual void fax(Document& doc) = 0;
};

struct IMachine : IPrinter, IScanner {};

struct Printer : IPrinter
{
    void print(Document &doc) override{

    }
};

struct Scanner : IScanner
{
    void scan(Document &doc) override{

    }
};

struct Machine : IMachine
{
    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner) {}

    void print(Document &doc) override {
        printer.print(doc);
    }

    void scan(Document &doc) override {
        scanner.scan(doc);
    }
};

int main ()
{
    return 0;
}