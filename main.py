from DummyProject64MemoryReader import DummyProject64MemoryReader

def main():
    dummy_reader = DummyProject64MemoryReader()

    # Simulate reading different types of data
    int_value = dummy_reader.read_value(0x90000000, 4)
    text_value = dummy_reader.read_text(0x90000020, 20)
    bin_value = dummy_reader.read_bin(0x90000018, 8)

    print(f"Integer Value: {int_value} (0x{int_value:X})")
    print(f"Text Value: {text_value}")
    print(f"Binary Value: {bin_value}")

if __name__ == "__main__":
    main()