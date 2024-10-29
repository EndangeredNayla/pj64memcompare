import ctypes
import psutil
import json

class GameEntity:
    def __init__(self, entity, location, datatype, size, hex_value):
        self.entity = entity
        self.location = location
        self.datatype = datatype
        self.size = size
        self.hex_value = hex_value
        self.value = None

class Project64:
    def __init__(self):
        self.connection_check_value = None
        self.connection_check_ptr = None
        self.game_id = ""
        self.game_name = ""
        self.game_region = ""
        self.platform_id = None

    def init(self, process_name, entities, regions):
        # Find the process by name
        for proc in psutil.process_iter(['name']):
            if proc.info['name'] == process_name:
                process = proc
                break
        else:
            return False

        # Open the process
        PROCESS_ALL_ACCESS = 0x1F0FFF
        process_handle = ctypes.windll.kernel32.OpenProcess(PROCESS_ALL_ACCESS, False, process.pid)

        # Define the ROM flag
        rom_flag = 0x0000000F80371240

        # Iterate over memory regions
        for region in process.memory_maps():
            r_size = region.rss

            if r_size not in (0x400000, 0x800000):
                continue

            # Read memory
            main_memory_region = ctypes.c_char_p(region.addr)
            temp = ctypes.c_uint32()
            ctypes.windll.kernel32.ReadProcessMemory(process_handle, main_memory_region.value + 8, ctypes.byref(temp), 4, None)

            if temp.value != 0x03400008:
                continue

            # Load system information
            self.load_system_information("N64", regions)
            regions[0].base_location_process = main_memory_region
            found = True
            break

        if not found:
            return False

        for region in process.memory_maps():
            r_size = region.rss

            if r_size < 0x400000:
                continue

            rom_region = ctypes.c_char_p(region.addr)
            temp = ctypes.c_uint64()
            ctypes.windll.kernel32.ReadProcessMemory(process_handle, rom_region.value, ctypes.byref(temp), 8, None)

            if temp.value != rom_flag:
                continue

            self.connection_check_value = rom_flag
            self.connection_check_ptr = rom_region
            # Set memory protection (not directly possible in Python, but you can use ctypes to call VirtualProtect)
            regions[1].base_location_process = rom_region
            regions[1].size = r_size
            found = True

            # Read game ID and name
            temp_id = ctypes.create_string_buffer(5)
            self.read_from_reordered_range_ex(process_handle, ctypes.byref(temp_id), rom_region.value + 0x3B)
            self.game_id = temp_id.value.decode()

            game_name_buffer = ctypes.create_string_buffer(20)
            for i in range(0, 20, 4):
                self.read_from_reordered_range_ex(process_handle, ctypes.byref(game_name_buffer, i), rom_region.value + 0x20 + i)

            self.game_name = self.remove_space_padding(game_name_buffer.value.decode())
            self.game_region = self.get_region_from_big_n_region_code(self.game_id[3])
            self.platform_id = "N64"
            break

        return found and self.obtain_game_entities("N64", entities)

    def load_system_information(self, system, regions):
        # Hardcoded system information for N64
        if system == "N64":
            regions.append({
                "Label": "RDRAM",
                "Base": 0x80000000,
                "Size": 0x800000
            })
            regions.append({
                "Label": "Cartridge ROM",
                "Base": 0xB0000000,
                "Size": 0x00
            })

    def read_from_reordered_range_ex(self, process_handle, buffer, address):
        # Assuming buffer is a ctypes buffer and address is an integer
        address = ctypes.c_char_p(address)
        dest = ctypes.cast(buffer, ctypes.POINTER(ctypes.c_char))

        for i in range(ctypes.sizeof(buffer)):
            reordered_address = self.translate_ptr_to_4_bytes_reordering_ptr(address.value + i)
            ctypes.windll.kernel32.ReadProcessMemory(process_handle, reordered_address, ctypes.byref(dest[i]), 1, None)


    def remove_space_padding(self, name):
        return name.strip()

    def get_region_from_big_n_region_code(self, code):
        region_map = {
         'A': "Any",
            'C': "China",
          'D': "Germany",
            'E': "USA",
           'F': "France",
            'H': "Netherlands",
        'I': "Italy",
        'J': "Japan",
        'K': "Korea",
        'L': "JPN-PAL",
        'M': "USA-PAL",
        'N': "JPN-USA",
        'P': "Europe", 'X': "Europe", 'Y': "Europe", 'Z': "Europe",
        'Q': "JPN-KOR",
        'R': "Russia",
        'S': "Spain",
        'T': "USA-KOR",
        'U': "Australia",
        'V': "Scandinavia",
        'W': "Taiwan/Hong Kong/Macau"
        }
        return region_map.get(code, "Unknown")

    def obtain_game_entities(self, system, entities):
        entities.clear()
    
        # Hardcoded JSON data
        hardcoded_data = {
            "N64": [
                {"Entity": "Endianness Indicator", "Location": "0x90000000", "Datatype": "INT", "Size": "1", "Hex": True},
                {"Entity": "Initial PI_BSB_DOM1_LAT_REG & PI_BSB_DOM1_PGS_REG", "Location": "0x90000001", "Datatype": "INT", "Size": "1", "Hex": True},
                {"Entity": "Initial PI_BSD_DOM1_PWD_REG", "Location": "0x90000002", "Datatype": "INT", "Size": "1", "Hex": True},
                {"Entity": "Initial PI_BSB_DOM1_PGS_REG", "Location": "0x90000003", "Datatype": "INT", "Size": "1", "Hex": True},
                {"Entity": "ClockRate Override", "Location": "0x90000004", "Datatype": "INT", "Size": "4", "Hex": True},
                {"Entity": "Program Counter", "Location": "0x90000008", "Datatype": "INT", "Size": "4", "Hex": True},
                {"Entity": "Release Address", "Location": "0x9000000C", "Datatype": "INT", "Size": "4", "Hex": True},
                {"Entity": "CRC1", "Location": "0x90000010", "Datatype": "INT", "Size": "4", "Hex": True},
                {"Entity": "CRC2", "Location": "0x90000014", "Datatype": "INT", "Size": "4", "Hex": True},
                {"Entity": "Unknown", "Location": "0x90000018", "Datatype": "BIN", "Size": "8", "Hex": True},
                {"Entity": "Name", "Location": "0x90000020", "Datatype": "TEXT", "Size": "20", "Hex": False},
                {"Entity": "Unknown", "Location": "0x90000034", "Datatype": "BIN", "Size": "4", "Hex": True},
                {"Entity": "Media Format", "Location": "0x90000038", "Datatype": "INT", "Size": "4", "Hex": True},
                {"Entity": "Cartridge ID", "Location": "0x9000003C", "Datatype": "TEXT", "Size": "2", "Hex": False},
                {"Entity": "Region Code", "Location": "0x9000003E", "Datatype": "TEXT", "Size": "1", "Hex": False},
                {"Entity": "Version", "Location": "0x9000003F", "Datatype": "TEXT", "Size": "1", "Hex": False}
            ]
        }
    
        system_entities = hardcoded_data.get(system, [])
    
        for game_entity in system_entities:
            entity = game_entity["Entity"]
            location = int(game_entity["Location"], 16)
            datatype = game_entity["Datatype"]
            size = int(game_entity["Size"])
            hex_value = game_entity["Hex"]
            entities.append(GameEntity(entity, location, datatype, size, hex_value))
    
        if not system_entities:
            return False
    
        for entity in entities:
            entity_value = ""
            if entity.datatype == "INT":
                temp_val = self.read_value(entity.location, entity.size)
                if entity.hex_value:
                    entity_value = f"0x{temp_val:X}"
                else:
                    entity_value = str(temp_val)
            elif entity.datatype == "TEXT":
                entity_value = self.read_text(entity.location, entity.size)
            elif entity.datatype == "BIN":
                entity_value = self.read_bin(entity.location, entity.size)
    
            entity.value = entity_value
    
        return True