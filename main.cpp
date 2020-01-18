#include "mySizeAvl.h"
using namespace sizeavl;
int main()
{
    Node<int> *root = nullptr;

    root = insert(root, 1, 1);
    root = insert(root, 2, 2);
    root = insert(root, 3, 3);
    root = insert(root, 4, 4);
    root = insert(root, 5, 5);
    root = insert(root, 6, 6);
    root = insert(root, 7, 7);
    root = insert(root, 8, 8);
    root = insert(root, 9, 9);

    show(root);

    root = deleteNode(root, 4);
    root = deleteNode(root, 4);

    show(root);

    return 0;
}