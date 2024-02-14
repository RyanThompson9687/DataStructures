/*
  Project2.cpp
  Ryan Thompson
  COP4415
  Last Modified: 11/18/2022
*/

#include <iostream>
#include <string.h>
using namespace std;

// global output file. Can be updated from anywhere
FILE *outfile;

// For the items of each tree name
class itemNode {
 public:
  char name[50];
  int count;
  itemNode *left, *right;

  itemNode() {
    name[0] = '\0';
    count = 0;
    left = NULL;
    right = NULL;
  }

  itemNode(char itemName[], int population) {
    strcpy(name, itemName);
    count = population;
    left = NULL;
    right = NULL;
  }
};

// For Tree Names
class treeNameNode {
 public:
  char treeName[50];
  treeNameNode *left, *right;
  itemNode *childItemNode;

  treeNameNode() {
    treeName[0] = '\0';
    childItemNode = NULL;
    left = NULL;
    right = NULL;
  }

  treeNameNode(char name[]) {
    strcpy(treeName, name);
    childItemNode = NULL;
    left = NULL;
    right = NULL;
  }
};

// inserts values into the nameTree (parent tree)
treeNameNode *insertNameTree(treeNameNode *topTree, treeNameNode *temp) {
  // Inserting into an empty tree.
  if (topTree == NULL){
    return temp;
  }
  else {
    // temp should be inserted to the right.
    if (strcmp(temp->treeName, topTree->treeName) > 0) {
      topTree->right = insertNameTree(topTree->right, temp);
    }
    
    // element should be inserted to the left.
    else {
      topTree->left = insertNameTree(topTree->left, temp);
    }

    // Return the root pointer of the updated tree.
    return topTree;
  }
}

// builds nameTree by reading input from in.txt, inserts values via insertNameTree function
treeNameNode *buildNameTree(FILE *infile, int tnCount) {
  treeNameNode *topTree = NULL;
  char treeName[50];
  for (int i = 0; i < tnCount; i++) {
    fscanf(infile, "%s", treeName);
    treeNameNode *temp = new treeNameNode(treeName);
    topTree = insertNameTree(topTree, temp);
  }
  return topTree;
}

// takes string from in.txt and searches the name (parent) tree for that string. Determines parent node for inputted item.
treeNameNode *searchNameNode(treeNameNode *topTree, char treeName[]) {
  // Check if there are nodes in the tree.
  if (topTree != NULL) {
    int cmpVal = strcmp(treeName, topTree->treeName);
    
    if (cmpVal == 0) { // Node found
      return topTree;
    }
    else if (cmpVal < 0) { // left
      return searchNameNode(topTree->left, treeName);
    }
    else { // right
      return searchNameNode(topTree->right, treeName);
    }
  }
  else {
    return NULL; // No node found
  }
}

// takes string from in.txt and searches the itemNode for that string. 
itemNode *searchItemNode(itemNode *root, char itemNodeSTR[]) {
  // Check if there are nodes in the tree.
  if (root != NULL) {
    int cmpVal = strcmp(itemNodeSTR, root->name);
    
    if (cmpVal == 0) { // Node found
      return root;
    }
    else if (cmpVal < 0) { // left
      return searchItemNode(root->left, itemNodeSTR);
    }
    else { // right
      return searchItemNode(root->right, itemNodeSTR);
    }
  }
  else {
    return NULL; // No node found
  }
}

// inserts values into itemNode child trees
itemNode *insertOtherTree(itemNode *childItemNode, itemNode *newItemNode) {
  // Inserting into an empty tree.
  if (childItemNode == NULL){
    return newItemNode;
  }
  else {
    // newItemNode should be inserted to the right.
    if (strcmp(newItemNode->name, childItemNode->name) > 0) {
      childItemNode->right = insertOtherTree(childItemNode->right, newItemNode);
    }

    // element should be inserted to the left.
    else {
      childItemNode->left = insertOtherTree(childItemNode->left, newItemNode);
    }

    // Return the root pointer of the updated tree.
    return childItemNode;
  }
}

// builds item tree by reading input from in.txt
void buildOtherTree(FILE *infile, treeNameNode *topTree, int itemCount) {
  char treeName[50], itemName[50];
  treeNameNode *parentTree;
  int population;

  for (int i = 0; i < itemCount; i++) {
    fscanf(infile, "%s %s %d", treeName, itemName, &population);
    // find parent tree
    parentTree = searchNameNode(topTree, treeName);
    // create new item node, insert item node into other tree
    itemNode *newItemNode = new itemNode(itemName, population);
    parentTree->childItemNode = insertOtherTree(parentTree->childItemNode, newItemNode);
  }
}

// prints inorder traversal of name trees
void inOrder_nameTree(treeNameNode *root) {
  if (root == NULL) {
    return;
  }
  inOrder_nameTree(root->left);
  printf("%s ", root->treeName);
  fprintf(outfile, "%s ", root->treeName);
  inOrder_nameTree(root->right);
}

// prints inOrder of tree passed into function
void inOrderTraversal(itemNode *root) {
  if (root == NULL) {
    return;
  }
  inOrderTraversal(root->left);
  printf("%s ", root->name);
  fprintf(outfile, "%s ", root->name);
  inOrderTraversal(root->right);
}

// traverses from root of name tree down through the corresponding item tree
void traverse_in_traverse(treeNameNode *root) {
  if (root == NULL) {
    return;
  }
  // traverse tree, print ***nameTree*** (parent tree)
  traverse_in_traverse(root->left);
  printf("***%s***\n", root->treeName);
  fprintf(outfile, "***%s***\n", root->treeName);

  // traverse tree, print inOrder values of item tree (child tree)
  inOrderTraversal(root->childItemNode);
  printf("\n");
  fprintf(outfile, "\n");

  // recursively call again
  traverse_in_traverse(root->right);
}

// searches for a nameTree (parent tree) and itemNode (child tree) and paramC from in.txt
int search(treeNameNode *root, char paramA[], char paramB[], int *paramC) {
  // finds nameTree (parent tree). If NULL, return -1
  treeNameNode *targetNode = searchNameNode(root, paramA);
  if (targetNode == NULL) {
    return -1;
  }
  // finds itemNode (child tree). If NULL, return -2
  itemNode *targetItem = searchItemNode(targetNode->childItemNode, paramB);
  if (targetItem == NULL) {
    return -2;
  }
  // set targetItem->count (int value found from searchItemNode) as the int value held by the *paramC pointer
  *paramC = targetItem->count;
  
  // if both nameTree (parent) and itemNode (child) found, return 0
  return 0;
}

// traverses item tree to determine the number of items before the desired item. 
int item_before_itemTree(itemNode *root, char paramB[]) {
  if (root == NULL) { // base case
    return 0;
  }

  int numNodes = 0; // keeps track of num nodes looked at. Initialize to 0 because you don't know if you need to count what you're currently looking at
  int compVal = strcmp(paramB, root->name); // compare the item we are looking for to the node we are currently looking at

  numNodes += item_before_itemTree(root->left, paramB); // // traverse left subtree

  //if you've found the node you're looking for
  if (compVal == 0) {
    return numNodes; // numNodes is currently the num of nodes in the left subtree
  }
  else if (compVal < 0) { // if current root is greater than what you're looking for
    return numNodes; // don't count what you're currently looking at and don't traverse right
  }
  else {
    numNodes += 1;  //count itself 
    numNodes += item_before_itemTree(root->right, paramB); //traverse the right tree
  }

  return numNodes; // numNodes currently represents the num items before what you're looking for
}

// finds name tree that acts as parent to the child tree where the item you are looking for is located
void item_before_nameTree(treeNameNode *root, char paramA[], char paramB[]) {
  // find the name tree that contains the item tree with the item we are looking for
  treeNameNode *temp = searchNameNode(root, paramA);
  // searches item tree for the item we are looking for
  int numItemsBefore = item_before_itemTree(temp->childItemNode, paramB);

  printf("item before %s: %d\n", paramB, numItemsBefore);
  fprintf(outfile, "item before %s: %d\n", paramB, numItemsBefore);
}

// finds height of node
int height(itemNode *root) {
  if (root == NULL) {
    return 0;
  }

  int LH = height(root->left);
  int RH = height(root->right);
  return 1 + max(LH, RH);
}

// finds left and right heights of tree, the difference in left and right heights, and determines if the heights are balanced 
void height_balance(treeNameNode *root, char paramA[]) {
  itemNode *temp = (searchNameNode(root, paramA)->childItemNode); // find parent node and set that node's childItemNode to a temp itemNode
  
  int LH = height(temp->left);
  int RH = height(temp->right);
  int difference = abs(LH-RH);

  int balanced;

  if (difference <= 1) {
    balanced = 1;
  }
  else if (difference > 1) {
    balanced = 0;
  }

  if (balanced == 1) {
    printf("%s: left height %d, right height %d, difference %d, balanced\n", paramA, LH, RH, difference);
    fprintf(outfile, "%s: left height %d, right height %d, difference %d, balanced\n", paramA, LH, RH, difference);
  }
  else {
    printf("%s: left height %d, right height %d, difference %d, not balanced\n", paramA, LH, RH, difference);
    fprintf(outfile, "%s: left height %d, right height %d, difference %d, not balanced\n", paramA, LH, RH, difference);
  }
}

// counts total items in item tree
int count_itemTree(itemNode *root) {
  if (root == NULL) {
    return 0;
  }

  return root->count + count_itemTree(root->left) + count_itemTree(root->right);
}

// prints the number of items in the entered name tree
void count_nameTree(treeNameNode *root, char paramA[]) {
  itemNode *temp = (searchNameNode(root, paramA)->childItemNode); // find parent node and set that node's childItemNode to a temp itemNode
  int count = count_itemTree(temp);

  printf("%s count %d\n", paramA, count);
  fprintf(outfile, "%s count %d\n", paramA, count);
}

// starts query functions to be outputted in out.txt
void performQueries (treeNameNode *root, FILE *infile, int queryCount) {
  char queryType[50];
  char paramA[50];
  char paramB[50];
  int paramC;
  int i;
  for (i = 0; i < queryCount; i++) {
    fscanf(infile, "%s", queryType);

    // search query
    if (strcmp(queryType, "search") == 0) {
      fscanf(infile, "%s %s", paramA, paramB);

      int searchResult = search(root, paramA, paramB, &paramC);
      
      // 3 cases
      if (searchResult == 0) {
        printf("%d %s found in %s\n", paramC, paramB, paramA);
        fprintf(outfile, "%d %s found in %s\n", paramC, paramB, paramA);
      }
      else if (searchResult == -1) {
        printf("%s does not exist\n", paramA);
        fprintf(outfile, "%s does not exist\n", paramA);
      }
      else if (searchResult == -2) {
        printf("%s not foud in %s\n", paramB, paramA);
        fprintf(outfile, "%s not foud in %s\n", paramB, paramA);
      }
    }

    // item_before query
    else if (strcmp(queryType, "item_before") == 0) {
      fscanf(infile, "%s %s", paramA, paramB);
      item_before_nameTree(root, paramA, paramB);
    }

    // height_balance query
    else if (strcmp(queryType, "height_balance") == 0) {
      fscanf(infile, "%s", paramA);
      height_balance(root, paramA);
    }

    // count query
    else if (strcmp(queryType, "count") == 0) {
      fscanf(infile, "%s", paramA);
      count_nameTree(root, paramA);
    }
  }
}

int main() {
  FILE *infile = fopen("in.txt", "r"); // opens input txt file
  outfile = fopen("out.txt", "w"); // opens output txt file
  treeNameNode *topTree = NULL; // creates empty name tree

  int tnCount, itemCount, queryCount; // creates variables to hold input values from line 1 of in.txt
  fscanf(infile, "%d %d %d", &tnCount, &itemCount, &queryCount); // scans first line of in.txt, assigns to variables
  
  topTree = buildNameTree(infile, tnCount); // inputs values into created name tree
  buildOtherTree(infile, topTree, itemCount); // creates and inputs values into item tree 

  inOrder_nameTree(topTree); // inOrder printout of name tree values
  printf("\n");
  fprintf(outfile, "\n"); 
  traverse_in_traverse(topTree); // traverses trees and prints inOrder printout of item trees

  performQueries(topTree, infile, queryCount); // performs search, item_before, height_balance, and count queries

  fclose(infile); // close input file
  fclose(outfile); // close output file

  return 0;
}
