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
  /* leaf nodes return themselves */
  assert(flat_tree_left_child(0) == 0);
  assert(flat_tree_right_child(0) == 0);
  return 0;
}
