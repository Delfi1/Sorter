import ctypes


class SorterCpp:
    def __init__(self, lib: ctypes.CDLL) -> None:
        lib.sort.argtypes = [
            ctypes.POINTER(ctypes.c_int),
            ctypes.c_char_p,
            ctypes.c_int,
        ]
        lib.sort.restype = None

        lib.generate.argtypes = [
            ctypes.POINTER(ctypes.c_int),
            ctypes.c_char_p,
            ctypes.c_int,
        ]
        lib.generate.restype = None

        self.lib = lib
        self.clear()

    def clear(self):
        self.status = ctypes.c_int(0)

    def sort(self, path: str, key: int):
        self.clear()
        self.lib.sort(ctypes.byref(self.status), path.encode(), key)

    def generate(self, path: str, count: int):
        self.clear()
        self.lib.generate(ctypes.byref(self.status), path.encode(), count)

    def value(self) -> int:
        return self.status.value
