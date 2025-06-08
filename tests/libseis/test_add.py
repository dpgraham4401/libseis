import libseis


class TestLibseis:
    def test_add(self):
        expected = 7
        assert libseis.add(3, 4) == expected
