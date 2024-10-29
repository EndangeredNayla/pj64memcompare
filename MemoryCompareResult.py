import os, shutil
from typing import List, Optional

class MemCompareResult:
    DUMP_STARTING_ADDRESS = 0
    RESULT_COUNT = 8
    ITERATION = 0x10
    VALUE_WIDTH = 0x12
    ADDRESS_WIDTH = 0x14
    PLACEHOLDER = 0x15
    HEADER_SIZE = 0x20

    _path: str = ""

    def __init__(self, path: str, iteration: int, address_width: int, value_width: int, range_count: int = 0, cached: bool = False, zip: bool = False):
        self._addresses: List[bytes] = []
        self._values: List[bytes] = []
        self._previous_values: List[bytes] = []
        self._indices: List[int] = []
        self._starting_addresses: List[int] = []
        self._result_counts: List[int] = []
        self._file_headers: List[str] = []
        self._path = path
        self._range_count = range_count
        self._total_result_count = 0
        self._address_width = address_width
        self._value_width = value_width
        self._file_size = 0
        self._iteration = iteration
        self._cached = cached
        self._zipped = zip

    def create_header(self, index: int):
        header = bytearray(16)
        header[0:8] = self._starting_addresses[index].to_bytes(8, 'little')
        header[8:16] = self._result_counts[index].to_bytes(8, 'little')
        header[16:18] = self._iteration.to_bytes(2, 'little')
        header[18:20] = self._value_width.to_bytes(2, 'little')
        header[20:21] = self._address_width.to_bytes(1, 'little')
        header[21:29] = (0).to_bytes(8, 'little')
        self._file_headers.append(header)

    def set_new_range(self, starting_address: int):
        self._starting_addresses.append(starting_address)
        self._result_counts.append(0)
        self._indices.append(len(self._addresses) // self._address_width)

    def push_back_result_by_ptr(self, address, value: bytes, previous_value: Optional[bytes] = None):
        self._addresses.extend(address.to_bytes(self._address_width, 'little'))
        self._values.extend(value[:self._value_width])

        if self._iteration > 1 and previous_value is not None:
            self._previous_values.extend(previous_value[:self._value_width])

        self._result_counts[-1] += 1
        self._total_result_count += 1

    def get_range_index_of_starting_address(self, starting_address: int) -> int:
        try:
            return self._starting_addresses.index(starting_address)
        except ValueError:
            return -1

    def get_addresses_ptr_all_ranges(self):
        return self._addresses

    def get_values_ptr_all_ranges(self):
        return self._values

    def get_previous_values_ptr_all_ranges(self):
        return self._previous_values

    def get_addresses_ptr_of_range(self, starting_address: int):
        index = self.get_range_index_of_starting_address(starting_address)
        if index == -1 or self._result_counts[index] == 0:
            return None
        return self._addresses[self._indices[index] * self._address_width:]

    def get_values_ptr_of_range(self, starting_address: int):
        index = self.get_range_index_of_starting_address(starting_address)
        if index == -1 or self._result_counts[index] == 0:
            return None
        return self._values[self._indices[index] * self._value_width:]

    def get_previous_values_ptr_of_range(self, starting_address: int):
        index = self.get_range_index_of_starting_address(starting_address)
        if index == -1 or self._result_counts[index] == 0:
            return None
        return self._previous_values[self._indices[index] * self._value_width:]

    def get_total_result_count(self) -> int:
        return self._total_result_count

    def get_result_count_by_range_index(self, index: int) -> int:
        return self._result_counts[index]

    def get_result_count_of_range(self, starting_address: int) -> int:
        index = self.get_range_index_of_starting_address(starting_address)
        if index == -1:
            return 0
        return self._result_counts[index]

    def clear(self, keep_iteration_count: bool = False):
        self._addresses.clear()
        self._values.clear()
        self._previous_values.clear()
        self._indices.clear()
        self._starting_addresses.clear()
        self._result_counts.clear()
        self._file_headers.clear()
        self._total_result_count = 0
        if not keep_iteration_count:
            self._iteration = 0

    def set_value_width(self, width: int):
        self._value_width = width

    def set_address_width(self, width: int):
        self._address_width = width

    def save_results(self, range_index: int, zipped: bool) -> bool:
        if range_index == -1:
            return False

        self.create_header(range_index)
        path = os.path.join(self._path, str(self._iteration - 1))
        os.makedirs(path, exist_ok=True)
        path = os.path.join(path, f"{range_index}.bin")

        if not self.save_binary(path, self._file_headers[range_index], self.HEADER_SIZE, False, zipped):
            return False

        if not self._addresses:
            return True

        if not self.save_binary(path, self._addresses, self._result_counts[range_index] * self._address_width, True, zipped):
            return False

        if not self.save_binary(path, self._values, self._result_counts[range_index] * self._value_width, True, zipped):
            return False

        if self._iteration > 1:
            if not self.save_binary(path, self._previous_values, self._result_counts[range_index] * self._value_width, True, zipped):
                return False

        return True

    @staticmethod
    def save_binary(file_path: str, data: bytes, size: int, append: bool, zip: bool) -> bool:
        mode = 'ab' if append else 'wb'
        try:
            with open(file_path, mode) as file:
                file.write(data[:size])
            return True
        except IOError:
            return False

    @staticmethod
    def load_binary(file_path: str, out: bytearray, size: int, start_pos: int) -> bool:
        try:
            with open(file_path, 'rb') as file:
                file.seek(start_pos)
                out.extend(file.read(size))
            return True
        except IOError:
            return False

    def get_value_width(self) -> int:
        return self._value_width

    def get_range_count(self) -> int:
        return self._range_count

    @staticmethod
    def clear_results_dir(iteration_index: int, remove_iteration_dir: bool = False):
        # Construct the path to the iteration directory
        iteration_dir = os.path.join(MemCompareResults._path, str(iteration_index))
        
        # Check if the directory exists
        if os.path.exists(iteration_dir):
            if remove_iteration_dir:
                # Remove the entire directory
                shutil.rmtree(iteration_dir)
            else:
                # Remove only the files within the directory
                for filename in os.listdir(iteration_dir):
                    file_path = os.path.join(iteration_dir, filename)
                    try:
                        if os.path.isfile(file_path) or os.path.islink(file_path):
                            os.unlink(file_path)
                        elif os.path.isdir(file_path):
                            shutil.rmtree(file_path)
                    except Exception as e:
                        print(f'Failed to delete {file_path}. Reason: {e}')

    @staticmethod
    def set_results_dir(dir: str):
        MemCompareResults._path = dir