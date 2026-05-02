#include <assert.h>
#include "../include/flattree.h"

int
main () {
  flat_tree_iterator_t it;

  /* init / seek */
  flat_tree_iterator_init(&it, 0);
  assert(it.index == 0 && it.depth == 0 && it.offset == 0);
  assert(flat_tree_iterator_is_leaf(&it));

  flat_tree_iterator_init(&it, 3);
  assert(it.index == 3 && it.depth == 2 && it.offset == 0);
  assert(!flat_tree_iterator_is_leaf(&it));

  flat_tree_iterator_seek(&it, 5);
  assert(it.index == 5 && it.depth == 1 && it.offset == 1);

  /* parent */
  flat_tree_iterator_init(&it, 0);
  flat_tree_iterator_parent(&it);
  assert(it.index == 1 && it.depth == 1 && it.offset == 0);
  flat_tree_iterator_parent(&it);
  assert(it.index == 3 && it.depth == 2 && it.offset == 0);

  flat_tree_iterator_init(&it, 6);
  flat_tree_iterator_parent(&it);
  assert(it.index == 5);
  flat_tree_iterator_parent(&it);
  assert(it.index == 3);

  /* left_child / right_child */
  flat_tree_iterator_init(&it, 3);
  flat_tree_iterator_left_child(&it);
  assert(it.index == 1 && it.depth == 1 && it.offset == 0);
  flat_tree_iterator_right_child(&it);
  assert(it.index == 2 && it.depth == 0 && it.offset == 1);

  flat_tree_iterator_init(&it, 0);
  flat_tree_iterator_left_child(&it);
  assert(it.index == 0);

  /* sibling */
  flat_tree_iterator_init(&it, 0);
  flat_tree_iterator_sibling(&it);
  assert(it.index == 2 && it.offset == 1);
  flat_tree_iterator_sibling(&it);
  assert(it.index == 0 && it.offset == 0);

  flat_tree_iterator_init(&it, 1);
  flat_tree_iterator_sibling(&it);
  assert(it.index == 5 && it.offset == 1);

  /* is_left / is_right */
  flat_tree_iterator_init(&it, 0);
  assert(flat_tree_iterator_is_left(&it));
  assert(!flat_tree_iterator_is_right(&it));
  flat_tree_iterator_init(&it, 2);
  assert(!flat_tree_iterator_is_left(&it));
  assert(flat_tree_iterator_is_right(&it));
  flat_tree_iterator_init(&it, 1);
  assert(flat_tree_iterator_is_left(&it));
  flat_tree_iterator_init(&it, 5);
  assert(flat_tree_iterator_is_right(&it));

  /* next / prev */
  flat_tree_iterator_init(&it, 0);
  flat_tree_iterator_next(&it);
  assert(it.index == 2 && it.offset == 1);
  flat_tree_iterator_next(&it);
  assert(it.index == 4 && it.offset == 2);
  flat_tree_iterator_prev(&it);
  assert(it.index == 2 && it.offset == 1);

  flat_tree_iterator_init(&it, 1);
  flat_tree_iterator_next(&it);
  assert(it.index == 5 && it.offset == 1);

  flat_tree_iterator_init(&it, 0);
  flat_tree_iterator_prev(&it);
  assert(it.index == 0);

  /* next_tree / prev_tree */
  flat_tree_iterator_init(&it, 0);
  flat_tree_iterator_next_tree(&it);
  assert(it.index == 2 && it.depth == 0);
  flat_tree_iterator_next_tree(&it);
  assert(it.index == 4 && it.depth == 0);

  flat_tree_iterator_init(&it, 3);
  flat_tree_iterator_next_tree(&it);
  assert(it.index == 8 && it.depth == 0);

  flat_tree_iterator_init(&it, 4);
  flat_tree_iterator_prev_tree(&it);
  assert(it.index == 2 && it.depth == 0);
  flat_tree_iterator_prev_tree(&it);
  assert(it.index == 0 && it.depth == 0);
  flat_tree_iterator_prev_tree(&it);
  assert(it.index == 0 && it.depth == 0);

  /* contains */
  flat_tree_iterator_init(&it, 3);
  assert(flat_tree_iterator_contains(&it, 0));
  assert(flat_tree_iterator_contains(&it, 1));
  assert(flat_tree_iterator_contains(&it, 2));
  assert(flat_tree_iterator_contains(&it, 3));
  assert(flat_tree_iterator_contains(&it, 4));
  assert(flat_tree_iterator_contains(&it, 5));
  assert(flat_tree_iterator_contains(&it, 6));
  assert(!flat_tree_iterator_contains(&it, 7));
  assert(!flat_tree_iterator_contains(&it, 8));

  flat_tree_iterator_init(&it, 0);
  assert(flat_tree_iterator_contains(&it, 0));
  assert(!flat_tree_iterator_contains(&it, 1));
  assert(!flat_tree_iterator_contains(&it, 2));

  /* count / count_leaves */
  flat_tree_iterator_init(&it, 0);
  assert(flat_tree_iterator_count(&it) == 1);
  assert(flat_tree_iterator_count_leaves(&it) == 1);

  flat_tree_iterator_init(&it, 1);
  assert(flat_tree_iterator_count(&it) == 3);
  assert(flat_tree_iterator_count_leaves(&it) == 2);

  flat_tree_iterator_init(&it, 3);
  assert(flat_tree_iterator_count(&it) == 7);
  assert(flat_tree_iterator_count_leaves(&it) == 4);

  flat_tree_iterator_init(&it, 7);
  assert(flat_tree_iterator_count(&it) == 15);
  assert(flat_tree_iterator_count_leaves(&it) == 8);

  /* peek_left_span / peek_right_span */
  flat_tree_iterator_init(&it, 3);
  assert(flat_tree_iterator_peek_left_span(&it) == 0);
  assert(flat_tree_iterator_peek_right_span(&it) == 6);
  assert(it.index == 3);

  flat_tree_iterator_init(&it, 5);
  assert(flat_tree_iterator_peek_left_span(&it) == 4);
  assert(flat_tree_iterator_peek_right_span(&it) == 6);
  assert(it.index == 5);

  /* left_span / right_span (mutating) */
  flat_tree_iterator_init(&it, 3);
  flat_tree_iterator_left_span(&it);
  assert(it.index == 0 && it.depth == 0 && it.offset == 0);

  flat_tree_iterator_init(&it, 3);
  flat_tree_iterator_right_span(&it);
  assert(it.index == 6 && it.depth == 0 && it.offset == 3);

  flat_tree_iterator_init(&it, 5);
  flat_tree_iterator_left_span(&it);
  assert(it.index == 4 && it.depth == 0);

  flat_tree_iterator_init(&it, 5);
  flat_tree_iterator_right_span(&it);
  assert(it.index == 6 && it.depth == 0);

  /* full_root */
  flat_tree_iterator_init(&it, 0);
  assert(flat_tree_iterator_full_root(&it, 8));
  assert(it.index == 3 && it.depth == 2);

  flat_tree_iterator_init(&it, 0);
  assert(flat_tree_iterator_full_root(&it, 4));
  assert(it.index == 1 && it.depth == 1);

  flat_tree_iterator_init(&it, 0);
  assert(!flat_tree_iterator_full_root(&it, 0));
  flat_tree_iterator_init(&it, 3);
  assert(!flat_tree_iterator_full_root(&it, 8));

  /* is_root */
  flat_tree_iterator_init(&it, 1);
  assert(flat_tree_iterator_is_root(&it, 2));
  assert(!flat_tree_iterator_is_root(&it, 4));

  flat_tree_iterator_init(&it, 3);
  assert(flat_tree_iterator_is_root(&it, 4));
  assert(!flat_tree_iterator_is_root(&it, 8));

  flat_tree_iterator_init(&it, 0);
  assert(flat_tree_iterator_is_root(&it, 1));
  assert(!flat_tree_iterator_is_root(&it, 2));

  /* iterator matches free functions for all nodes 0..63 */
  for (uint64_t i = 0; i < 64; i++) {
    flat_tree_iterator_seek(&it, i);
    assert(it.index == i);
    assert(it.depth == flat_tree_depth(i));
    assert(it.offset == flat_tree_offset(i));
    assert(flat_tree_iterator_peek_left_span(&it) == flat_tree_left_span(i));
    assert(flat_tree_iterator_peek_right_span(&it) == flat_tree_right_span(i));
    assert(flat_tree_iterator_count(&it) == flat_tree_count(i));
  }

  for (uint64_t i = 0; i < 64; i++) {
    flat_tree_iterator_seek(&it, i);
    flat_tree_iterator_parent(&it);
    assert(it.index == flat_tree_parent(i));
  }

  for (uint64_t i = 0; i < 64; i++) {
    flat_tree_iterator_seek(&it, i);
    flat_tree_iterator_sibling(&it);
    assert(it.index == flat_tree_sibling(i));
  }

  return 0;
}
