import ctypes


class SorterCpp:
    def __init__(self, lib: ctypes.CDLL) -> None:
        lib.init.argtypes = []
        lib.init.restype = ctypes.c_void_p

        lib.sort.argtypes = [
            ctypes.c_void_p,
            ctypes.POINTER(ctypes.c_float),
            ctypes.c_char_p,
            ctypes.c_int,
        ]
        lib.sort.restype = None

        lib.generate.argtypes = [
            ctypes.c_void_p,
            ctypes.POINTER(ctypes.c_float),
            ctypes.c_char_p,
            ctypes.c_int,
        ]
        lib.generate.restype = None

        self.obj = lib.init()
        self.lib = lib
        self.clear()

    def clear(self):
        self.status = ctypes.c_float(0.0)

    def sort(self, path: str, key: int):
        self.clear()
        self.lib.sort(self.obj, ctypes.byref(self.status), path.encode(), key)

    def generate(self, path: str, count: int):
        self.clear()
        self.lib.generate(self.obj, ctypes.byref(self.status), path.encode(), count)

    def value(self) -> float:
        return self.status.value
