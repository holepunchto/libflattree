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
  assert(flat_tree_offset(7) == 0);
  assert(flat_tree_offset(8) == 4);
  assert(flat_tree_offset(9) == 2);
  assert(flat_tree_offset(10) == 5);
  assert(flat_tree_offset(11) == 1);
  assert(flat_tree_offset(12) == 6);
  assert(flat_tree_offset(13) == 3);
  assert(flat_tree_offset(14) == 7);
  assert(flat_tree_offset(15) == 0);
  return 0;
}
