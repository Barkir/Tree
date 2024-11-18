#ifndef TREE_H
#define TREE_H

typedef int CompareFunc_t(const char * field);

enum order
{
    IN_ORDER,
    PRE_ORDER,
    POST_ORDER
};

enum choice
{
    TREE_DEF,
    TREE_YES,
    TREE_NO,
    TREE_END
};

struct Tree
{
    char * field;
    Tree * left;
    Tree * right;
    CompareFunc_t * compare;
};

int TreeCtor(Tree ** tree, char * field);
void TreeDtor(Tree * tree);

Tree * TreeSearchFunc(Tree * tree, const char * field);
int TreeSearch(Tree * tree, const char * field);

int TreeAdd(Tree ** tree, char * field);

Tree * TreePrint(Tree * tree, int height);
Tree * TreePrintBracket(Tree * tree, int height);

Tree * TreeDump(Tree * tree, const char * FileName, Tree * sel);
Tree * TreeDumpFunc(Tree * tree, FILE * Out, Tree * sel);

Tree * Akinator(Tree * tree);

int TreeParse(Tree ** tree, const char * filename);
int _TreeParse(Tree ** tree, const char ** string, int start, int end);
int FindIndex(const char ** string, int start, int end);


#endif




