import subprocess
from dataclasses import dataclass


@dataclass(frozen=True, repr=True)
class ProcessRunData:
    args: list[str]
    stdin: list[str]


@dataclass(frozen=True, repr=True)
class ProcessRunResult:
    stdout: str
    stderr: str


class TestRunException(Exception):
    def __init__(self, message: str, params: ProcessRunData, return_code: int, stdout: str = None, stderr: str = None):
        super().__init__(message)
        self.message = message
        self.params = params
        self.return_code = return_code
        self.stdout = stdout
        self.stderr = stderr

    def __repr__(self):
        return f'{self.__class__.__name__}({self.message}, {self.params}, {self.return_code}, {self.stdout}, {self.stderr})'


# Function to run the sort and return the time and the number of comparisons
def run(exe: str, data: ProcessRunData) -> ProcessRunResult:
    process = subprocess.run([exe] + data.args, input=' '.join((str(i) for i in data.stdin)),
                             text=True,
                             capture_output=True)

    # If the sort failed, print the error and raise an exception
    if process.returncode != 0:
        raise TestRunException("Non 0 code returned", data, process.returncode, process.stdout, process.stderr)

    return ProcessRunResult(process.stdout, process.stderr)
