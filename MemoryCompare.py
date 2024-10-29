from typing import List, Optional
import MemoryCompareResult

class MemCompare:
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(MemCompare, cls).__new__(cls)
            cls._instance._initialize()
        return cls._instance

    def _initialize(self):
        self._results: List[MemoryCompareResult] = []
        self._iteration_count = 0
        self._result_count = 0
        self._setup_flags = 0
        self._results_dir = ""
        self._superior_datatype = 0
        self._subsidiary_datatype = 2
        self._address_width = 4
        self._value_width = 4
        self._alignment = 4
        self._primary_known_value_str = ""
        self._secondary_known_value_str = ""
        self._iteration_flags = 0
        self._condition = 0
        self._counter_iteration = 0
        self._counter_iteration_index = 0
        self._precision = 1.0
        self._range_count = 0
        self._previous_iteration_range_index = -1
        self._current_dump_address = None
        self._current_dump_size = 0
        self._current_base_address = 0

    def set_up(self, results_dir: str, superior_datatype: int, subsidiary_datatype: int, address_width: int, alignment: int = 4, setup_flags: int = 0):
        MemoryCompareResult.set_results_dir(results_dir)
        MemoryCompareResult.clear_results_dir(-1)
        self._results_dir = results_dir
        self._superior_datatype = superior_datatype
        self._subsidiary_datatype = subsidiary_datatype
        self._address_width = address_width
        self._setup_flags = setup_flags
        self._alignment = alignment

    def new_iteration(self, condition: int, counter_iteration: int, primary_known_value: str, secondary_known_value: str, precision: float = 1.0, iteration_flags: int = 0):
        self._condition = condition
        self._counter_iteration = counter_iteration
        self._primary_known_value_str = primary_known_value
        self._secondary_known_value_str = secondary_known_value
        self._precision = precision
        self._iteration_flags = iteration_flags

    def process_next_range(self, range):
        if self._iteration_count > 1:
            self._previous_iteration_range_index = self._results[self._counter_iteration_index].get_range_index_of_starting_address(range.get_base_address())

        if self._superior_datatype == 1:  # ARRAY
            if self._iteration_count < 2:
                self.select_array_known_initial()
            else:
                self.select_array_known_successive()
        elif self._superior_datatype == 2:  # TEXT
            self.select_text_known_initial()
        elif self._superior_datatype == 3:  # COLOR
            if self._iteration_count < 2:
                self.select_color_known_initial()
            else:
                self.select_color_known_successive()
        else:  # PRIMITIVE
            if self._iteration_count < 2:
                if self._iteration_flags & 1:  # KNOWN
                    self.select_primitive_known_initial()
                else:
                    self.select_primitive_unknown_initial()
            else:
                if self._iteration_flags & 1:  # KNOWN
                    self.select_primitive_known_successive()
                else:
                    self.select_primitive_unknown_successive()

        if not (self._setup_flags & 16) or (self._setup_flags & 64):  # CACHED or DISABLE_UNDO
            self.save_results()

        self._result_count = self._results[-1].get_total_result_count()

    def get_result_count(self) -> int:
        return self._result_count

    def get_iteration_count(self) -> int:
        return self._iteration_count

    def get_results(self) -> MemoryCompareResult:
        return self._results[-1]

    def reset(self):
        MemoryCompareResult.clear_results_dir(-1)
        self._results.clear()
        self._iteration_count = 0
        self._result_count = 0
        self._results_dir = ""
        self._superior_datatype = 0
        self._subsidiary_datatype = 2
        self._address_width = 4
        self._value_width = 4
        self._setup_flags = 0
        self._range_count = 0
        self._alignment = 4
        self._primary_known_value_str = ""
        self._secondary_known_value_str = ""
        self._condition = 0
        self._iteration_flags = 0
        self._counter_iteration = 0
        self._precision = 1.0
        self._counter_iteration_index = 0
        self._range_count = 0
        self._previous_iteration_range_index = -1
        self._current_dump_address = None
        self._current_dump_size = 0
        self._current_base_address = 0

    def save_results(self) -> bool:
        return self._results[-1].save_results(self._results[-1].get_range_count() - 1, self._setup_flags & 32)  # ZIP_RESULTS

    # Placeholder methods for selection logic
    def select_primitive_unknown_initial(self):
        pass

    def select_primitive_unknown_successive(self):
        pass

    def select_primitive_known_initial(self):
        pass

    def select_primitive_known_successive(self):
        pass

    def select_color_known_initial(self):
        pass

    def select_color_known_successive(self):
        pass

    def select_text_known_initial(self):
        pass

    def select_array_known_initial(self):
        pass

    def select_array_known_successive(self):
        pass