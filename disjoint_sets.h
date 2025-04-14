/*!
  \brief  Disoint sets using quick find implementation (linked lists and
  a look-up table)

Implements:
  ctor (size)
  Make( id )      initialize
  Join( id,id )   join 2 sets
  GetRepresentative( id )

Rationale:
  elements of the set are assumed to be contiguous 0,1,2,3,....
*/

#ifndef DISJOINT_SETS_H
#define DISJOINT_SETS_H
#include <cstdlib>
#include <fstream> //ostream, istream

// add Head and Node

class Node final {
public:
  Node(size_t value);

  Node *get_next() const;

  void set_next(Node *new_next);

  size_t get_value() const;

  friend std::ostream &operator<<(std::ostream &os, Node const &node);

private:
  Node *next;
  size_t value;
};

class Head final {
public:
  Head();

  ~Head();

  size_t size() const;

  void reset();

  Node *get_first() const;

  Node *get_last() const;

  void init(size_t value);

  void join(Head *pHead2);

  friend std::ostream &operator<<(std::ostream &os, Head const &head);

private:
  size_t counter{0};
  Node *first{nullptr};
  Node *last{nullptr};
};

////////////////////////////////////////////////////////////
class DisjointSets { // you MAY modify this
public:
  DisjointSets(size_t const &capacity);

  DisjointSets(DisjointSets const &) = delete;

  DisjointSets &operator=(DisjointSets const &) = delete;

  DisjointSets(DisjointSets &&) = delete;

  DisjointSets &operator=(DisjointSets &&) = delete;

  ~DisjointSets();

  void Make();

  void Join(size_t const &id1, size_t const &id2);

  size_t GetRepresentative(size_t const &id) const;

  size_t operator[](size_t const &id) const;

  friend std::ostream &operator<<(std::ostream &os, DisjointSets const &ds);

private:
  size_t size{0}; // current size
  size_t capacity{0}; // capacity - NOT growing, provided as ctor arg
  size_t *representatives{nullptr}; // look-up table ID -> representative's ID
  Head *heads{nullptr}; // lists' heads
};

#endif
