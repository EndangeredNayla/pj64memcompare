#pragma once
#include<functional>
#include<iostream>
#include <filesystem>

namespace MemoryCompare
{
	class MemCompareResults
	{
	private:
		enum HeaderOffsets { DUMP_STARTING_ADDRESS = 0, RESULT_COUNT = 8, ITERATION = 0x10, VALUE_WIDTH = 0x12, ADDRESS_WIDTH = 0x14, PLACEHOLDER = 0x15, HEADER_SIZE = 0x20 };
		std::vector<char> _addresses;
		std::vector<char> _values;
		std::vector<char> _previousValues;
		std::vector<uint64_t> _indices;
		std::vector<uint64_t> _startingAdresses;
		std::vector<uint64_t> _resultCounts;
		std::vector<std::string> _fileHeaders;
		std::wstring _path;
		uint16_t _rangeCount = 0;
		uint64_t _totalResultCount = 0;
		uint8_t _addressWidth = 0;
		uint16_t _valueWidth = 0;
		uint64_t _fileSize = 0;
		uint16_t _iteration = 0;
		bool _cached = false;
		bool _zipped = false;

		void createHeader(const uint32_t index);

	public:
		MemCompareResults(std::wstring path, uint16_t iteration, uint8_t addressWidth, uint16_t valueWidth, uint16_t rangeCount = 0, bool cached = false, bool zip = false);

		void SetNewRange(const uint64_t startingAddress);

		template<typename addressType> void PushBackResultByPtr(addressType address, char* value, char* previousValue = nullptr)
		{
			_addresses.insert(_addresses.end(), reinterpret_cast<char*>(&address), reinterpret_cast<char*>(&address + 1));
			_values.insert(_values.end(), value, value + _valueWidth);

			if (_iteration > 1)
				_previousValues.insert(_previousValues.end(), previousValue, previousValue + _valueWidth);

			++_resultCounts.back();
			++_totalResultCount;
		}

		template<typename addressType, typename dataType> void PushBackResult(addressType address, dataType value, dataType previousValue = 0)
		{
			_addresses.insert(_addresses.end(), reinterpret_cast<char*>(&address), reinterpret_cast<char*>(&address + 1));
			_values.insert(_values.end(), reinterpret_cast<char*>(&value), reinterpret_cast<char*>(&value + 1));

			if (_iteration > 1)
				_previousValues.insert(_previousValues.end(), reinterpret_cast<char*>(&previousValue), reinterpret_cast<char*>(&previousValue + 1));

			++_resultCounts.back();
			++_totalResultCount;
		}

		int GetRangeIndexOfStartingAddress(const uint64_t startingAddress) const;

		template <typename addressType> addressType* GetAddressesPtrAllRanges()
		{
			return reinterpret_cast<addressType*>(_addresses.data());
		}

		template <typename dataType> dataType* GetValuesPtrAllRanges()
		{
			return reinterpret_cast<dataType*>(_values);
		}

		template <typename dataType> dataType* GetPreviousValuesPtrAllRanges()
		{
			return reinterpret_cast<dataType*>(_previousValues);
		}

		template<typename addressType> addressType* GetAddressesPtrOfRange(const uint64_t startingAddress)
		{
			for (int i = 0; i < _rangeCount; ++i)
				if (_startingAdresses[i] == startingAddress)
					if (_resultCounts[i] == 0)
						return nullptr;
					else
						return reinterpret_cast<addressType*>(& _addresses[_indices[i] * sizeof(addressType)]);

			return nullptr;
		}

		template<typename dataType> dataType* GetValuesPtrOfRange(const uint64_t startingAddress)
		{
			for (int i = 0; i < _rangeCount; ++i)
				if (_startingAdresses[i] == startingAddress)
					if (_resultCounts[i] == 0)
						return nullptr;
					else
						return reinterpret_cast<dataType*>(&_values[_indices[i] * sizeof(dataType)]);

			return nullptr;
		}

		template<typename dataType> dataType* GetPreviousValuesPtrOfRange(const uint64_t startingAddress)
		{
			for (int i = 0; i < _rangeCount; ++i)
				if (_startingAdresses[i] == startingAddress)
					if (_resultCounts[i] == 0)
						return nullptr;
					else
						return reinterpret_cast<dataType*>(&_previousValues[_indices[i] * sizeof(dataType)]);

			return nullptr;
		}

		template<typename addressType> addressType* GetAddressesPtrByRangeIndex(const uint32_t rangeIndex)
		{
			if (_resultCounts[rangeIndex] == 0)
				return nullptr;

			return reinterpret_cast<addressType*>(&_addresses[_indices[rangeIndex] * sizeof(addressType)]);
		}

		template<typename dataType> dataType* GetValuesPtrByRangeIndex(const uint32_t rangeIndex)
		{
			if (_resultCounts[rangeIndex] == 0)
				return nullptr;

			return reinterpret_cast<dataType*>(&_values[_indices[rangeIndex] * sizeof(dataType)]);
		}

		template<typename dataType> dataType* GetPreviousValuesPtrByRangeIndex(const uint32_t rangeIndex)
		{
			if (_resultCounts[rangeIndex] == 0)
				return nullptr;

			return reinterpret_cast<dataType*>(_previousValues[_indices[rangeIndex] * sizeof(dataType)]);
		}

		template<typename addressType> addressType GetAddressByRangeIndex(const uint32_t rangeIndex, const uint64_t addressIndex)
		{
			if (_resultCounts[rangeIndex] == 0)
				return 0;

			return *reinterpret_cast<addressType*>(&_addresses[_indices[rangeIndex] * sizeof(addressType) + addressIndex * sizeof(addressType)]);
		}

		template<typename dataType> dataType GetValueByRangeIndex(const uint32_t rangeIndex, const uint64_t valueIndex)
		{
			if (_resultCounts[rangeIndex] == 0)
				return 0;

			return *reinterpret_cast<dataType*>(&_values[_indices[rangeIndex] * sizeof(dataType) + valueIndex * sizeof(dataType)]);
		}

		template<typename dataType> dataType GetPreviousValueByRangeIndex(const uint32_t rangeIndex, const uint64_t valueIndex)
		{
			if (_resultCounts[rangeIndex] == 0)
				return 0;

			if(_iteration < 2)
				return 0; 
			
			return *reinterpret_cast<dataType*>(&_previousValues[_indices[rangeIndex] * sizeof(dataType) + valueIndex * sizeof(dataType)]);
		}

		template<typename addressType> addressType GetAddressAllRanges(const uint64_t addressIndex)
		{
			return *reinterpret_cast<addressType*>(&_addresses[addressIndex * sizeof(addressType)]);
		}

		template<typename dataType> dataType GetValueAllRanges(const uint64_t valueIndex)
		{
			return *reinterpret_cast<dataType*>(&_values[valueIndex * sizeof(dataType)]);
		}

		template<typename dataType> dataType GetPreviousValueAllRanges(const uint64_t valueIndex)
		{
			if (_iteration < 2)
				return 0;

			return *reinterpret_cast<dataType*>(&_previousValues[valueIndex * sizeof(dataType)]);
		}

		template<typename dataType> dataType* GetSpecificValuePtrByRangeIndex(const int32_t rangeIndex, const uint64_t valueIndex)
		{
			if (_resultCounts[rangeIndex] == 0)
				return nullptr;

			return reinterpret_cast<dataType*>(&_values[_indices[rangeIndex] * sizeof(dataType) + valueIndex * sizeof(dataType)]);
		}

		template<typename dataType> dataType* GetSpecificValuePtrAllRanges(const uint64_t valueIndex)
		{
			return reinterpret_cast<dataType*>(&_values[valueIndex * sizeof(dataType)]);
		}

		template<typename dataType> dataType* GetSpecificPreviousValuePtrByRangeIndex(const uint32_t rangeIndex, const uint64_t valueIndex)
		{
			if (_resultCounts[rangeIndex] == 0)
				return nullptr;

			if (_iteration < 2)
				return nullptr;

			return reinterpret_cast<dataType*>(&_previousValues[_indices[rangeIndex] * sizeof(dataType) + valueIndex * sizeof(dataType)]);
		}

		template<typename dataType> dataType* GetSpecificPreviousValuePtrAllRanges(const uint64_t valueIndex)
		{
			if (_iteration < 2)
				return nullptr;

			return reinterpret_cast<dataType*>(&_previousValues[valueIndex * sizeof(dataType)]);
		}

		uint64_t GetTotalResultCount();
		uint64_t GetResultCountByRangeIndex(const uint32_t index);
		uint64_t GetResultCountOfRange(const uint64_t startingAddress);
		void Clear();
		void SetValueWidth(const uint16_t width);
		void SetAddressWidth(const uint8_t width);
		void SetResultCount(uint32_t index, uint64_t count);
		bool SaveResults(uint32_t rangeIndex, bool zipped);
		bool LoadResults(bool zipped);
		uint16_t GetValueWidth() const;
		void operator=(const MemCompareResults& other);
		uint16_t GetRangeCount() const;
	};
}