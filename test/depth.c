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
  return 0;
}
