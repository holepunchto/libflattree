#include <assert.h>
#include "../include/flattree.h"

int
main () {
  assert(flat_tree_depth(0) == 0);
  assert(flat_tree_depth(1) == 1);
  assert(flat_tree_depth(2) == 0);
  assert(flat_tree_depth(3) == 2);
  assert(flat_tree_depth(4) == 0);
  assert(flat_tree_depth(5) == 1);
  assert(flat_tree_depth(6) == 0);
  assert(flat_tree_depth(7) == 3);
  assert(flat_tree_depth(8) == 0);
  assert(flat_tree_depth(9) == 1);
  assert(flat_tree_depth(10) == 0);
  assert(flat_tree_depth(11) == 2);
  assert(flat_tree_depth(12) == 0);
  assert(flat_tree_depth(13) == 1);
  assert(flat_tree_depth(14) == 0);
  assert(flat_tree_depth(15) == 4);
  assert(flat_tree_depth(31) == 5);
  assert(flat_tree_depth(63) == 6);
  assert(flat_tree_depth(127) == 7);
  return 0;
}
