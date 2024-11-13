#include <stdio.h>

#include "tree.h"
#include "compare.h"
#include "ascii.h"

int main(void)
{

    Tree * tree = NULL;

    tree = TreeAdd(tree, 0, "NBA CHAMP?", CompareLess);

    tree->left = TreeAdd(tree->left, 0, "MVP?", CompareLess);
    tree->right = TreeAdd(tree->right, 1, "MVP?", CompareLess);

    tree->left->left = TreeAdd(tree->left->left, 0, "High?", CompareLess);

    tree->left->left->left = TreeAdd(tree->left->left->left, 0, "King of 4th quarters?", CompareLess);
    tree->left->left->right = TreeAdd(tree->left->left->right, 1, "Ultimate Dunker?", CompareLess);

    tree->left->left->left->left = TreeAdd(tree->left->left->left->left, 0, "Dunno", CompareLess);
    tree->left->left->left->right = TreeAdd(tree->left->left->left->right, 1, "Isaiah Thomas", CompareLess);

    tree->left->left->right->left= TreeAdd(tree->left->left->left->right->left, 0, "Dunno", CompareLess);
    tree->left->left->right->right= TreeAdd(tree->left->left->left->right->right, 1, "Vince Carter", CompareLess);

    tree->left->right = TreeAdd(tree->left->right, 1, "High?", CompareLess);
    tree->left->right->left = TreeAdd(tree->left->right->left, 0, "Dribble King?", CompareLess);
    tree->left->right->left->left = TreeAdd(tree->left->right->left->left, 0, "Dunno", CompareLess);
    tree->left->right->left->right = TreeAdd(tree->left->right->left->right, 1, "Allen Iverson", CompareLess);
    tree->left->right->right = TreeAdd(tree->left->right->right, 1, "Karl Malone", CompareLess);


    tree->right->left = TreeAdd(tree->right->left, 0, "Rajon Rondo", CompareLess);
    tree->right->right = TreeAdd(tree->right->right, 1, "Michael Jordan", CompareLess);

    TreeDump(tree, "out.dot", tree);

    Akinator(tree);

    TreeDtor(tree);

}
