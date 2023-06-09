import logging
from collections import defaultdict
from dataclasses import dataclass

from tqdm import tqdm

import config
import tests_runner as tr
from tests_generator import get_test, GraphType


@dataclass(frozen=True, repr=True)
class Test:
    name: str
    graph_type: GraphType
    sizes: range


TESTS = [Test(f"Dense_graph", GraphType.DENSE, range(10, 1011, 50)),
         Test(f"Connected_graph", GraphType.CONNECTED, range(10, 1011, 50)),
         Test(f"Sparse_graph", GraphType.SPARSE, range(10, 1011, 50))]
TESTS = [Test(f"Connected_graph", GraphType.CONNECTED, range(10, 1011, 50))]

logging.basicConfig(level=logging.ERROR)


# disable logging


def main():
    logging.info("Program started!")
    with tqdm(total=len(TESTS) * len(tr.Algorithm) * len(range(10, 1011, 50)) * config.RUNS_PER_TEST) as pbar:
        for test in TESTS:
            logging.info(f"Running: {test.name}")

            with open(config.TESTS_RESULTS_PATH + f'/{test.name}.csv', 'w') as f:
                tests_results: dict[str, list[tuple[int, int, int]]] = defaultdict(
                    list)  # algo -> [(vertexes, edges, time), ...]

                for size in test.sizes:
                    logging.debug(f'= Size {size}')
                    test_data = get_test(test.graph_type, size)
                    graph = test_data.graph
                    for algo in tr.Algorithm:
                        logging.debug(f'- Algo: {algo.value}')
                        total_time = 0
                        for t_n in range(config.RUNS_PER_TEST):
                            total_time += tr.run_test(algo, graph, test_data.end_vertex, 2).time_elapsed.microseconds
                            pbar.update(1)

                        total_time /= config.RUNS_PER_TEST
                        tests_results[algo.name].append((graph.vertexes, graph.edges, total_time))

                test_res_1 = next(iter(tests_results.values()))
                f.write('algo;' + ';'.join(f'{v}@{e}' for v, e, _ in test_res_1) + '\n')

                for algo, results in tests_results.items():
                    f.write(f'{algo};')
                    for ind, result in enumerate(results):
                        f.write(f'{result[2]}')
                        if ind != len(results) - 1:
                            f.write(';')
                    f.write('\n')


if __name__ == '__main__':
    main()
