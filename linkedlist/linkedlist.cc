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

void LinkedList::insert(item, index){
  /*
   * This function will insert the given  item at the
   * given index 
   */

  // case: index is 0 (head)
  if(index==0){
    LinkedList.prepend(item);
    return
  }
  // case: index is length of ll (tail)
  if(index==LinkedList.size-1){
    LinkedList.append(item);
    return
  }

  previous_node = LinkedList.get_index_node(index-1);
  index_node = LinkedList.get_index_node(index);
  // create node
  next_node = new Node(item);
  // update next
  previous_node.next = &next_node;
  next_node.next = &index_node;
  // update size
  LinkedList.size++; 
}

} // namespace linkedlist
