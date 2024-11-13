#ifndef TREE_H
#define TREE_H

typedef int CompareFunc_t(const int a, const int b);

enum order
{
    IN_ORDER,
    PRE_ORDER,
    POST_ORDER
};

enum choice
{
    YES,
    NO
};

struct Tree
{
    int field;
    const char * quality;
    Tree * left;
    Tree * right;
};

Tree * TreeCtor(int val, const char * quality);
void TreeDtor(Tree * tree);

Tree * TreeAdd(Tree * tree, int val, const char * quality, CompareFunc_t * compare);
Tree * TreeSearchFunc(Tree * tree, int val);
int TreeSearch(Tree * tree, int val);

Tree * TreePrint(Tree * tree, int height);
Tree * TreePrintBracket(Tree * tree, int height);

Tree * TreeDump(Tree * tree, const char * FileName, Tree * sel);
Tree * TreeDumpFunc(Tree * tree, FILE * Out, Tree * sel);

Tree * Akinator(Tree * tree);

#endif
