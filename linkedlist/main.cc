#include "linkedlist.cc"

#include <iostream>

namespace linkedlist {

int main() {
  int nums[5] = {1, 2, 3, 4, 5};

  linked_list_obj = LinkedList(nums);

  node = linked_list_obj.head;

  for (int i=0; i <= linked_list_obj.size; i++) {
    std::cout << "----- before deletion -----";
    std::cout << node.data;
    node = node.next;
  }

  linked_list_obj.delete_(4);

  
  for (int i=0; i <= linked_list_obj.size; i++) {
    std::cout << "***** after deletion *****";
    std::cout << node.data;
    node = node.next;
  }
}

} // namespace linkedlist
