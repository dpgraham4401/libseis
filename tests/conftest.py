from pathlib import Path

import pytest


@pytest.fixture
def seismic_trace_1d_file() -> str:
    """Fixture to create a 1D seismic trace."""
    trace_path = Path(__file__).parent / "fixtures" / "testTrace.bin"
    return trace_path.as_posix()
