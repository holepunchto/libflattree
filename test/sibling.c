#include <assert.h>
#include "../include/flattree.h"

int
main () {
  assert(flat_tree_sibling(0) == 2);
  assert(flat_tree_sibling(2) == 0);
  assert(flat_tree_sibling(1) == 5);
  assert(flat_tree_sibling(5) == 1);
  assert(flat_tree_sibling(4) == 6);
  assert(flat_tree_sibling(6) == 4);
  return 0;
}
