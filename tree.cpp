#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

Tree * TreeCtor(int val)
{
    Tree * tree = (Tree*) calloc(1, sizeof(Tree));
    tree->field = val;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

void TreeDtor(Tree * tree)
{
    if (tree)
    {
        TreeDtor(tree->left);
        TreeDtor(tree->right);
    }

    free(tree);
}

Tree * TreeAdd(Tree * tree, int val, CompareFunc_t * compare)
{
    if (!tree)
    {
        return TreeCtor(val);
    }
    if (compare(val, tree->field)) tree->left  = TreeAdd(tree->left, val, compare);
    else                           tree->right = TreeAdd(tree->right, val, compare);

    return tree;

}

Tree * TreePrint(Tree * tree, int height)
{
    if (!tree)
        return tree;

    printf("tree[%p], %*stree.field = %d, tree.left[%p] tree.right[%p]\n", tree, height*4, "", tree->field, tree->left, tree->right);
    TreePrint(tree->left, height + 1);
    TreePrint(tree->right, height + 1);
    return tree;
}

Tree * TreePrintBracket(Tree * tree, int order)
{
    if (!tree)
        return tree;

    printf("( ");

    if (order == PRE_ORDER) printf("%d ", tree->field);
    TreePrintBracket(tree->left, order);
    if (order == IN_ORDER) printf("%d ", tree->field);
    TreePrintBracket(tree->right, order);
    if (order == POST_ORDER) printf("%d ", tree->field);

    printf(") ");

    return tree;
}

Tree * TreeSearchFunc(Tree * tree, int val)
{
    if (!tree) return NULL;
    if (tree->field == val) return tree;

    Tree * left = TreeSearchFunc(tree->left, val);
    if (left) return left;
    Tree * right = TreeSearchFunc(tree->right, val);
    if (right) return right;
    return NULL;
}

int TreeSearch(Tree * tree, int val)
{
    Tree * tr = TreeSearchFunc(tree, val);
    if (tr->field == val)
        return printf("tree[%p], tree.field = %d, tree.left[%p], tree.right[%p]\n", tree, tree->field, tree->left, tree->right);
    return -printf("not found :(\n");
}

Tree * TreeDumpFunc(Tree * tree, FILE * Out, Tree * sel)
{
    unsigned int color = 0XE0D0FF;
    if (tree == sel) color = 0XFFF0F0;

    if (!tree)
        return tree;

    fprintf(Out, "tree%p [shape = Mrecord; label = \"{ adr = %p | field = %d  | { left = %p | right = %p } }\"; style = filled; fillcolor = \"#%06X\"];\n",
        tree, tree, tree->field, tree->left, tree->right, color);
    if (tree->left)
        fprintf(Out, "tree%p -> tree%p\n", tree, tree->left);

    if (tree->right)
        fprintf(Out, "tree%p -> tree%p\n", tree, tree->right);

    TreeDumpFunc(tree->left, Out, sel);
    TreeDumpFunc(tree->right, Out, sel);

    return tree;
}

Tree * TreeDump(Tree * tree, const char * FileName, Tree * sel)
{
    FILE * Out = fopen(FileName, "wb");
    fprintf(Out, "digraph\n{\n");
    TreeDumpFunc(tree, Out, sel);
    fprintf(Out, "}\n");

    fclose(Out);

    return tree;
}
