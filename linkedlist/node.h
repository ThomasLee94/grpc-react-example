#ifndef NODE_H_
#define NODE_H_

namespace linkedlist {

struct Node {
  int data;
  struct Node *next;

  Node(const int data) { this->data = data; }
};

} // namespace linkdedlist

#endif // NODE_H_
