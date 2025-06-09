import pytest

from libseis import Gather


class TestSeismicGather:
    """Test the Gather class from."""

    @pytest.fixture
    def gather(self):
        """Fixture to create a Gather instance."""
        return Gather()

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
