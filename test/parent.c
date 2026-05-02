#include <assert.h>
#include "../include/flattree.h"

int
main () {
  assert(flat_tree_parent(0) == 1);
  assert(flat_tree_parent(2) == 1);
  assert(flat_tree_parent(1) == 3);
  assert(flat_tree_parent(4) == 5);
  assert(flat_tree_parent(6) == 5);
  assert(flat_tree_parent(5) == 3);
  assert(flat_tree_parent(3) == 7);
  assert(flat_tree_parent(8) == 9);
  assert(flat_tree_parent(10) == 9);
  assert(flat_tree_parent(9) == 11);
  assert(flat_tree_parent(12) == 13);
  assert(flat_tree_parent(14) == 13);
  assert(flat_tree_parent(13) == 11);
  assert(flat_tree_parent(11) == 7);

  /* parent of left child and parent of right child are both the node */
  for (uint64_t i = 1; i < 64; i += 2) {
    assert(flat_tree_parent(flat_tree_left_child(i)) == i);
    assert(flat_tree_parent(flat_tree_right_child(i)) == i);
  }

  return 0;
}
