#include <iostream>
using namespace std;

class Node {
public:
  int data;
  Node *next;
};

// prints LL
void printList(Node *node) {
  while (node != NULL) {
    cout << " " << node->data;
    node = node->next;
  }
}

// ** is a pointer to a pointer, or a reference to a pointer
// Node **headRef is a pointer that references (or points to) the "head" pointer of this linked list
void insertBeg(Node **headRef, int newData) {
  
  // creates newNode pointer, initializes as new object in the node class.
  Node *newNode = new Node(); 

  // sets data value of newNode to newData (inputted into from this function)
  newNode->data = newData;
  
  // dereferences (take address from) headRef pointer to allow head pointer to point to new object
  newNode->next = *headRef;

  // sets now dereferenced headRef pointer to the newNode pointer which points to the new object
  *headRef = newNode;
}

// Given a node prevNode, insert a new node after the given prevNode
void insertAfter(Node *prevNode, int newData) {

  //created new object from Node class, pointer named newNode to point to object
  Node *newNode = new Node();

  // sets data value of newNode to newData (inputted into from this function)
  newNode->data = newData;

  //sets next pointer of newNode to the address of prevNode by derefferencing prevNode pointer
  newNode->next = prevNode->next;

  //sets next pointer of prevNode (which has been derefferenced, therefore has no address) to point to the address of newNode.
  prevNode->next = newNode;

  if(prevNode == NULL) {
    cout << "The given prevNode should not be NULL";
    return;
  }
}

// Given a reference pointer (pointer to a pointer) to the head pointer of a list and an int value, appends a new node at the end
void insertLast(Node **headRef, int newData) {
  //created new object from Node class, pointer named newNode to point to object
  Node *newNode = new Node();

  // stores the address of headRef in a new Node pointer called last. Does not dereference headRef
  Node *last = *headRef; 

  // sets data value of newNode to newData (inputted into from this function)
  newNode->data = newData;

  // sets address of next pointer to NULL since it is the last in the linked list
  newNode->next = NULL;

  // Checks if the linked list is empty, if true; make new node as head
  if(*headRef == NULL) {
    *headRef = newNode;
    return;
  }

  //if false, traverse list until last node
  while(last->next != NULL) {
    last = last->next;
  }

  // change next of last node to new node
  last->next = newNode;
  return;
}

// removes all elements equal to inputted value
Node *removeAll(Node *head, int value) {
  // if the LL is empty, return it
  if (head == NULL) {
    return head;
  }
  // while the head isn't empty and the head data is equal to inputted value
  while (head != NULL && head->data == value) {
    // set address of head to next node pointer, skipping over the previous head node (therefore "deleting" it)
    head = head->next;
  }
  // Creates prevNode pointer
  Node *prevNode = new Node();
  // makes prevNode the new head of the list
  prevNode = head;

  // while prevNode is not null
  while(prevNode != NULL) {
    // checks if prevNode next pointer (the current head) is empty, if so, return
    if (prevNode->next == NULL) {
      return head;
    }
    // checks if data of the prevNode's next node pointer is equal to the inputted value
    else if (prevNode->next->data == value) {
      // sets prevNode next node pointer to the following next pointer (skipping over the unwanted one if applicable)
      prevNode->next = prevNode->next->next;
    }
    else {
      // sets address of prevNode to prevNode's next pointer, provided the next node just checked was not equal to the value that needs to be deleted
      prevNode = prevNode->next;
    }
  }
  return head;
}

// inserts a value in a position/place based on inputted numbers
Node *insertToPlace(Node *head, int value, int place) {
  // checks if list is empty or if place is the 1st or less, if so, return
  if (head == NULL || place <= 1) {
    return head;
  }
  // create tempNode
  Node *tempNode = new Node();
  // set tempNode equal to inputted value
  tempNode->data = value;
  // creates arbitrary pointer to point to head pointer
  Node *current = head;
  // uses current pointer to traverse without changing head
  for (int i = 1; i < place-1; i++) {
    // if current->next is null, that is the last node, break
    if (current->next == NULL) {
      break;
    }
    // traverse list by setting current next pointer to the next node every time it's not null
    else {
      current = current->next;
    }
  }
  // sets tempNode next pointer to current's next pointer : tempNode->next = NULL, current->next = what last traversed node is pointing to in list : result sets tempNode->next to next node in list (you traverse to the node BEFORE the place you want to insert a new node)
  tempNode->next = current->next;
  // sets current->next to point at the created tempNode, which has the inputted value and points to the next node in the list
  current->next = tempNode;
  return head;
}

int main() {
  // creates empty list with a head pointer that is equal to NULL
  Node *head = NULL;

  // insert 20 as head : LL is 20->NULL
  insertLast(&head, 20);

  // insert 10 at beginning : LL is 10->20->NULL
  insertBeg(&head, 10);

  // insert 15 after 10 : LL is 10->15->20->NULL
  insertAfter(head, 15);

  // insert 10 in place 3 : LL is 10->15->10->20->NULL
  head = insertToPlace(head, 10, 3); // use head = func to update LL

  //print list
  cout << "LL is: ";
  printList(head);
  cout << endl;

  // removes all instances of '10'
  head = removeAll(head, 10); // use head = func to update LL

  //print list
  cout << "LL is: ";
  printList(head);
  cout << endl;
}
