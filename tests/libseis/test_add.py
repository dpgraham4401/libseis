from libseis import add, add_one


class TestLibseis:
    """This is just here while we set up pybind11, cmake, pytest, etc.

    The add example function can be removed once we're at a place where we don't
    need to test the build system.
    """

    def test_add(self):
        expected = 7
        assert add(3, 4) == expected

    def test_add_one(self):
        expected = 4
        assert add_one(3) == expected
