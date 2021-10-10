#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;

enum class OutputFormat
{
    markdown,
    html,
};

struct ListStrategy
{
    virtual void start(ostringstream &oss) {}
    virtual void addListItem(ostringstream &oss, const string &item) = 0;
    virtual void end(ostringstream &oss) {}
};

struct MarkdownListStrategy : ListStrategy
{
    void addListItem(ostringstream &oss, const string &item) override
    {
        oss << " * " << item << endl;
    }
};

struct HtmlListStrategy : ListStrategy
{
    void start(ostringstream &oss) override
    {
        oss << "<ul>" << endl;
    }

    void end(ostringstream &oss) override
    {
        oss << "</ul>" << endl;
    }

    void addListItem(ostringstream &oss, const string &item) override
    {
        oss << "<li>" << item << "</li>" << endl;
    }
};

struct TextProcessor
{
    void clear()
    {
        oss.str("");
        oss.clear();
    }
    void appendList(const vector<string> &items)
    {
        listStrategy->start(oss);
        for (auto &item : items)
            listStrategy->addListItem(oss, item);
        listStrategy->end(oss);
    }
    void setOutputFormat(const OutputFormat &format)
    {
        switch (format)
        {
        case OutputFormat::markdown:
            listStrategy = make_unique<MarkdownListStrategy>();
            /* code */
            break;
        case OutputFormat::html:
            listStrategy = make_unique<HtmlListStrategy>();
            break;
        default:
            break;
        }
    }
    string str() const { return oss.str(); }

private:
    ostringstream oss;
    unique_ptr<ListStrategy> listStrategy;
};

int main(int argc, char const *argv[])
{
    // markdown
    TextProcessor tp;
    tp.setOutputFormat(OutputFormat::markdown);
    tp.appendList({"foo", "bar", "baz"});
    cout << tp.str() << endl;

    // html
    tp.clear();
    tp.setOutputFormat(OutputFormat::html);
    tp.appendList({"foo", "bar", "baz"});
    cout << tp.str() << endl;

    getchar();
    return 0;
}
