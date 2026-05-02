#include <assert.h>
#include "../include/flattree.h"

int
main () {
  assert(flat_tree_left_child(1) == 0);
  assert(flat_tree_right_child(1) == 2);
  assert(flat_tree_left_child(3) == 1);
  assert(flat_tree_right_child(3) == 5);
  assert(flat_tree_left_child(5) == 4);
  assert(flat_tree_right_child(5) == 6);
  assert(flat_tree_left_child(7) == 3);
  assert(flat_tree_right_child(7) == 11);
  assert(flat_tree_left_child(11) == 9);
  assert(flat_tree_right_child(11) == 13);
  assert(flat_tree_left_child(15) == 7);
  assert(flat_tree_right_child(15) == 23);

  /* leaf nodes return themselves */
  assert(flat_tree_left_child(0) == 0);
  assert(flat_tree_right_child(0) == 0);
  assert(flat_tree_left_child(2) == 2);
  assert(flat_tree_right_child(4) == 4);

  /* left child spans left half, right child spans right half */
  for (uint64_t i = 1; i < 64; i += 2) {
    uint64_t lc = flat_tree_left_child(i);
    uint64_t rc = flat_tree_right_child(i);
    assert(flat_tree_left_span(lc) == flat_tree_left_span(i));
    assert(flat_tree_right_span(rc) == flat_tree_right_span(i));
  }

  return 0;
}
