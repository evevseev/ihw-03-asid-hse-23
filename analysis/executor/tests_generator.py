import random
from dataclasses import dataclass

from enum import Enum


class GraphType(Enum):
    DENSE = 'dense'
    SPARSE = 'sparse'
    CONNECTED = 'connected'


class Graph:

    def __init__(self):
        self.vertexes: int = 0
        self.edges: int = 0

        self.adj_list: list[list[tuple[int, int]]] = []

    def add_vertex(self):
        self.vertexes += 1
        self.adj_list.append([])

    def add_edge(self, u: int, v: int, weight: int):
        self.edges += 1
        self.adj_list[u].append((v, weight))
        self.adj_list[v].append((u, weight))

    def _get_edges(self):
        for u, adj in enumerate(self.adj_list):
            for v, weight in adj:
                yield u, v, weight

    def __repr__(self):
        return f'{self.vertexes} {self.edges}\n' + \
            '\n'.join(f'{u} {v} {weight}' for u, v, weight in self._get_edges())


@dataclass
class TestData:
    graph: Graph
    end_vertex: int


def random_weight() -> int:
    return random.randint(0, 10)


def get_test(graph_type: GraphType, vertexes: int) -> TestData:
    graph = Graph()

    for i in range(vertexes):
        graph.add_vertex()

        if i == 0:
            continue

        if graph_type == GraphType.DENSE:
            for j in range(i):
                graph.add_edge(i, j, random_weight())

        else:
            graph.add_edge(random.randint(0, i), i, random_weight())

    if graph_type == GraphType.CONNECTED:
        for i in range(vertexes // 2 // 2 * vertexes):
            rand1, rand2 = random.randint(0, vertexes - 1), random.randint(0, vertexes - 1)
            graph.add_edge(rand1, rand2, random_weight())

    end_vertex = 5 * (vertexes - 1) // 6

    return TestData(graph, end_vertex)
