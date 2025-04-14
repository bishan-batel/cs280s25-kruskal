#include "disjoint_sets.h"

// class Node implementation
Node::Node(size_t value) : next(), value(value) {}

Node *Node::get_next() const { return next; }

void Node::set_next(Node *new_next) { next = new_next; }

size_t Node::get_value() const { return value; }

std::ostream &operator<<(std::ostream &os, Node const &node) {
  os << "(" << node.value << " ) -> ";
  return os;
}

// class Head implementation
Head::Head() = default;

Head::~Head() { /* .... */ }

size_t Head::size() const { return counter; }

void Head::reset() {
  counter = 0;
  last = nullptr;
  first = nullptr;
}

Node *Head::get_first() const { return first; }

Node *Head::get_last() const { return last; }

void Head::init(size_t value) {
  first = last = new Node{value};
  counter = 1;
}

void Head::join(Head *head2) {}

std::ostream &operator<<(std::ostream &os, Head const &head) {
  os << "[" << head.counter << " ] -> ";
  return os;
}

// class DisjointSets implementation
DisjointSets::DisjointSets(size_t const &capacity) :
    size(0), capacity(capacity), representatives(new size_t[capacity]), heads(new Head[capacity]) {}

DisjointSets::~DisjointSets() {
  delete[] heads;
  delete[] representatives;
}

void DisjointSets::Make() {
  if (size == capacity) throw "DisjointSets::Make(...) out of space";
  heads[size].init(size);
  representatives[size] = size;
  ++size;
}

void DisjointSets::Join(size_t const &id1, size_t const &id2) {}

size_t DisjointSets::GetRepresentative(size_t const &id) const { return representatives[id]; }

size_t DisjointSets::operator[](size_t const &id) const { return representatives[id]; }

std::ostream &operator<<(std::ostream &os, DisjointSets const &ds) {
  for (size_t i = 0; i < ds.size; ++i) {
    os << i << ":  ";
    Head *p_head = &ds.heads[i];
    os << *p_head;
    Node *p_node = p_head->get_first();
    while (p_node) {
      os << *p_node;
      p_node = p_node->get_next();
    }
    os << "NULL (representative " << ds.representatives[i] << ")\n";
  }
  return os;
}
