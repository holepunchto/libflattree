#include <assert.h>
#include "../include/flattree.h"

int
main () {
  flat_tree_iterator_t it;

  flat_tree_iterator_init(&it, 0);
  assert(it.index == 0);
  assert(it.depth == 0);
  assert(it.offset == 0);
  assert(flat_tree_iterator_is_leaf(&it));

  flat_tree_iterator_init(&it, 3);
  assert(it.index == 3);
  assert(it.depth == 2);
  assert(it.offset == 0);
  assert(!flat_tree_iterator_is_leaf(&it));

  /* seek */
  flat_tree_iterator_seek(&it, 5);
  assert(it.index == 5);
  assert(it.depth == 1);
  assert(it.offset == 1);

  /* parent */
  flat_tree_iterator_init(&it, 0);
  flat_tree_iterator_parent(&it);
  assert(it.index == 1);
  assert(it.depth == 1);
  assert(it.offset == 0);

  flat_tree_iterator_parent(&it);
  assert(it.index == 3);
  assert(it.depth == 2);
  assert(it.offset == 0);

  flat_tree_iterator_init(&it, 6);
  flat_tree_iterator_parent(&it);
  assert(it.index == 5);
  flat_tree_iterator_parent(&it);
  assert(it.index == 3);

  /* left_child / right_child */
  flat_tree_iterator_init(&it, 3);
  flat_tree_iterator_left_child(&it);
  assert(it.index == 1);
  assert(it.depth == 1);
  assert(it.offset == 0);

  flat_tree_iterator_right_child(&it);
  assert(it.index == 2);
  assert(it.depth == 0);
  assert(it.offset == 1);

  /* left_child on leaf is no-op */
  flat_tree_iterator_init(&it, 0);
  flat_tree_iterator_left_child(&it);
  assert(it.index == 0);

  /* sibling */
  flat_tree_iterator_init(&it, 0);
  flat_tree_iterator_sibling(&it);
  assert(it.index == 2);
  assert(it.offset == 1);

  flat_tree_iterator_sibling(&it);
  assert(it.index == 0);
  assert(it.offset == 0);

  flat_tree_iterator_init(&it, 1);
  flat_tree_iterator_sibling(&it);
  assert(it.index == 5);
  assert(it.offset == 1);

  /* spans */
  flat_tree_iterator_init(&it, 3);
  assert(flat_tree_iterator_left_span(&it) == 0);
  assert(flat_tree_iterator_right_span(&it) == 6);

  flat_tree_iterator_init(&it, 5);
  assert(flat_tree_iterator_left_span(&it) == 4);
  assert(flat_tree_iterator_right_span(&it) == 6);

  /* iterator matches free functions for all nodes 0..63 */
  for (uint64_t i = 0; i < 64; i++) {
    flat_tree_iterator_seek(&it, i);
    assert(it.index == i);
    assert(it.depth == flat_tree_depth(i));
    assert(it.offset == flat_tree_offset(i));
    assert(flat_tree_iterator_left_span(&it) == flat_tree_left_span(i));
    assert(flat_tree_iterator_right_span(&it) == flat_tree_right_span(i));
  }

  /* parent via iterator matches parent free function */
  for (uint64_t i = 0; i < 64; i++) {
    flat_tree_iterator_seek(&it, i);
    flat_tree_iterator_parent(&it);
    assert(it.index == flat_tree_parent(i));
  }

  /* sibling via iterator matches sibling free function */
  for (uint64_t i = 0; i < 64; i++) {
    flat_tree_iterator_seek(&it, i);
    flat_tree_iterator_sibling(&it);
    assert(it.index == flat_tree_sibling(i));
  }

  return 0;
}
