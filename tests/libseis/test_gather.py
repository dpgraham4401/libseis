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

    def test_read_gather(self, seismic_trace_1d_file):
        """Test reading a gather."""
        # Assuming the Gather class has a method to read data
        gather = Gather.from_bin_file(seismic_trace_1d_file, 4, 1, 0.004)
        assert isinstance(gather.data, list)
