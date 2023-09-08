# MemoryCompare
A library for comparing memory dumps

## Usage

The MemCompare class is a singleton class and therefore has no initialization. Instead it needs to be reset before performing a new memory comparirion queue. This is needed to be called in the beginning of each iteration once.

### SetUp(std::wstring& resultsDir, uint16_t superiorDatatype, uint16_t subsidiaryDatatype, uint8_t addressWidth, bool isSigned, uint16_t alignment = 4, bool swapBytes = false, bool cached = false)
Before starting any comparision the comparision queue has to be setup once. 

#### std::wstring& resultsDir
Directory where results will be saved on your system's drive. This is only relevant if your seach queue is not cached.

#### uint16_t superiorDatatype
Superior Datatype of the serch queue. More details down below.

#### uint16_t subsidiaryDatatype

Superior Datatype of the serch queue. More details down below.

#### uint8_t addressWidth
The width of addresses in bytes. This is needed to probably store results of more complex datatypes.

#### bool signedOrCaseSensitive
If this is true, searches for integer values will be signed and searches for string values (Text) will be case-sensitive.

####  uint16_t alignment = 4
This value affects the step's wisdth the scan iterates through the memory dump. 4 is usually a good option since many values are aligned by 4 bytes. But for values narrower than 4 bytes, string values,a and RGB888 values an alignment of 1 might be better instead.

#### bool swapBytes = false
This allows scanning big endian memory dumps on little endian machines and vice versa. If true the opposite endianness will be considered.

#### bool cached = false
Whether to store previous memory dumps on disk or RAM. If true all scan results will be held in RAM which may speed up scanning especially when re-scanning past searches but it will eat a lot of RAM. If this is set to false results 2 iterations ago will be saved on disk and therefore won't eat any RAM. However, scans might take a bit longer.

### void NewIteration(uint8_t condition, bool hex, bool isKnownValue, uint16_t counterIteration, std::string& primaryKnownValue, std::string& secondaryKnownValue, float precision = 1.0f);

#### uint8_t condition
Search condition to be performed. More details down below.

#### bool hex
If the input input values for known-values searches shoud be consideren as hexadecimal. Not applicable for floats, Strings (MorphText), Arrays (OperativeArray) and Color values (LitColor) ignore these since they use their own formatting.

#### bool isKnownValue
Wheather known values (KNOWN (1)) should be scanned or not (UNKNOWN (0)). If not the parameters primaryKnownValue, and secondaryKnownValue will be ignored.

#### uint16_t counterIteration
If you did any mistage you can jump back to an older search. The first iteration has the value of 1 (not 0).

#### std::string& primaryKnownValue, std::string& secondaryKnownValue
These will be used by known value searches. If *primaryKnownValue* will be utilizes by increased/decreased unknown value searches as well.

#### float precision = 1.0f
This sets the accuracy when scanning for floating point values (float, doule) and color values (LitColor) since it may be impossible to know the exact value. A precision of 90.0 should be good enough in most cases.

### void ProcessNextRange(MemDump* range)
This scans a single memory region/memory dump. Call this function with each memory dump of the current iteration.

#### MemDump* range
Memory dump/range to be scanned/compared. More details down below.

### std::pair<uint64_t, uint16_t> GetSearchStats()
Returns the current search results. *.first* is the total result count. *.second* is the iteration count.

### MemCompareResults& GetResults()
Returns a reference to all search results of the last iteration. Use MemoryCompare::MemCompare::GetResults().GetValueAllRanges(1234) for instance. More details below on how to retreive search results though this function.

### void Reset()
Resets the current memory search queue and makes the singleton class ready for the next scan queue.

### Superiour Datatypes
These are needed to specify the kind of data typep.

#### PRIMITIVE (0)
Search considers primitive values such as Int8, Int16, Int32, Int64 (signed and unsigned) as well as float single and float double.
More details down below.

#### ARRAY (1)
Search consideres arrays of the types mentioned at *PRIMITIVE* (except for float single and float doubole)
Elements are separated by commas. Hex values must start with *0x*. Wildcards (index to be ignored) must be represented by a *#* (example: 0x420, #, 69).

#### TEXT (2)
Search considers strings/texts such as UTF-8, UTF16 little endian, UTF-16 big endian, utf-32 little endian, utf-32 big endian, ASCII, ISO_8859_1 - ISO_8859_16, SHIFT-JIS.

#### COLOR (3)
Search considers color values such as RGB888, RGB8888, RGB565, RGBF, RGBAF.

### Conditions
Condition types.
#### EQUAL [==] (0)
Search for values that DO match the (primary) known value (KNOWN value search) or previous one (UNKOWN va;ue search).

#### UNEQUAL [!=] (1)
Search for values that DO NOT match the (primary) known value (KNOWN value search) or previous one (UNKOWN va;ue search).

#### GREATER [>] (2)
Search for values that ARE BIGGER than the (primary) known value (KNOWN value search) or previous one (UNKOWN va;ue search).

#### GREATER_EQUAL [>=] (3)
Search for values that ARE BIGGER than or DO match the (primary) known value (KNOWN value search) or previous one (UNKOWN va;ue search).

#### LOWER [<] (4)
Search for values that ARE Smaller than the (primary) known value (KNOWN value search) or previous one (UNKOWN va;ue search).

#### LOWER_EQUAL [<=] (5)
Search for values that ARE SMALLER than or DO match the (primary) known value (KNOWN value search) or previous one (UNKOWN va;ue search).

#### INCREASED_BY (6)
Search for values that have INCREASED by the (primary) known value (UNKOWN value search).

#### DECREASED_BY (7)
Search for values that have DECREASED by the (primary) known value (UNKOWN value search).

#### BETWEEN (8)
Search for values that ARE BETWEEN the primary known value and secondary known value.

#### NOT_BETWEEN (9)
Search for values that ARE BETWEEN the primary known value and secondary known value.

#### AND [&&] (10)
Search for values that where ALL true bits ot the (primary) known value (KNOWN value search) or previous one (UNKOWN va;ue search) appear in the scanned value.

#### OR [||] (11)
Search for values that where at least one true bit ot the (primary) known value (KNOWN value search) or previous one (UNKOWN va;ue search) appear in the scanned value.

### Primitive Types and Array Types
- INT8 (0)
- INT16 (1)
- INT32 (2)
- INT64 (3)
- FLOAT (4) (Primitives only)
-# DOUBLE (5) (Primitives only)

If signedOrCaseSensitive is true INT8, INT16, INT32, and INT64 will be considered as signed values.

### Text Types
- UTF8 (0)
- UTF16LE (1)
- UTF16BE (2)
- UTF32LE (3)
- UTF32BE (4)
- ASCII (5)
- ISO_8859_1, LATIN1 (6)
- ISO_8859_2, LATIN2 (7)
- ISO_8859_3, LATIN3 (8)
- ISO_8859_4, LATIN4 (9)
- ISO_8859_5, CYRILLIC (10)
- ISO_8859_6, ARABIC (11)
- ISO_8859_7, GREEK (12)
- ISO_8859_8, HEBREW (13)
- ISO_8859_9, LATIN5, TURKISH (14)
- ISO_8859_10, LATIN6, NORDIC (15)
- ISO_8859_11, THAI (16)
- ISO_8859_13, LATIN7, BALTIC (17)
- ISO_8859_14, LATIN8, CELTIC (18)
- ISO_8859_15, WEST_EUROPEAN, LATIN9 (19)
- ISO_8859_16, LATIN10, SOUTHEAST_EUROPEAN (20)
- SHIFTJIS (21)

### Color Types
- RGB888 (0)
- RGBA8888 (1)
- RGBF (2)
- RGBAF (3)
- RGB565 (4)

## Examples
### Primitive Type Search
```c++
	if (MemoryCompare::MemCompare::GetSearchStats().second < 2) //Setup search when no comparision has been done yet. You can use the member function GetSearchStats().second to obtain the current iteration value
		MemoryCompare::MemCompare::SetUp(L"C:\\dumps\\", 
										 MemoryCompare::PRIMITIVE, //superior type
										 MemoryCompare::INT32, //subsidiary type
										 4, //address width of 4 bytes
										 false, //unsigned values
										 4, //alignment of 4-byte steps
										 true, //memory dump is big endian
										 true, //keep results in RAM
										 false);//zipped results yet not implemented

	MemoryCompare::MemCompare::NewIteration(MemoryCompare::EQUAL, search for matching values
											true, //known value is hex
											true, //known value search 
											1, //first/initial iteration 
											"DEADC0DE", //known value
											"", 
											1.0f);

	for (SystemRegion& dumpRegion : _dumpRegions) //iterate though regions (SystemRegion is a struct not related to this project)
	{
		char* buf = new char[dumpRegion.Size];
		Xertz::SystemInfo::GetProcessInfo(ProcessInformation::GetPID()).ReadExRAM(buf, dumpRegion.BaseLocationProcess, dumpRegion.Size); //dump region
		{																		//unnamed scope so so the MemDump instance will be automatically deleted 
			MemoryCompare::MemDump dump(buf, dumpRegion.Base, dumpRegion.Size); //create MemDump instance for the current region
			delete[] buf;	//delete current temp buffer
			MemoryCompare::MemCompare::ProcessNextRange(&dump); //process current memory dump
		}
	}
```

### Color Type Search
```c++
	if (MemoryCompare::MemCompare::GetSearchStats().second < 2) //Setup search when no comparision has been done yet. You can use the member function GetSearchStats().second to obtain the current iteration value
		MemoryCompare::MemCompare::SetUp(L"C:\\dumps\\", 
										 MemoryCompare::COLOR, //superior type
										 MemoryCompare::RGBF, //subsidiary type
										 4, //address width of 4 bytes
										 false, //unsigned values
										 4, //alignment of 4-byte steps
										 true, //memory dump is big endian
										 true, //keep results in RAM
										 false); //zipped results yet not implemented

	MemoryCompare::MemCompare::NewIteration(MemoryCompare::EQUAL, search for matching values
											true, //known value is hex (ignored by color searches)
											true, //known value search 
											4, //conpare against 4th iteration
											"0.75, 0.8, 1.0", //known value
											"", 
											0.9f); //allow values to be 10% off
```


## MemDump Class
Instances of this class carry memory dumps.

### Constructors

#### MemDump(void* baseLocation, uint64_t baseAddress, uint64_t size)
Copies *size* bytes from *baseLocation*. *baseAddress* is the logical address where the memory dump/region starts for the target system.

#### MemDump(const std::wstring& path, uint64_t baseAddress, uint64_t size = 0, uint64_t startReading = 0)
Loads the memory dump defined by *path* from your system's storage. *baseAddress* is the logical address where the memory dump/region starts for the target system. *size* defines the numbers of bytes to be written and *startReadin* the offset of the first byte to be read. 0 means that it starts reading from the beginning of the file.

### Public Member Functions
#### dataType GetDump<dataType>()
Returns the pointer of type dataType to the memory dump.

#### uint64_t GetBaseAddress()
Returns the base address.

#### uint64_t GetSize()
Returns the dump size.

#### std::wstring GetPath()
Returns the memory dump file path.

## MemCompareResults Class
Instances that manage memory comparision results

### Constructor

#### MemCompareResults(std::wstring path, uint16_t iteration, uint8_t addressWidth, uint16_t valueWidth, uint16_t rangeCount = 0, bool cached = false, bool zip = false)
Creates an instance.
- path: where to store the result file on disk
- iteration: iteration number
- addressWidth
- valueWidth
- rangeCount (optional)
- cached (WIP)
- zip (WIP)

### Public Member Functions

#### void SetNewRange(uint64_t startingAddress)
Adds a new range entry to the results range list. This is required before adding results of a new range.

#### void PushBackResultByPtr<addressType>(addressType address, char* value, char* previousValue = nullptr)
Adds a search result to the current range's memory comparision of its iteration. *address* is passed by value while the value and previous value is passed by pointer. This is needed for more complex types such as arrays or RGBF, and RGBAF. Previous value is optional.

#### void PushBackResult<addressType, dataType>(addressType address, dataType value, dataType previousValue = 0)
Adds a search result to the current range's memory comparision of its iteration. Previous value is optional.

#### int GetRangeIndexOfStartingAddress(uint64_t startingAddress)
Returns the index of the startingAddress aka base address list. If startingAddress is not found it returns -1.

#### addressType* GetAddressesPtrAllRanges<dataType>()
Returns a pointer of type addressType to all regions' result addresses.

#### dataType* GetValuesPtrAllRanges<dataType>()
Returns a pointer of type dataType to all regions' result values.

#### dataType* GetPreviousValuesPtrAllRanges<dataType>()
Returns a pointer of type dataType to all regions' result previous values.

#### addressType* GetAddressesPtrOfRange<addressType>(uint64_t startingAddress)
Returns a pointer of type addressType to all result addresses of *startingAddress*' range.

#### dataType* GetValuesPtrOfRange<dataType>(uint64_t startingAddress)
Returns a pointer of type dataType to all result values of *startingAddress*' range.

#### dataType* GetPreviousValuesPtrOfRange<dataType>(uint64_t startingAddress)
Returns a pointer of type dataType to all result previous values of *startingAddress*' range.

#### addressType* GetAddressesPtrByRangeIndex<addressType>(uint32_t rangeIndex)
Returns a pointer of type addressType to all result addresses of *rangeIndex*.

#### dataType* GetValuesPtrByRangeIndex<dataType>(uint32_t rangeIndex)
Returns a pointer of type dataType to all result values of *rangeIndex*.

#### dataType* GetPreviousValuesPtrByRangeIndex<dataType>(uint32_t rangeIndex)
Returns a pointer of type dataType to all result previous values of *rangeIndex*.

#### addressType GetAddressByRangeIndex<addressType>(uint32_t rangeIndex, uint64_t addressIndex)
Returns a result address of type addressType of the range specified by *rangeIndex* and address-index of *addressIndex*.

#### dataType* GetSpecificValuePtrByRangeIndex<dataType>(const int32_t rangeIndex, uint64_t valueIndex)
Returns a pointer of type dataType of the range specified by *rangeIndex* and the value-index of *valueIndex*.

#### dataType* GetSpecificValuePtrAllRanges<dataType>(uint64_t valueIndex)
Returns a result value pointer of type dataType* of all ranges *valueIndex*.

#### dataType* GetSpecificPreviousValuePtrByRangeIndex<dataType>(uint32_t rangeIndex, uint64_t valueIndex)
Returns a result previous-value pointer of type dataType* of the range specified by *rangeIndex* and the value-index of *valueIndex*.

#### dataType* GetSpecificPreviousValuePtrAllRanges<dataType>(uint64_t valueIndex)
Returns a result previous-value pointer of type dataType* of all ranges *valueIndex*.

#### uint64_t GetTotalResultCount()
Returns the sum of all regions result counts.

#### uint64_t GetResultCountByRangeIndex(uint32_t index)
Returns the result count of the range specified by *rangeIndex*.

#### uint64_t GetResultCountOfRange(uint64_t startingAddress)
Returns the result count of the range specified by *startingAddress*.

#### void Clear()
Clears all result data.

#### void SetValueWidth(uint16_t width)
Sets value width to a new value.

#### void SetAddressWidth(uint8_t width)
Sets address width to a new value.

#### bool SaveResults(uint32_t rangeIndex, bool zipped)
Saves results of range defined by *rangeIndex*.

#### bool LoadResults(bool zipped)
(Re)Loads results from defined path.

#### uint16_t GetValueWidth()
Returns the results value width.

#### uint16_t GetRangeCount()
Returns amount of scanned ranges.

### Operators

#### void operator=(MemCompareResults& other)
Copies the right-hand instance to the left-hand one.
