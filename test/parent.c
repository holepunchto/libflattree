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
  return 0;
}
