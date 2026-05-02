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
  assert(flat_tree_sibling(3) == 11);
  assert(flat_tree_sibling(11) == 3);
  assert(flat_tree_sibling(7) == 23);
  assert(flat_tree_sibling(23) == 7);

  /* sibling is its own inverse */
  for (uint64_t i = 0; i < 64; i++) {
    assert(flat_tree_sibling(flat_tree_sibling(i)) == i);
  }

  /* sibling shares the same parent */
  for (uint64_t i = 0; i < 64; i++) {
    assert(flat_tree_parent(flat_tree_sibling(i)) == flat_tree_parent(i));
  }

  return 0;
}
