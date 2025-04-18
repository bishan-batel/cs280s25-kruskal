#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "disjoint_sets.h"
#include "graph.h"

/**
 * @brief Performs kruskal algorithm on given graph for MST
 */
template<typename Vertex, typename Edge>
auto kruskal(const Graph<Vertex, Edge>& graph) -> std::vector<Edge> {
  const size_t size = graph.Size();

  std::vector<Edge> mst{};
  mst.reserve(size - 1);

  std::vector<Edge> edges{graph.GetEdges().begin(), graph.GetEdges().end()};

  std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
    return a.Weight() < b.Weight();
  });

  DisjointSets set{size};

  for (size_t i = 0; i < size; i++) {
    set.Make();
  }

  // Step 4: Add edges to MST if they don't form a cycle
  for (const Edge& edge: edges) {

    const size_t u = edge.ID1();
    const size_t v = edge.ID2();

    const size_t rep1 = set.GetRepresentative(u);
    const size_t rep2 = set.GetRepresentative(v);

    if (rep1 != rep2) {
      set.Join(u, v);
      mst.push_back(edge);

      if (mst.size() == size - 1) {
        break;
      }
    }
  }

  return mst;
}

#endif
