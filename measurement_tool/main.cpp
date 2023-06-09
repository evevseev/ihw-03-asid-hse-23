#include "algorithms/algorithms.h"
#include "iostream"
#include "unordered_set"
#include "utils/time_it.h"

using sortFunc = void (*)(DataPackage &);

sortFunc getAlgoFunc(std::string &name) {
  if (name == "dijkstras") {
    return dijkstras;
  } else if (name == "bellmanFord") {
    return bellmanFord;
  } else if (name == "floydWarshall") {
    return floydWarshall;
  } else if (name == "aStar") {
    return aStar;
  } else {
    std::cerr << "Unknown sort name: " << name << std::endl;
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cout << "Usage: " << argv[0] << " <algo_name> <end> <runs>";
    return 1;
  }

  std::string algo_name = argv[1];
  size_t end_vertex = std::stoi(argv[2]);
  size_t runs = std::stoi(argv[3]);

  auto func = getAlgoFunc(algo_name);

  uint64_t total_elapsed_time = 0;
  size_t result;

  // Get input
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  size_t n, m;
  std::cin >> n >> m;

  if (end_vertex >= n) {
    std::cerr << "End vertex is out of range" << std::endl;
    exit(1);
  }

  std::vector<std::vector<std::pair<int, int>>> adj_list(n);
  std::vector<std::vector<int>> adj_matrix(n, std::vector<int>(n, -1));

  for (size_t i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    adj_list[u].emplace_back(v, w);
    adj_matrix[u][v] = w;
  }

  // Run!
  for (size_t i = 0; i < runs; ++i) {
    DataPackage package(adj_list, adj_matrix, end_vertex);
    uint64_t elapsed_time = 0;
    elapsed_time += time([&func, &package]() { func(package); });

    total_elapsed_time += elapsed_time;
  }

  std::cout << total_elapsed_time << std::endl;

  return 0;
}
