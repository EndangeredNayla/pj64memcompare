from typing import Callable, TypeVar, Generic
import struct

T = TypeVar('T')

class DataAccess(Generic[T]):
    def __init__(self, reader: Callable[[T], T]):
        self.reader = reader

    def __call__(self, ptr: T) -> T:
        return self.reader(ptr)

    @staticmethod
    def read(ptr: T) -> T:
        return ptr

    @staticmethod
    def read_reversed(ptr: T) -> T:
        # Determine the format character for the data type
        if isinstance(ptr, int):
            # Assuming 4-byte integer for demonstration
            byte_format = 'I'
        elif isinstance(ptr, float):
            # Assuming 4-byte float
            byte_format = 'f'
        else:
            raise TypeError("Unsupported data type for byte swapping")

        # Pack the data into bytes, reverse the bytes, and unpack it back
        packed_data = struct.pack(byte_format, ptr)
        reversed_data = packed_data[::-1]
        return struct.unpack(byte_format, reversed_data)[0]



class CompareOperator(Generic[T]):
    def __init__(self):
        self.op_simple: Callable[[T, T], bool] = CompareOperator.equal
        self.op_range: Callable[[T, T, T], bool] = CompareOperator.between
        self.op_precision: Callable[[T, T, float], bool] = CompareOperator.equal_precision
        self.op_range_precision: Callable[[T, T, T, float], bool] = CompareOperator.between_precision
        self.op_color: Callable[[T, T, float], bool] = CompareOperator.equal_color

    def __call__(self, current_val: T, old_or_known: T) -> bool:
        return self.op_simple(current_val, old_or_known)

    @staticmethod
    def equal(current_val: T, old_or_known: T) -> bool:
        return current_val == old_or_known

    @staticmethod
    def not_equal(current_val: T, old_or_known: T) -> bool:
        return current_val != old_or_known

    @staticmethod
    def lower(current_val: T, old_or_known: T) -> bool:
        return current_val < old_or_known

    @staticmethod
    def lower_equal(current_val: T, old_or_known: T) -> bool:
        return current_val <= old_or_known

    @staticmethod
    def greater(current_val: T, old_or_known: T) -> bool:
        return current_val > old_or_known

    @staticmethod
    def greater_equal(current_val: T, old_or_known: T) -> bool:
        return current_val >= old_or_known

    @staticmethod
    def And(current_val: T, old_or_known: T) -> bool:
        return (current_val & old_or_known) == old_or_known

    @staticmethod
    def Or(current_val: T, old_or_known: T) -> bool:
        return (current_val & old_or_known) != 0

    @staticmethod
    def dummy(x: T, y: T) -> bool:
        return False

    def range_operator(self, current_val: T, old_or_range_min: T, offset_or_range_max: T) -> bool:
        return self.op_range(current_val, old_or_range_min, offset_or_range_max)

    @staticmethod
    def increased(current_val: T, old: T, offset: T) -> bool:
        return current_val == old + offset

    @staticmethod
    def decreased(current_val: T, old: T, offset: T) -> bool:
        return current_val == old - offset

    @staticmethod
    def between(current_val: T, range_min: T, range_max: T) -> bool:
        return range_min <= current_val <= range_max

    @staticmethod
    def not_between(current_val: T, range_min: T, range_max: T) -> bool:
        return current_val < range_min or current_val > range_max

    @staticmethod
    def dummy_range(x: T, y: T, z: T) -> bool:
        return False

    def precision_operator(self, current_val: T, old_or_known: T, precision: float) -> bool:
        return self.op_precision(current_val, old_or_known, precision)

    @staticmethod
    def equal_precision(current_val: T, old_or_known: T, precision: float) -> bool:
        return old_or_known * precision <= current_val <= old_or_known * (2.0 - precision)

    @staticmethod
    def not_equal_precision(current_val: T, old_or_known: T, precision: float) -> bool:
        return not CompareOperator.equal_precision(current_val, old_or_known, precision)

    @staticmethod
    def lower_precision(current_val: T, old_or_known: T, precision: float) -> bool:
        return current_val < old_or_known * precision

    @staticmethod
    def lower_equal_precision(current_val: T, old_or_known: T, precision: float) -> bool:
        return not CompareOperator.greater_precision(current_val, old_or_known, precision)

    @staticmethod
    def greater_precision(current_val: T, old_or_known: T, precision: float) -> bool:
        return current_val > old_or_known * (2.0 - precision)

    @staticmethod
    def greater_equal_precision(current_val: T, old_or_known: T, precision: float) -> bool:
        return not CompareOperator.lower_precision(current_val, old_or_known, precision)

    @staticmethod
    def dummy_precision(x: T, y: T, z: float) -> bool:
        return False

    def range_precision_operator(self, current_val: T, old_or_range_min: T, offset_or_range_max: T, precision: float) -> bool:
        return self.op_range_precision(current_val, old_or_range_min, offset_or_range_max, precision)

    @staticmethod
    def increased_precision(current_val: T, old: T, offset: T, precision: float) -> bool:
        return CompareOperator.equal_precision(current_val, old + offset, precision)

    @staticmethod
    def decreased_precision(current_val: T, old: T, offset: T, precision: float) -> bool:
        return CompareOperator.equal_precision(current_val, old - offset, precision)

    @staticmethod
    def between_precision(current_val: T, range_min: T, range_max: T, precision: float) -> bool:
        return CompareOperator.greater_equal_precision(current_val, range_min, precision) and CompareOperator.lower_equal_precision(current_val, range_max, precision)

    @staticmethod
    def not_between_precision(current_val: T, range_min: T, range_max: T, precision: float) -> bool:
        return CompareOperator.lower_precision(current_val, range_min, precision) and CompareOperator.greater_precision(current_val, range_max, precision)

    @staticmethod
    def dummy_range_precision(x: T, y: T, z: T, w: float) -> bool:
        return False

    def color_operator(self, current_val, old_or_known, precision: float) -> bool:
        return self.op_color(current_val, old_or_known, precision)

    @staticmethod
    def equal_color(current_val, old_or_known, precision: float) -> bool:
        if not current_val.had_valid_color_source():
            return False
        return old_or_known - (1.0 - precision) <= current_val <= old_or_known + (1.0 - precision)

    @staticmethod
    def not_equal_color(current_val, old_or_known, precision: float) -> bool:
        return not CompareOperator.equal_color(current_val, old_or_known, precision)

    @staticmethod
    def lower_color(current_val, old_or_known, precision: float) -> bool:
        if not current_val.had_valid_color_source():
            return False
        return current_val < old_or_known + (1.0 - precision)

    @staticmethod
    def lower_equal_color(current_val, old_or_known, precision: float) -> bool:
        return not CompareOperator.greater_color(current_val, old_or_known, precision)

    @staticmethod
    def greater_color(current_val, old_or_known, precision: float) -> bool:
        if not current_val.had_valid_color_source():
            return False
        return current_val > old_or_known - (1.0 - precision)

    @staticmethod
    def greater_equal_color(current_val, old_or_known, precision: float) -> bool:
        return not CompareOperator.lower_color(current_val, old_or_known, precision)