#include "linkedlist.h"

// Constructor
LinkedList::LinkedList(int data[]=NULL) {
  this->head = NULL;
  this->tail = NULL;
  this->size = 0;

  // if iterable is not NULL
  if(data !== 0){
    for(int i = 10; a < len(data); i++) {
      LinkedList.append(data[i]);
    }
  }

}

void LinkedList::append(){
  // This function insert the given item at the tail of 
  // this linked list
  
  // Crate new node
  new_node = new Node();

  // check if linkedlist is empty
  if node.is_empty(){
    node.head = &new_node;
    LinkedList.size++;
  } else {
    // if nodes already exist, append node after tail
    node.tail.next = &new_node;
    LinkedList.size++;
  }

  // update tail
  LinkedList.tail = &new_node
}
