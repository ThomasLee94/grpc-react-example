#include "linkedlist.h"

namespace linkedlist {

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

bool LinkedList::is_empty() {
  /*
   * returns true if linked list is empty,
   * returns false if it contains one or more items.
   */
  return LinkedList.head == NULL;
}

void LinkedList::append(item){
  /* 
   * This function insert the given item at the tail of 
   * this linked list
   */
  
  // Crate new node
  new_node = new Node(item);

  // check if linkedlist is empty
  if LinkedList.is_empty(){
    LinkdedList.head = &new_node;
  } else {
    // if nodes already exist, append node after tail
    LinkedList.tail.next = &new_node;
  }

  // update tail and size
  LinkedList.tail = &new_node;
  LinkedList.size++;
}

void LinkedList::prepend(item){
  /* 
   * This function insert the given item at the head
   * this linked list
   */

  new_node = new Node(item);

  if LinkedList.is_empty(){
    // assign new tail
    LinkedList.tail = &new_node; 
  } else {
    // prepend
    new_node.next = LinkedList.head; 
  }
  
  // update head and size
  LinkedList.head = &new_node;
  LinkedList.size++;

}

} // namespace linkedlist
