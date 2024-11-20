#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "compare.h"
#include "ascii.h"

// C3 Algorithm
// BNF Normal Form

/*
 * This is a tree structure made by barkir
 * You can create your own akinator tree using bracket sequence
 * e.g: ("NBA CHAMP?" ("Kwame Brown")("Michael Jordan"))
 * Write this down in a file and run the code below
 * As an example of a choice tree you can use toparse.txt
 * You can also use TreeDump to create a png picture of your tree.
 * For this write TreeDump(your_tree, "your_file.txt")
 * Don't forget to use TreeDtor after you finished working with tree
 *
 * soon updates:
 *               tree parser for equations,
 *               picture ascii dump when akinator guessed correct.
 *
*/

int main(void)
{
    Tree * tree = NULL;
    TreeParse(&tree, "toparse.txt");
    Akinator(tree);
    TreeSearch(tree, "Isaiah Thomas");
    TreeDump(tree, "tree", tree);
    TreeDtor(tree);

}
