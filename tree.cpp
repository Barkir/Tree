#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "tree.h"
#include "ascii.h"
#include "compare.h"

int TreeCtor(Tree ** tree, char * field)
{
    *tree = (Tree*) calloc(1, sizeof(Tree));
    if (!tree) return -1;

    (*tree)->field = field;

    (*tree)->left = NULL;
    (*tree)->right = NULL;

    (*tree)->compare = CompareString;

    return 0;
}

void TreeDtor(Tree * tree)
{

    if (tree)
    {
        TreeDtor(tree->left);
        TreeDtor(tree->right);
    }

    if (tree) free(tree->field);
    free(tree);

}

int TreeAdd(Tree ** tree, char * field)
{
    if (!tree)
    {
        return TreeCtor(tree, field);
    }
    if ((*tree)->compare((*tree)->field) < 0)   return TreeAdd(&((*tree)->left), field);
    else                                        return TreeAdd(&((*tree)->right), field);

    return 0;

}

Tree * TreePrint(Tree * tree, int height)
{
    if (!tree)
        return tree;

    printf("tree[%p], %*stree.field = %s, tree.left[%p] tree.right[%p]\n", tree, height*4, "", tree->field, tree->left, tree->right);
    TreePrint(tree->left, height + 1);
    TreePrint(tree->right, height + 1);

    return tree;
}

Tree * TreePrintBracket(Tree * tree, int order)
{
    if (!tree)
        return tree;

    printf("( ");

    if (order == PRE_ORDER) printf("\"%s\" ", tree->field);
    TreePrintBracket(tree->left, order);

    if (order == IN_ORDER) printf("\"%s\" ", tree->field);

    TreePrintBracket(tree->right, order);
    if (order == POST_ORDER) printf("\"%s\" ", tree->field);

    printf(") ");

    return tree;
}

int TreeSearchFunc(Tree * tree, const char * field, int num)
{
    if (tree == NULL) return NULL;

    if (strcmp(tree->field, field) == 0) return num;

    int result  = TreeSearchFunc(tree->left, field, num * 10 + 1);
    if (!result) result = TreeSearchFunc(tree->right, field, num * 10 + 2);

    return result;

}

int TreeSearch(Tree * tree, const char * field)
{

    int found = TreeSearchFunc(tree, field, 0);
    int result = 0;

    while (found)
    {
        result = result * 10 + found % 10;
        found /= 10;
    }

    if (result)
    {
        _TreeSearchHelpFunc(tree, result);
        return 1;
    }
    return -printf("not found :(\n");
}

void _TreeSearchHelpFunc(Tree * tree, int num)
{
    if (num)
    {
        if (num % 10 == 1) printf("not ");
        printf("%s, ", tree->field);
        if (num % 10 == 1) _TreeSearchHelpFunc(tree->left, num / 10);
        if (num % 10 == 2) _TreeSearchHelpFunc(tree->right, num / 10);
    }
    else if (!tree->left || !tree->right) printf("it is %s\n", tree->field);
}

Tree * TreeDumpFunc(Tree * tree, FILE * Out, Tree * sel)
{
    unsigned int color = 0XE0D0FF;
    if (tree == sel) color = 0XFFF0F0;

    if (!tree)
        return tree;

    fprintf(Out, "tree%p [shape = Mrecord; label = \"{ %s? | adr = %p}\"; style = filled; fillcolor = \"#%06X\"];\n",
        tree, tree->field, tree, color);

    if (tree->left)
        fprintf(Out, "tree%p -> tree%p [label = \"NO\"]\n", tree, tree->left);

    if (tree->right)
        fprintf(Out, "tree%p -> tree%p [label = \"YES\"]\n", tree, tree->right);

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

    char command[DEF_SIZE] = "";
    sprintf(command, "dot %s -T png -o %s.png", FileName, FileName);

    fclose(Out);

    system(command);

    return tree;
}

Tree * Akinator(Tree * tree)
{
    if (!tree->left && !tree->right)
    {
        printf("%s?\n", tree->field);
        return NULL;
    }

    switch(tree->compare(tree->field))
    {
        case TREE_YES:
            return Akinator(tree->right);
        case TREE_NO:
            return Akinator(tree->left);
        case TREE_END:
            return tree;
        default:
            return Akinator(tree);
    }
}

int TreeParse(Tree ** tree, const char * filename)
{
    FILE * file = fopen(filename, "rb");
    fseek(file, 0L, SEEK_END);
    long int fsize = ftell(file);
    if (fsize <= 0) return -fprintf(stderr, "Wrong file size");
    rewind(file);

    char * expression = (char *) calloc((size_t)(fsize + 1), sizeof(char));
    if (!expression) return -fprintf(stderr,"Allocate Memory error!");
    fread(expression, sizeof(char), (size_t) fsize, file);

    const char * ptr = expression;
    _TreeParse(tree, &ptr, 0, (int)(strlen(ptr) - 1));

    fclose(file);
    free(expression);
    return 1;
}

int _TreeParse(Tree ** tree, const char ** string, int start, int end)
{
    int index = -1;

    if (start > end) return 0;
    char * field = NULL;

    while (*((*string) + start) == ' ') start++;

    while (*((*string) + start) != '\"')
        start++;
    start++;

    const char * ptr = ((*string) + start);
    size_t size = 0;
    while (*((*string) + start) != '\"')
    {
        start++;
        size++;
    }
    start++;

    field = (char*) calloc(size + 1, sizeof(char));
    if (!field) return -fprintf(stderr, "Allocate Memory Error!\n");
    memcpy(field, ptr, size);
    TreeCtor(tree, field);

    while (*((*string) + start) == ' ') start++;
    if (start <= end)
        index = FindIndex(string, start, end);

    if (index < 0) return -1;
    _TreeParse(&(*tree)->left, string, start + 1, index - 1);
    _TreeParse(&(*tree)->right, string, index + 2, end - 1);
    return 0;



}

int FindIndex(const char ** string, int start, int end)
{
    if (start > end) return -fprintf(stderr, "start[%d] > end[%d]\n", start, end);
    int res = 0;
    if (*(*string + start) != '(') return -1;
    for (int i = start; i <= end; i++)
    {
        if (res < 0) return -fprintf(stderr, "Wrong Bracket Sequence!\n");
        if (*(*string + i) == '(') res++;
        else if (*(*string + i) == ')') res--;
        if (!res) return i;
    }

    return -fprintf(stderr, "Not Found!\n");
}


