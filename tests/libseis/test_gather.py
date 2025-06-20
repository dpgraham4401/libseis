import numpy as np
import pytest

from libseis import Gather


class TestSeismicGather:
    """Test the Gather class from."""

    @pytest.fixture
    def gather(self):
        """Fixture to create a Gather instance."""
        return Gather(id=1, nt=2, nx=3, dt=4.0)

    def test_gather_init(self, gather):
        """Test the Gather class base constructor."""
        assert isinstance(gather, Gather)

    @pytest.mark.parametrize("attr", ["id", "dt", "nx", "nt"])
    def test_public_int_attributes(self, gather, attr):
        """Test that the id attribute is publicly accessible."""
        val = 42
        setattr(gather, attr, val)
        assert getattr(gather, attr) == val

    def test_gather_has_str_method(self, gather, capfd):
        """Test the Gather class __str__."""
        print(gather)  # noqa: T201
        out, _ = capfd.readouterr()
        assert "Gather" in out


class TestReadSeismicData:
    """Test reading seismic data."""

    @pytest.fixture
    def nt(self) -> int:
        """Number of time samples."""
        return 4

    @pytest.fixture
    def nx(self) -> int:
        """Number of spatial samples."""
        return 1

    def test_read_gather(self, seismic_trace_1d_file, nt, nx):
        """Test reading a gather."""
        # Assuming the Gather class has a method to read data
        gather = Gather.from_bin_file(seismic_trace_1d_file, nt, nx, 0.004)
        assert isinstance(gather.data, np.ndarray)

    def test_loads_dimensions_correctly(self, seismic_trace_1d_file, nt, nx):
        """Test reading a gather."""
        # Assuming the Gather class has a method to read data
        NUM_DIM = 2
        gather = Gather.from_bin_file(seismic_trace_1d_file, nt, nx, 0.004)
        assert gather.data.ndim == NUM_DIM
        assert gather.data.size == nt * nx
