class DummyProject64MemoryReader:
    def __init__(self):
        # Initialize with some dummy data if needed
        self.memory = {}

    def read_value(self, location, size):
        # Simulate reading an integer value from memory
        return self.memory.get(location, 0)

    def read_text(self, location, size):
        # Simulate reading a text value from memory
        return self.memory.get(location, "Unknown")[:size]

    def read_bin(self, location, size):
        # Simulate reading binary data from memory
        return self.memory.get(location, b'\x00' * size)[:size]