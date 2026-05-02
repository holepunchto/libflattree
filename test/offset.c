#include <assert.h>
#include "../include/flattree.h"

int
main () {
  assert(flat_tree_offset(0) == 0);
  assert(flat_tree_offset(1) == 0);
  assert(flat_tree_offset(2) == 1);
  assert(flat_tree_offset(3) == 0);
  assert(flat_tree_offset(4) == 2);
  assert(flat_tree_offset(5) == 1);
  assert(flat_tree_offset(6) == 3);
  return 0;
}
