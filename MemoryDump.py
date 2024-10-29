class MemDump:
    def __init__(self, base_location=None, base_address=0, size=0, path="", start_reading=0):
        if base_location is not None:
            # Assuming base_location is a bytes-like object
            self._mem_dump = base_location[:size]
        else:
            self._mem_dump = bytearray(size)
            if path:
                self.load_binary(path, size, start_reading)

        self._base_address = base_address
        self._size = size
        self._path = path

    def __eq__(self, other):
        if not isinstance(other, MemDump):
            return NotImplemented
        return (self._mem_dump == other._mem_dump and
                self._base_address == other._base_address and
                self._size == other._size and
                self._path == other._path)

    def load_binary(self, path, size, start_reading):
        try:
            with open(path, 'rb') as file:
                file.seek(start_reading)
                self._mem_dump = file.read(size)
        except IOError:
            self._mem_dump = bytearray()

    def get_dump(self, data_type):
        # Assuming data_type is a callable that can process the string
        return data_type(self._mem_dump)

    def get_base_address(self):
        return self._base_address

    def get_size(self):
        return self._size

    def get_path(self):
        return self._path