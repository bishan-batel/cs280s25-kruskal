#include "disjoint_sets.h"

// class Node implementation
Node::Node(size_t value) : next{nullptr}, value(value) {}

std::shared_ptr<Node> Node::get_next() { return next; }

void Node::set_next(std::shared_ptr<Node> new_next) { next = std::move(new_next); }

size_t Node::get_value() const { return value; }

std::ostream &operator<<(std::ostream &os, Node const &node) {
  os << "(" << node.value << " ) -> ";
  return os;
}

// class Head implementation
Head::Head() = default;

Head::~Head() { /* .... */ }

size_t Head::size() const { return length; }

void Head::reset() {
  length = 0;
  last = nullptr;
  first = nullptr;
}

std::shared_ptr<Node> Head::get_first() const { return first; }

std::shared_ptr<Node> Head::get_last() const { return last; }

void Head::init(size_t value) {
  first = std::make_shared<Node>(value);
  last = first;
  length = 1;
}

void Head::join(Head &head2) {
  last->set_next(std::exchange(head2.first, nullptr));
  last = std::exchange(head2.last, nullptr);
  length += std::exchange(head2.length, 0);
}

std::ostream &operator<<(std::ostream &os, Head const &head) {
  os << "[" << head.length << " ] -> ";
  return os;
}

// class DisjointSets implementation
DisjointSets::DisjointSets(const size_t capacity) :
    size(0), capacity(capacity), representatives{new size_t[capacity]}, heads{new Head[capacity]} {}

void DisjointSets::Make() {
  if (size == capacity) throw "DisjointSets::Make(...) out of space";
  heads[size].init(size);
  representatives[size] = size;
  ++size;
}

void DisjointSets::Join(const size_t id1, const size_t id2) {
  Head &head1 = heads[GetRepresentative(id1)];
  Head &head2 = heads[GetRepresentative(id2)];
  head1.join(head2);
  representatives[id2] = 
}

size_t DisjointSets::GetRepresentative(const size_t id) const { return representatives[id]; }

size_t DisjointSets::operator[](const size_t id) const { return representatives[id]; }

std::ostream &operator<<(std::ostream &os, DisjointSets const &ds) {
  for (size_t i = 0; i < ds.size; ++i) {
    os << i << ":  ";
    Head *p_head = &ds.heads[i];
    os << *p_head;
    Node *p_node = p_head->get_first().get();
    while (p_node) {
      os << *p_node;
      p_node = p_node->get_next().get();
    }
    os << "NULL (representative " << ds.representatives[i] << ")\n";
  }
  return os;
}
