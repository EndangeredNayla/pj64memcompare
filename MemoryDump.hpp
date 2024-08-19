#pragma once
#include<string>

namespace MemoryCompare
{
	class MemDump
	{
	private: 
		std::string _memDump;
		uint64_t _baseAddress = 0;
		uint64_t _size = 0;
		std::wstring _path;

	public: 
		MemDump(void* baseLocation, const uint64_t baseAddress, const uint64_t size);
		MemDump(const std::wstring& path, const uint64_t baseAddress, const uint64_t size = 0, const uint64_t startReading = 0);
		MemDump() {}

		void operator=(const MemDump& other)
		{
			_memDump = other._memDump;
			_baseAddress = other._baseAddress;
			_size = other._size;
			_path = other._path;
		}

		template<typename dataType> dataType GetDump()
		{
			return reinterpret_cast<dataType>(_memDump.data());
		}

		uint64_t GetBaseAddress();
		uint64_t GetSize();
		std::wstring GetPath();

	};
}