import datetime
from dataclasses import dataclass
from enum import Enum

import config
import runner


@dataclass
class TestResult:
    time_elapsed: datetime.timedelta


class Algorithm(Enum):
    DIJKSTRAS = 'dijkstras'
    BELLMANFORD = 'bellmanFord'
    FLOYDWARSHALL = 'floydWarshall'
    ASTAR = 'aStar'


def run_test(algorithm: Algorithm, graph, end: int,
             runs: int = 1) -> TestResult:
    data = runner.ProcessRunData([algorithm.value, str(end), str(runs)], [repr(graph)])
    result = runner.run(config.MEASUREMENT_TOOL_PATH, data)
    return TestResult(datetime.timedelta(microseconds=int(result.stdout)))
