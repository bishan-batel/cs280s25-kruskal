#include "disjoint_sets.h"
#include <iostream>
#include <utility>

// class Node implementation
Node::Node(size_t value): next{nullptr}, value(value) {}

Node* Node::get_next() { return next; }

auto Node::set_next(Node* new_next) -> void { next = std::move(new_next); }

auto Node::get_value() const -> size_t { return value; }

auto operator<<(std::ostream& os, const Node& node) -> std::ostream& {
  os << "(" << node.value << " ) -> ";
  return os;
}

Head::Head() = default;

Head::~Head() {
  for (size_t i = 0; i < length; ++i) {
    delete std::exchange(first, first->get_next());
  }
}

auto Head::size() const -> size_t { return length; }

auto Head::get_first() const -> Node* { return first; }

auto Head::get_last() const -> Node* { return last; }

auto Head::init(size_t value) -> void {
  first = new Node{value};
  last = first;
  length = 1;
}

auto Head::join(Head& head2) -> void {
  length += std::exchange(head2.length, 0);

  if (length == 0) {
    first = std::exchange(head2.first, nullptr);
  } else {
    last->set_next(std::exchange(head2.first, nullptr));
  }

  last = std::exchange(head2.last, nullptr);
}

auto operator<<(std::ostream& os, const Head& head) -> std::ostream& {
  os << "[" << head.length << " ] -> ";
  return os;
}

// class DisjointSets implementation
DisjointSets::DisjointSets(const size_t capacity):
    size(0),
    capacity(capacity),
    representatives{new size_t[capacity]},
    heads{new Head[capacity]} {}

auto DisjointSets::Make() -> void {
  // if (size == capacity) {
  //   throw "DisjointSets::Make(...) out of space";
  // }
  heads[size].init(size);
  representatives[size] = size;
  ++size;
}

auto DisjointSets::Join(const size_t id1, const size_t id2) -> void {
  size_t rep1 = GetRepresentative(id1);
  size_t rep2 = GetRepresentative(id2);

  if (rep1 == rep2) {
    return;
  }

  if (heads[rep2].size() < heads[rep1].size()) {
    std::swap(rep1, rep2);
  }

  Node* current = heads[rep2].get_last();
  heads[rep2].join(heads[rep1]);

  current = current->get_next();

  // update representative refs
  while (current) {
    representatives[current->get_value()] = rep2;
    current = current->get_next();
  }

  std::ignore = GetRepresentative(id1);
  std::ignore = GetRepresentative(id2);
}

auto DisjointSets::GetRepresentative(const size_t id) const -> size_t {
  if (representatives[id] != id) {
    representatives[id] = GetRepresentative(representatives[id]);
  }
  return representatives[id];
}

auto DisjointSets::operator[](const size_t id) const -> size_t {
  return representatives[id];
}

auto operator<<(std::ostream& os, const DisjointSets& ds) -> std::ostream& {
  for (size_t i = 0; i < ds.size; ++i) {
    os << i << ":  ";
    Head* p_head = &ds.heads[i];
    os << *p_head;
    Node* p_node = p_head->get_first();
    while (p_node) {
      os << *p_node;
      p_node = p_node->get_next();
    }
    os << "NULL (representative " << ds.representatives[i] << ")\n";
  }
  return os;
}
