#ifndef FLATTREE_H
#define FLATTREE_H

#ifdef __cplusplus
extern "C" {
#endif

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
  uint64_t d = flat_tree_depth(i);
  if (d == 0) return i >> 1;
  return i >> (d + 1);
}

static inline uint64_t
flat_tree_parent (uint64_t i) {
  uint64_t d = flat_tree_depth(i);
  return flat_tree_index(d + 1, flat_tree_offset(i) >> 1);
}

static inline uint64_t
flat_tree_sibling (uint64_t i) {
  uint64_t d = flat_tree_depth(i);
  uint64_t o = flat_tree_offset(i);
  return flat_tree_index(d, o & 1 ? o - 1 : o + 1);
}

static inline uint64_t
flat_tree_left_child (uint64_t i) {
  uint64_t d = flat_tree_depth(i);
  if (d == 0) return i;
  return flat_tree_index(d - 1, flat_tree_offset(i) * 2);
}

static inline uint64_t
flat_tree_right_child (uint64_t i) {
  uint64_t d = flat_tree_depth(i);
  if (d == 0) return i;
  return flat_tree_index(d - 1, flat_tree_offset(i) * 2 + 1);
}

static inline uint64_t
flat_tree_left_span (uint64_t i) {
  uint64_t d = flat_tree_depth(i);
  return flat_tree_offset(i) * ((uint64_t) 2 << d);
}

static inline uint64_t
flat_tree_right_span (uint64_t i) {
  uint64_t d = flat_tree_depth(i);
  return (flat_tree_offset(i) + 1) * ((uint64_t) 2 << d) - 2;
}

static inline uint64_t
flat_tree_count (uint64_t i) {
  uint64_t d = flat_tree_depth(i);
  return ((uint64_t) 2 << d) - 1;
}

static inline uint64_t
flat_tree_spans (uint64_t i) {
  uint64_t d = flat_tree_depth(i);
  return (uint64_t) 2 << d;
}

static inline int
flat_tree_full_roots (uint64_t index, uint64_t *roots) {
  int len = 0;
  uint64_t tmp = index / 2;
  uint64_t offset = 0;
  uint64_t factor = 1;

  while (tmp > 0) {
    while (factor * 2 <= tmp) factor *= 2;
    roots[len++] = offset + factor - 1;
    offset += factor * 2;
    tmp -= factor;
    factor = 1;
  }

  return len;
}

#ifdef __cplusplus
}
#endif

#endif
