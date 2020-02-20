#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <vector>

#include "linkedlist/node.h"

namespace linkedlist{ 

class LinkedList {
  public:
  LinkedList(const std::vector<int>& data);

  bool is_empty(); // checks if ll is empty
  int get_at_index(int index); // returns data of node at given index
  Node get_index_node(int index); // returns node obj at given index
  void append(int item); // appends given item to the end of the ll
  void prepend(int item); // prepends the given item to the beginning of the ll
  void insert(int item, int index); // inserts the given item at the given index of ll
  void delete_(int item); // deletes node containing given item, throws error otherwise.

  Node *head;
  Node *tail;
  int size;
};

} // namespace linkedlist

#endif // LINKEDLIST_H_
