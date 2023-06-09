#include "algorithms.h"
#include "queue"

void dijkstras(DataPackage &package) {
  auto graph = package.adj_list;
  std::vector<int> dist(graph.size(), -1); // -1 = INF

  dist[0] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<>>
      pq;

  pq.emplace(0, 0);

  while (!pq.empty()) {
    auto [dis, ver] = pq.top();
    pq.pop();

    if (ver == package.end_vertex) {
      break;
    }

    for (auto [n_v, n_w] : graph[ver]) {
      if (dist[n_v] == -1 || dist[n_v] > dist[ver] + n_w) {
        dist[n_v] = dist[ver] + n_w;
        pq.emplace(dist[n_v], n_v);
      }
    }
  }
}

void bellmanFord(DataPackage &package) {
  auto graph = package.adj_list;
  auto vertexes = graph.size();
  std::vector<int> dist(vertexes, INT32_MAX);
  dist[0] = 0;

  // BF
  for (int i = 0; i < vertexes - 1; ++i) {
    for (int from = 0; from < vertexes; ++from) {
      for (auto [to, w] : graph[from]) {
        if (dist[to] == INT32_MAX || dist[to] > dist[from] + w) {
          dist[to] = dist[from] + w;
        }
      }
    }
  }

  //  for (int i = 0; i < vertexes - 1; ++i) {
  //    for (int from = 0; from < vertexes; ++from) {
  //      for (auto [to, w] : graph[from]) {
  //        if (dist[to] == INT32_MAX || dist[to] > dist[from] + w) {
  //          dist[to] = INT32_MIN;
  //        }
  //      }
  //    }
  //  }
}

void floydWarshall(DataPackage &package) {
  auto graph = package.adj_matrix;
  auto vertexes = graph.size();
  //  std::vector<std::vector<uint64_t>> graph(n, std::vector<uint64_t>(n,
  //  myMax)); for (int i = 0; i < m; ++i) {
  //    int u, v, w;
  //    std::cin >> u >> v >> w;
  //    graph[u][v] = w;
  //  }

  // Input end
  // Floyd-Warshall

  for (int i = 0; i < vertexes; ++i) {
    graph[i][i] = 0;
  }

  for (int i = 0; i < vertexes; ++i) {
    graph[i][i] = 0;
  }

  for (int k = 0; k < vertexes; ++k) {
    for (int u = 0; u < vertexes; ++u) {
      for (int v = 0; v < vertexes; ++v) {
        if (graph[u][k] != -1 && graph[k][v] != -1) {
          graph[u][v] = std::min(graph[u][v], graph[u][k] + graph[k][v]);
        }
      }
    }
  }
}

void aStar(DataPackage &package) {
  auto &adj_list = package.adj_list;
  size_t end_vertex = package.end_vertex;

  size_t num_vertices = adj_list.size();

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<>>
      pq;

  std::vector<int> cost(num_vertices, std::numeric_limits<int>::max());
  std::vector<bool> visited(num_vertices, false);

  size_t start_vertex = 0;
  cost[start_vertex] = 0;
  pq.emplace(cost[start_vertex], start_vertex);

  while (!pq.empty()) {
    auto current_vertex = pq.top().second;
    pq.pop();

    if (current_vertex == end_vertex) {
      break;
    }

    if (visited[current_vertex]) {
      continue;
    }

    visited[current_vertex] = true;

    for (const auto &neighbor : adj_list[current_vertex]) {
      auto neighbor_vertex = neighbor.first;
      auto edge_cost = neighbor.second;

      int total_cost = cost[current_vertex] + edge_cost;
      if (total_cost < cost[neighbor_vertex]) {
        cost[neighbor_vertex] = total_cost;
        pq.emplace(cost[neighbor_vertex], neighbor_vertex);
      }
    }
  }
}