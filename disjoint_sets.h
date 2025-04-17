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
#include <memory>

// add Head and Node

class Node final {
public:

  Node(size_t value);

  std::shared_ptr<Node> get_next();

  void set_next(std::shared_ptr<Node> new_next);

  size_t get_value() const;

  friend std::ostream& operator<<(std::ostream& os, const Node& node);

private:

  std::shared_ptr<Node> next;
  size_t value;
};

class Head final {
public:

  Head();

  ~Head();

  size_t size() const;

  void reset();

  std::shared_ptr<Node> get_first() const;

  std::shared_ptr<Node> get_last() const;

  void init(size_t value);

  void join(Head& head2);

  friend std::ostream& operator<<(std::ostream& os, const Head& head);

private:

  size_t length{0};
  std::shared_ptr<Node> first{nullptr};
  std::shared_ptr<Node> last{nullptr};
};

////////////////////////////////////////////////////////////
class DisjointSets { // you MAY modify this
public:

  DisjointSets(size_t capacity);

  DisjointSets(const DisjointSets&) = delete;

  DisjointSets& operator=(const DisjointSets&) = delete;

  DisjointSets(DisjointSets&&) = delete;

  DisjointSets& operator=(DisjointSets&&) = delete;

  void Make();

  void Join(size_t id1, size_t id2);

  size_t GetRepresentative(size_t id) const;

  size_t operator[](size_t id) const;

  friend std::ostream& operator<<(std::ostream& os, const DisjointSets& ds);

private:

  size_t size{0};     // current size
  size_t capacity{0}; // capacity - NOT growing, provided as ctor arg
  std::unique_ptr<size_t[]> representatives{nullptr
  };                  // look-up table ID -> representative's ID
  std::unique_ptr<Head[]> heads{nullptr}; // lists' heads
};

#endif
