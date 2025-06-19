from typing import Self

class Gather:
    """
    A seismic gather.
    """

    id: int
    nt: int
    nx: int
    dt: float
    data: list[float]

    def __init__(
        self, id: int = 0, nt: int = 0, nx: int = 0, dt: float = 0
    ) -> Self: ...
    @staticmethod
    def from_bin_file(
        filename: str,
        nt: int = 0,
        nx: int = 0,
        dt: float | None = 0.0,
    ) -> Gather:
        """
        Load gather data from a binary file.

        Returns:
            Self: An instance of Gather with data loaded.
        """
