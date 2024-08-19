#include "MemoryDump.hpp"
#include "MemoryCompare.hpp"
#include <fstream>

MemoryCompare::MemDump::MemDump(void* baseLocation, const uint64_t baseAddress, const uint64_t size)
{
	_memDump = std::string(static_cast<char*>(baseLocation), size);
	_baseAddress = baseAddress;
	_size = size;
}

MemoryCompare::MemDump::MemDump(const std::wstring& path, const uint64_t baseAddress, uint64_t size, const uint64_t startReading)
{
	_memDump.resize(size);
	void* ptr = &_memDump[0];

	if (!MemoryCompare::LoadBinary(path, ptr, size, startReading))
		_memDump.clear();

	_baseAddress = baseAddress;
	_size = size;
}

uint64_t MemoryCompare::MemDump::GetBaseAddress()
{
	return _baseAddress;
}

uint64_t MemoryCompare::MemDump::GetSize()
{
	return _size;
}

std::wstring MemoryCompare::MemDump::GetPath()
{
	return _path;
}