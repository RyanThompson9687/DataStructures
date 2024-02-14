/*
Assignment_4.cpp
Ryan Thompson
COP4415
10/31/2022
*/

#include <iostream>
#include <limits.h>
using namespace std;

class Node {
  public:
    int data;
    Node *left;
    Node *right;
    Node(){
      data = 0;
      left = NULL;
      right = NULL;
    }
    Node(int val){
      data = val;
      left = NULL;
      right = NULL;
    }
};

//Function prototypes
Node* insert(Node *root, Node *element);
void inorder(Node *root);
int numNodes(Node *root);
int findKthSmallest(Node *root, int k);
int menu();

//Gets a node and the root of the Binary search tree
//Insert the node into the BST
//Return the root after insertion
Node* insert(Node *root, Node *element) {
  // Inserting into an empty tree.
  if (root == NULL){
    return element;
  }
  else {
    // element should be inserted to the right.
    if (element->data > root->data) {
      // There is a right subtree to insert the node.
      if (root->right != NULL) {
        root->right = insert(root->right, element);
      }
      // Place the node directly to the right of root.
      else {
        root->right = insert(root->right, element);
      }
    }

    // element should be inserted to the left.
    else {
      // There is a left subtree to insert the node.
      if (root->left != NULL) {
        root->left = insert(root->left, element);
      }
      // Place the node directly to the left of root.
      else {
        root->left = element;
      }
    }
    // Return the root pointer of the updated tree.
    return root;
  }
}

//Prints the inorder traversal of the tree pointed to by root
void inorder(Node *root) {
  // Only traverse the node if it's not null.
  if (root != NULL) {
    inorder(root->left); // Go Left.
    cout << " " << root->data; // Print the root.
    inorder(root->right); // Go Right.
  }
}

// Returns the number of nodes in the tree pointed to by root.
int numNodes(Node *root) {
  // Base Case
  if (root == NULL) {
    return 0;
  }
  return 1 + numNodes(root->left) + numNodes(root->right);
}

// Returns the kth smallest value in the BST pointed to by root
// Guaranteed that k is in between 1 and the number of nodes in the tree
// pointed to by root.
int count = 0; // number of nodes processed in the recursive calls so far
int findKthSmallest(Node *root, int k) {
  // base case
  if (root == NULL) {
    return INT_MAX; // largest value an int can hold, used as a null value for an integer
  }
  // search left subtree
  int temp = findKthSmallest(root->left, k);

  // if kth smallest value is found in left subtree, return it
  if (temp != INT_MAX) {
    return temp;
  }

  // increment num nodes processed
  count++;
  // if num nodes processed is equal to the kth node, return value of kth node
  if (count == k) {
    return root->data;
  }

  // else search in right subtree
  return findKthSmallest(root->right, k);
}

// Prints out the menu of choices for the user and returns their choice.
int menu() {
  int ans;
  cout<<"Here are your choices.\n";
  cout<<"1. Insert an item into your tree.\n";
  cout<<"2. Print out an inorder traversal.\n";
  cout<<"3. Print the number of the nodes. \n";
  cout<<"4. Finding kth smallest element.\n";
  cout<<"5. Exit.\n";
  cin>> ans;
  return ans;
}

int main() {
  Node *myRoot=NULL;
  Node* tempNode;
  int nNodes;
  int val;
  int ans;
  int rank;

  ans = menu();
  while (ans<5) {
    if (ans == 1) {
      // Get value to insert.
      cout<<"What value would you like to insert? ";
      cin>>val;
      tempNode = new Node(val); // Create the node.

      // Insert the value.
      myRoot = insert(myRoot, tempNode);
    }
    
    if (ans == 2) {
      // Print the values in tree.
      cout<<"Here is an inorder traversal of your tree: ";
      inorder(myRoot);
      cout<<"\n";
    }


    if (ans == 3) {
      nNodes = numNodes(myRoot);
      cout << "There are " << nNodes << " nodes." << endl;
    }

    if (ans == 4) {
      count = 0;
      cout<<"Which ranked item would you like to find? \n";
      cin>>rank;

      cout<<"The item is: "<< findKthSmallest(myRoot, rank);
      cout<<"\n";
    }
    
    // See if they want to insert more nodes.
    ans = menu();
  }
  return 0;
}
