#include <iostream>
#include <string>
#include <coroutine>

template <typename T>
struct BinaryTree;

using namespace std;

template <typename T>
struct Node
{
    T value = T();
    Node<T> *left{nullptr}, *right{nullptr}, *parent{nullptr};
    BinaryTree<T> *tree{nullptr};

    Node(T value) : value(value) {}

    Node(T value, Node<T> *left, Node<T> *right) : value(value), left(left), right(right)
    {
        this->left->tree = this->right->tree;
        this->left->parent = this->right->parent = this;
    }

    void setTree(BinaryTree<T> *t)
    {
        tree = t;
        if (left)
            left->setTree(t);
        if (right)
            right->setTree(t);
    }
    ~Node()
    {
        if (left)
            delete left;
        if (right)
            delete right;
    }
};

template <typename T>
struct BinaryTree
{
    Node<T> *root{nullptr};

    BinaryTree(Node<T> *root) : root(root), preorder(*this)
    {
        root->setTree(this);
    }

    ~BinaryTree()
    {
        if (root)
            delete root;
    }

    /**
     * @brief Preorder iterator object
     * 
     * @tparam U 
     */
    template <typename U>
    struct PreOrderIterator
    {
        Node<U> *current;

        explicit PreOrderIterator(Node<U> *current)
            : current(current)
        {
        }

        bool operator!=(const PreOrderIterator<U> &other)
        {
            return current != other.current;
        }

        // no continuations in C++ (unlike C#)
        PreOrderIterator<U> &operator++()
        {
            if (current->right)
            {
                current = current->right;
                while (current->left)
                    current = current->left;
            }
            else
            {
                Node<T> *p = current->parent;
                while (p && current == p->right)
                {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }

        Node<U> &operator*() { return *current; }
    };
    /**
     * @brief Make our preorder iterator the default iterator
     * 
     */
    typedef PreOrderIterator<T> iterator;
    iterator begin()
    {
        Node<T> *n = root;
        if (n)
            while (n->left)
                n = n->left;
        return iterator{n};
    }

    iterator end()
    {
        return iterator{nullptr};
    }

    class PreOrderTraversal
    {
        BinaryTree &tree;

    public:
        PreOrderTraversal(BinaryTree &tree) : tree(tree) {}
        iterator begin() { return tree.begin(); }
        iterator end() { return tree.end(); }
    } preorder;

    generator<Node<T> *> postOrder()
    {
        return postOrderImpl(root);
    }

private:
    generator<Node<T> *> postOrderImpl(Node<T> *node)
    {
        if (node)
        {
            for (auto x : postOrderImpl(node->left))
                co_yield x;
            for (auto y : postOrderImpl(node->right))
                co_yield y;
            co_yield node;
        }
    }
};

int main(int argc, char const *argv[])
{
    BinaryTree<string> family{
        new Node<string>{"me",
                         new Node<string>{"mother", new Node<string>{"mother's mother"}, new Node<string>{"mother's father"}},
                         new Node<string>{"father"}}};

    for (auto it = family.begin(); it != family.end(); ++it)
    {
        cout << (*it).value << endl;
    }

    for (auto it : family.postOrder())
        cout << (*it).value << endl;
    return 0;
}
