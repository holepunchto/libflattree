#include <assert.h>
#include "../include/flattree.h"

int
main () {
  assert(flat_tree_index(0, 0) == 0);
  assert(flat_tree_index(0, 1) == 2);
  assert(flat_tree_index(0, 2) == 4);
  assert(flat_tree_index(1, 0) == 1);
  assert(flat_tree_index(1, 1) == 5);
  assert(flat_tree_index(2, 0) == 3);
  return 0;
}
