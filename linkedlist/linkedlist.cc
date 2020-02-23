#include "linkedlist.h"

#include <stdexcept>
#include <vector>

#include "linkedlist/node.h"

namespace linkedlist {

// Constructor
LinkedList::LinkedList(const std::vector<int>& data) {
  this->head = nullptr;
  this->tail = nullptr;
  this->size = 0;

  for (const int datum : data) {
    append(datum);
  }
}

bool LinkedList::is_empty() {
  /*
   * returns true if linked list is empty,
   * returns false if it contains one or more items.
   */
  return head == nullptr;
}

int LinkedList::get_at_index(int index){
  /*
   * Return the item at the given index in this linked list, or
   * raise error if index is out of bounds.
   */

  Node* node = head;

  for (int i=0; i<=index; i++) {
    node = node->next;
  }

  return node->data;
}

Node LinkedList::get_index_node(int index) {
  // Returns the node at given index
  
  // Check if the given index is out of range and if so raise an error
  if (index < 0 && index >= size) {
    throw std::invalid_argument( "index is out or range" );
  }

  Node* node = head;

  // reassign node to node.next until index is reached
  for (int i = 0; i <= index; i++){
    node = node->next;
  }

  return *node;
}

void LinkedList::append(int item){
  /* 
   * This function insert the given item at the tail of 
   * this linked list
   */
  
  // Crate new node
  Node* new_node = new Node(item);

  // check if linkedlist is empty
  if (is_empty()) {
    head = new_node;
  } else {
    // if nodes already exist, append node after tail
    tail->next = new_node;
  }

  // update tail and size
  tail = new_node;
  size++;
}

void LinkedList::prepend(int item){
  /* 
   * This function insert the given item at the head
   * this linked list
   */

  Node* new_node = new Node(item);

  if (is_empty()) {
    // assign new tail
    tail = new_node; 
  } else {
    // prepend
    new_node->next = head;
  }
  
  // update head and size
  head = new_node;
  size++;

}

void LinkedList::insert(int item, int index){
  /*
   * This function will insert the given  item at the
   * given index or raise error if index is out of bounds.
   */

  // case: index is 0 (head)
  if(index==0){
    prepend(item);
    return;
  }
  // case: index is length of ll (tail)
  if(index==size-1){
    append(item);
    return;
  }

  Node previous_node = get_index_node(index-1);
  Node index_node = get_index_node(index);

  // create node
  Node* next_node = new Node(item);

  // update next
  previous_node.next = next_node;
  next_node->next = &index_node;

  // update size
  size++;
}

void LinkedList::delete_(int item){
  // Deletes the given item from the linked list

  Node* node = head;

  // Keep track of previous node
  Node* previous = nullptr;

  // found flag
  bool found = false;

  // Iterate until given item is found or node is nullptr
  while (found == false && node != nullptr) {
    // check if node' data matches item
    if (item == node->data){
      found = true;
    } else {
      // continue iteration
      previous = node;
      node = node->next;
    }
  }
  
  // end of initial iteration, check if item was found
  if (found) {
    // check if node is inbetween head and tail
    if (node != head && node != tail) {
      previous->next = node->next;
      node->next = nullptr;
      size--;
    }

    if (node == head) {
        head = node->next;
        node->next = nullptr;
        size--;
    }

    if (node == tail) {
      if (previous != nullptr) {
        previous->next = nullptr;
        size--;
      }

      tail = previous;
    }
  } else {
    throw std::invalid_argument("item not in linked list");
  }
}

} // namespace linkedlist
