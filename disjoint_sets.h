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
#include <iostream>
#include <memory>

// add Head and Node

/**
 * @class Node
 * @brief Node for use in disjointed set
 *
 */
class Node final {
public:

  /**
   * @brief Constructor
   *
   * @param value Repr ID
   */
  Node(size_t value);

  /**
   * @brief Gets next node in list
   */
  [[nodiscard]] Node* get_next();

  /**
   * @brief Sets next node in list
   */
  void set_next(Node* new_next);

  /**
   * @brief Gets inner value / repr
   */
  [[nodiscard]] size_t get_value() const;

  /**
   * @brief Prints to output stream
   */
  friend std::ostream& operator<<(std::ostream& os, const Node& node);

private:

  /**
   * @brief Next pointer
   */
  Node* next;

  /**
   * @brief Value
   */
  size_t value;
};

/**
 * @class Head
 * @brief Head list for a linked list of representatives
 *
 */
class Head final {
public:

  /**
   * @brief Default constructor
   */
  Head();

  /**
   * @brief Destructor
   */
  ~Head();

  /**
   * @brief Deleted move cosntructor
   */
  Head(Head&&) = delete;

  /**
   * @brief Deleted copy constructor
   */
  Head(const Head&) = delete;

  /**
   * @brief Deleted move assignment
   */
  auto operator=(Head&&) -> Head& = delete;

  /**
   * @brief Deleted copy assignment
   */
  auto operator=(const Head&) -> Head& = delete;

  /**
   * @brief Gets the amount of nodes in this list
   */
  [[nodiscard]] auto size() const -> size_t;

  /**
   * @brief Gets first node in list
   */
  [[nodiscard]] auto get_first() const -> Node*;

  /**
   * @brief Gest last node in list
   */
  [[nodiscard]] auto get_last() const -> Node*;

  /**
   * @brief Initialises list to have 1 node with represenative 'value'
   */
  auto init(size_t value) -> void;

  /**
   * @brief Gives head to self
   */
  auto join(Head& head2) -> void;

  /**
   * @brief Prints to character ostream
   */
  friend auto operator<<(std::ostream& os, const Head& head) -> std::ostream&;

private:

  size_t length{0};
  Node* first{nullptr};
  Node* last{nullptr};
};

/**
 * @class DisjointSets
 * @brief Disjoint sets class helper for unions
 */
class DisjointSets {
public:

  /**
   * @brief Constructor to create a disjoint list with a fixed inner capacity
   */
  DisjointSets(size_t capacity);

  /**
   * @brief Deleted copy constructor
   */
  DisjointSets(const DisjointSets&) = delete;

  /**
   * @brief Deleted copy assignment
   */
  DisjointSets& operator=(const DisjointSets&) = delete;

  /**
   * @brief Deleted move constructor
   */
  DisjointSets(DisjointSets&&) = delete;

  /**
   * @brief Deleted move assignment
   */
  DisjointSets& operator=(DisjointSets&&) = delete;

  /**
   * @brief Creates a new representative with ID of the current size
   */
  auto Make() -> void;

  /**
   * @brief Joins the two represntatives together
   */
  auto Join(size_t id1, size_t id2) -> void;

  /**
   * @brief Gets representative index from the given id
   */
  [[nodiscard]] auto GetRepresentative(size_t id) const -> size_t;

  /**
   * @brief Raw index into the representative array
   */
  [[nodiscard]] auto operator[](size_t id) const -> size_t;

  /**
   * @brief Prints self to character ostream
   */
  friend auto operator<<(std::ostream& os, const DisjointSets& ds)
    -> std::ostream&;

private:

  // current size
  size_t size{0};

  // capacity - NOT growing, provided as ctor arg
  size_t capacity{0};

  // look-up table ID -> representative's ID
  std::unique_ptr<size_t[]> representatives{nullptr};

  // lists' heads
  std::unique_ptr<Head[]> heads{nullptr};
};

#endif
