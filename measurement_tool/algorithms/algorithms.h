#ifndef MEASUREMENT_TOOL_ALGORITHMS_H_
#define MEASUREMENT_TOOL_ALGORITHMS_H_

#include <vector>

// Structure that contains data for sorting functions
struct DataPackage {
  DataPackage(std::vector<std::vector<std::pair<int, int>>> &adj_list,
              std::vector<std::vector<int>> &adj_matrix, size_t end_vertex)
      : adj_list(adj_list), adj_matrix(adj_matrix), end_vertex(end_vertex) {}

  std::vector<std::vector<std::pair<int, int>>> &adj_list;
  std::vector<std::vector<int>> &adj_matrix;
  size_t end_vertex = 0;
};

void dijkstras(DataPackage &package);
void bellmanFord(DataPackage &package);
void floydWarshall(DataPackage &package);
void aStar(DataPackage &package);

#endif
