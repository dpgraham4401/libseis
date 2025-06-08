import libseis


class TestLibseis:
    def test_add(self):
        expected = 7
        assert libseis.add(3, 4) == expected

    def test_add_one(self):
        expected = 4
        assert libseis.add_one(3) == expected
