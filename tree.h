#ifndef TREE_H
#define TREE_H

typedef int CompareFunc_t(const int a, const int b);

enum order
{
    IN_ORDER,
    PRE_ORDER,
    POST_ORDER
};

struct Tree
{
    int field;
    Tree * left;
    Tree * right;
};

Tree * TreeCtor(int val);
void TreeDtor(Tree * tree);

Tree * TreeAdd(Tree * tree, int val, CompareFunc_t * compare);

Tree * TreeSearchFunc(Tree * tree, int val);
int TreeSearch(Tree * tree, int val);

Tree * TreePrint(Tree * tree, int height);
Tree * TreePrintBracket(Tree * tree, int height);

Tree * TreeDump(Tree * tree, const char * FileName, Tree * sel);
Tree * TreeDumpFunc(Tree * tree, FILE * Out, Tree * sel);

#endif
