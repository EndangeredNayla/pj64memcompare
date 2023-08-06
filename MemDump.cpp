#include "MemDump.h"
#include<fstream>

MemoryCompare::MemDump::MemDump(const HANDLE handle, void* address, const uint64_t memSize)
{
	_handle = handle;
	_hasHandle = true;
	_address = address;
	_memSize = memSize;
	DumpExRAM();
}

MemoryCompare::MemDump::MemDump(const std::wstring& path, void* address, const uint64_t size, const uint64_t startReading)
{
	_hasHandle = false;
	_address = address;

	_memDump = malloc(_memSize);
	if (!MemoryCompare::LoadBinary(path, _memDump, _memSize, startReading))
	{
		free(_memDump);
		_address = 0;
		_memDump = nullptr;
	}
}

void MemoryCompare::MemDump::DumpExRAM()
{
	_memDump = malloc(_memSize);
	if (!ReadProcessMemory(_handle, _address, _memDump, _memSize, nullptr))
	{
		free(_memDump);
		_memDump = nullptr;
	}
}

bool MemoryCompare::MemDump::SaveDump(const std::wstring& filePath) const
{
	return MemoryCompare::SaveBinary(filePath, _memDump, _memSize);
}

bool MemoryCompare::MemDump::SaveDump() const
{
	return MemoryCompare::SaveBinary(_filePath, _memDump, _memSize);
}