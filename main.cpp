#include <stdio.h>

#include "tree.h"
#include "compare.h"

int main(int argc, char * argv[])
{

    Tree * tree = NULL;

    tree = TreeAdd(tree, 7, CompareLess);
    tree = TreeAdd(tree, 8, CompareLess);
    tree = TreeAdd(tree, 6, CompareLess);
    tree = TreeAdd(tree, 5, CompareLess);

    // TreeSearch(tree, 6);
    TreePrint(tree, 0);
    TreeDump(tree, "out.dot", tree->left->left);
    TreeDtor(tree);

}
