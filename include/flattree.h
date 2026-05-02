#ifndef FLATTREE_H
#define FLATTREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

static inline uint64_t
flat_tree_depth (uint64_t i) {
  return __builtin_ctzll(~i);
}

static inline uint64_t
flat_tree_index (uint64_t depth, uint64_t offset) {
  return (1 + 2 * offset) * ((uint64_t) 1 << depth) - 1;
}

static inline uint64_t
flat_tree_offset (uint64_t i) {
  return i >> (flat_tree_depth(i) + 1);
}

static inline uint64_t
flat_tree_parent (uint64_t i) {
  uint64_t d = flat_tree_depth(i);
  uint64_t step = (uint64_t) 1 << d;
  return (i >> (d + 1)) & 1 ? i - step : i + step;
}

static inline uint64_t
flat_tree_sibling (uint64_t i) {
  return i ^ ((uint64_t) 2 << flat_tree_depth(i));
}

static inline uint64_t
flat_tree_left_child (uint64_t i) {
  uint64_t d = flat_tree_depth(i);
  if (d == 0) return i;
  return i - ((uint64_t) 1 << (d - 1));
}

static inline uint64_t
flat_tree_right_child (uint64_t i) {
  uint64_t d = flat_tree_depth(i);
  if (d == 0) return i;
  return i + ((uint64_t) 1 << (d - 1));
}

static inline uint64_t
flat_tree_left_span (uint64_t i) {
  uint64_t d = flat_tree_depth(i);
  return i & ~(((uint64_t) 2 << d) - 1);
}

static inline uint64_t
flat_tree_right_span (uint64_t i) {
  uint64_t d = flat_tree_depth(i);
  return (i | (((uint64_t) 2 << d) - 1)) - 1;
}

static inline uint64_t
flat_tree_count (uint64_t i) {
  return ((uint64_t) 2 << flat_tree_depth(i)) - 1;
}

static inline uint64_t
flat_tree_spans (uint64_t i) {
  return (uint64_t) 2 << flat_tree_depth(i);
}

static inline int
flat_tree_full_roots (uint64_t index, uint64_t *roots) {
  int len = 0;
  uint64_t tmp = index / 2;
  uint64_t offset = 0;

  while (tmp > 0) {
    uint64_t factor = (uint64_t) 1 << (63 - __builtin_clzll(tmp));
    roots[len++] = offset + factor - 1;
    offset += factor * 2;
    tmp -= factor;
  }

  return len;
}

typedef struct {
  uint64_t index;
  uint64_t depth;
  uint64_t offset;
} flat_tree_iterator_t;

static inline void
flat_tree_iterator_seek (flat_tree_iterator_t *it, uint64_t index) {
  it->index = index;
  it->depth = flat_tree_depth(index);
  it->offset = index >> (it->depth + 1);
}

static inline void
flat_tree_iterator_init (flat_tree_iterator_t *it, uint64_t index) {
  flat_tree_iterator_seek(it, index);
}

static inline uint64_t
flat_tree_iterator_index (flat_tree_iterator_t *it) {
  return it->index;
}

static inline uint64_t
flat_tree_iterator_depth (flat_tree_iterator_t *it) {
  return it->depth;
}

static inline uint64_t
flat_tree_iterator_offset (flat_tree_iterator_t *it) {
  return it->offset;
}

static inline bool
flat_tree_iterator_is_leaf (flat_tree_iterator_t *it) {
  return it->depth == 0;
}

static inline uint64_t
flat_tree_iterator_parent (flat_tree_iterator_t *it) {
  uint64_t step = (uint64_t) 1 << it->depth;
  it->index = it->offset & 1 ? it->index - step : it->index + step;
  it->offset >>= 1;
  it->depth++;
  return it->index;
}

static inline uint64_t
flat_tree_iterator_left_child (flat_tree_iterator_t *it) {
  if (it->depth == 0) return it->index;
  it->depth--;
  it->offset *= 2;
  it->index -= (uint64_t) 1 << it->depth;
  return it->index;
}

static inline uint64_t
flat_tree_iterator_right_child (flat_tree_iterator_t *it) {
  if (it->depth == 0) return it->index;
  it->depth--;
  it->offset = it->offset * 2 + 1;
  it->index += (uint64_t) 1 << it->depth;
  return it->index;
}

static inline uint64_t
flat_tree_iterator_sibling (flat_tree_iterator_t *it) {
  it->index ^= (uint64_t) 2 << it->depth;
  it->offset ^= 1;
  return it->index;
}

static inline bool
flat_tree_iterator_is_left (flat_tree_iterator_t *it) {
  return (it->offset & 1) == 0;
}

static inline bool
flat_tree_iterator_is_right (flat_tree_iterator_t *it) {
  return (it->offset & 1) == 1;
}

static inline uint64_t
flat_tree_iterator_next (flat_tree_iterator_t *it) {
  it->offset++;
  it->index += (uint64_t) 2 << it->depth;
  return it->index;
}

static inline uint64_t
flat_tree_iterator_prev (flat_tree_iterator_t *it) {
  if (it->offset == 0) return it->index;
  it->offset--;
  it->index -= (uint64_t) 2 << it->depth;
  return it->index;
}

static inline uint64_t
flat_tree_iterator_next_tree (flat_tree_iterator_t *it) {
  it->index += ((uint64_t) 1 << it->depth) + 1;
  it->offset = it->index >> 1;
  it->depth = 0;
  return it->index;
}

static inline uint64_t
flat_tree_iterator_prev_tree (flat_tree_iterator_t *it) {
  if (it->offset == 0) {
    it->index = 0;
    it->depth = 0;
    return it->index;
  }
  it->index -= ((uint64_t) 1 << it->depth) + 1;
  it->offset = it->index >> 1;
  it->depth = 0;
  return it->index;
}

static inline bool
flat_tree_iterator_contains (flat_tree_iterator_t *it, uint64_t index) {
  uint64_t half = (uint64_t) 1 << it->depth;
  if (index > it->index) return index < it->index + half;
  if (index < it->index) return it->index - index < half;
  return 1;
}

static inline uint64_t
flat_tree_iterator_count (flat_tree_iterator_t *it) {
  return ((uint64_t) 2 << it->depth) - 1;
}

static inline uint64_t
flat_tree_iterator_count_leaves (flat_tree_iterator_t *it) {
  return (uint64_t) 1 << it->depth;
}

static inline uint64_t
flat_tree_iterator_peek_left_span (flat_tree_iterator_t *it) {
  return it->index & ~(((uint64_t) 2 << it->depth) - 1);
}

static inline uint64_t
flat_tree_iterator_peek_right_span (flat_tree_iterator_t *it) {
  return (it->index | (((uint64_t) 2 << it->depth) - 1)) - 1;
}

static inline uint64_t
flat_tree_iterator_left_span (flat_tree_iterator_t *it) {
  it->index = it->index - ((uint64_t) 1 << it->depth) + 1;
  it->offset = it->index >> 1;
  it->depth = 0;
  return it->index;
}

static inline uint64_t
flat_tree_iterator_right_span (flat_tree_iterator_t *it) {
  it->index = it->index + ((uint64_t) 1 << it->depth) - 1;
  it->offset = it->index >> 1;
  it->depth = 0;
  return it->index;
}

static inline bool
flat_tree_iterator_full_root (flat_tree_iterator_t *it, uint64_t index) {
  if (index <= it->index || it->depth > 0) return 0;
  while (index > it->index + ((uint64_t) 2 << it->depth) + ((uint64_t) 1 << it->depth)) {
    it->index += (uint64_t) 1 << it->depth;
    it->depth++;
    it->offset >>= 1;
  }
  return 1;
}

static inline bool
flat_tree_iterator_is_root (flat_tree_iterator_t *it, uint64_t length) {
  uint64_t half = (uint64_t) 1 << it->depth;
  uint64_t current_length = 1 + (it->index + half - 1) / 2;
  if (length < current_length) return 0;
  uint64_t parent = it->offset & 1 ? it->index - half : it->index + half;
  uint64_t parent_length = 1 + (parent + half * 2 - 1) / 2;
  return parent_length > length;
}

#ifdef __cplusplus
}
#endif

#endif
