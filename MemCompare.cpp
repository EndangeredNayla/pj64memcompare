#pragma once
#include"MemCompare.h"

void MemoryCompare::MemCompare::selectPrimitiveUnknownInitial()
{
	switch (_subsidiaryDatatype)
	{
	case INT8:
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveUnknownInitial<uint16_t, int8_t>() : primitiveUnknownInitial<uint16_t, uint8_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveUnknownInitial<uint64_t, int8_t>() : primitiveUnknownInitial<uint64_t, uint8_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveUnknownInitial<uint32_t, int8_t>() : primitiveUnknownInitial<uint32_t, uint8_t>();
		}
	}
	break;
	case INT16:
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveUnknownInitial<uint16_t, int16_t>() : primitiveUnknownInitial<uint16_t, uint16_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveUnknownInitial<uint64_t, int16_t>() : primitiveUnknownInitial<uint64_t, uint16_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveUnknownInitial<uint32_t, int16_t>() : primitiveUnknownInitial<uint32_t, uint16_t>();
		}
	}
	break;
	case INT64:
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveUnknownInitial<uint16_t, int64_t>() : primitiveUnknownInitial<uint16_t, uint64_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveUnknownInitial<uint64_t, int64_t>() : primitiveUnknownInitial<uint64_t, uint64_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveUnknownInitial<uint32_t, int64_t>() : primitiveUnknownInitial<uint32_t, uint64_t>();
		}
	}
	break;
	case FLOAT:
	{
		switch (_addressWidth)
		{
		case 2:
			primitiveUnknownInitial<uint16_t, float>();
			break;
		case 8:
			primitiveUnknownInitial<uint64_t, float>();
			break;
		default:
			primitiveUnknownInitial<uint32_t, float>();
		}
	}
	break;
	case DOUBLE:
	{
		switch (_addressWidth)
		{
		case 2:
			primitiveUnknownInitial<uint16_t, double>();
			break;
		case 8:
			primitiveUnknownInitial<uint64_t, double>();
			break;
		default:
			primitiveUnknownInitial<uint32_t, double>();
		}
	}
	break;
	default: //INT32
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveUnknownInitial<uint16_t, int32_t>() : primitiveUnknownInitial<uint16_t, uint32_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveUnknownInitial<uint64_t, int32_t>() : primitiveUnknownInitial<uint64_t, uint32_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveUnknownInitial<uint32_t, int32_t>() : primitiveUnknownInitial<uint32_t, uint32_t>();
		}
	}
	}
}

void MemoryCompare::MemCompare::selectPrimitiveUnknownSuccessive()
{
	switch (_subsidiaryDatatype)
	{
	case INT8:
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveUnknownSuccessive<uint16_t, int8_t>() : primitiveUnknownSuccessive<uint16_t, uint8_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveUnknownSuccessive<uint64_t, int8_t>() : primitiveUnknownSuccessive<uint64_t, uint8_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveUnknownSuccessive<uint32_t, int8_t>() : primitiveUnknownSuccessive<uint32_t, uint8_t>();
		}
	}
	break;
	case INT16:
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveUnknownSuccessive<uint16_t, int16_t>() : primitiveUnknownSuccessive<uint16_t, uint16_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveUnknownSuccessive<uint64_t, int16_t>() : primitiveUnknownSuccessive<uint64_t, uint16_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveUnknownSuccessive<uint32_t, int16_t>() : primitiveUnknownSuccessive<uint32_t, uint16_t>();
		}
	}
	break;
	case INT64:
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveUnknownSuccessive<uint16_t, int64_t>() : primitiveUnknownSuccessive<uint16_t, uint64_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveUnknownSuccessive<uint64_t, int64_t>() : primitiveUnknownSuccessive<uint64_t, uint64_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveUnknownSuccessive<uint32_t, int64_t>() : primitiveUnknownSuccessive<uint32_t, uint64_t>();
		}
	}
	break;
	case FLOAT:
	{
		switch (_addressWidth)
		{
		case 2:
			primitiveUnknownSuccessive<uint16_t, float>();
			break;
		case 8:
			primitiveUnknownSuccessive<uint64_t, float>();
			break;
		default:
			primitiveUnknownSuccessive<uint32_t, float>();
		}
	}
	break;
	case DOUBLE:
	{
		switch (_addressWidth)
		{
		case 2:
			primitiveUnknownSuccessive<uint16_t, double>();
			break;
		case 8:
			primitiveUnknownSuccessive<uint64_t, double>();
			break;
		default:
			primitiveUnknownSuccessive<uint32_t, double>();
		}
	}
	break;
	default: //INT32
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveUnknownSuccessive<uint16_t, int32_t>() : primitiveUnknownSuccessive<uint16_t, uint32_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveUnknownSuccessive<uint64_t, int32_t>() : primitiveUnknownSuccessive<uint64_t, uint32_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveUnknownSuccessive<uint32_t, int32_t>() : primitiveUnknownSuccessive<uint32_t, uint32_t>();
		}
	}
	}
}

void MemoryCompare::MemCompare::selectPrimitiveKnownInitial()
{
	switch (_subsidiaryDatatype)
	{
	case INT8:
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveKnownInitial<uint16_t, int8_t>() : primitiveKnownInitial<uint16_t, uint8_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveKnownInitial<uint64_t, int8_t>() : primitiveKnownInitial<uint64_t, uint8_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveKnownInitial<uint32_t, int8_t>() : primitiveKnownInitial<uint32_t, uint8_t>();
		}
	}
	break;
	case INT16:
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveKnownInitial<uint16_t, int16_t>() : primitiveKnownInitial<uint16_t, uint16_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveKnownInitial<uint64_t, int16_t>() : primitiveKnownInitial<uint64_t, uint16_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveKnownInitial<uint32_t, int16_t>() : primitiveKnownInitial<uint32_t, uint16_t>();
		}
	}
	break;
	case INT64:
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveKnownInitial<uint16_t, int64_t>() : primitiveKnownInitial<uint16_t, uint64_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveKnownInitial<uint64_t, int64_t>() : primitiveKnownInitial<uint64_t, uint64_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveKnownInitial<uint32_t, int64_t>() : primitiveKnownInitial<uint32_t, uint64_t>();
		}
	}
	break;
	case FLOAT:
	{
		switch (_addressWidth)
		{
		case 2:
			primitiveKnownInitial<uint16_t, float>();
			break;
		case 8:
			primitiveKnownInitial<uint64_t, float>();
			break;
		default:
			primitiveKnownInitial<uint32_t, float>();
		}
	}
	break;
	case DOUBLE:
	{
		switch (_addressWidth)
		{
		case 2:
			primitiveKnownInitial<uint16_t, double>();
			break;
		case 8:
			primitiveKnownInitial<uint64_t, double>();
			break;
		default:
			primitiveKnownInitial<uint32_t, double>();
		}
	}
	break;
	default: //INT32
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveKnownInitial<uint16_t, int32_t>() : primitiveKnownInitial<uint16_t, uint32_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveKnownInitial<uint64_t, int32_t>() : primitiveKnownInitial<uint64_t, uint32_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveKnownInitial<uint32_t, int32_t>() : primitiveKnownInitial<uint32_t, uint32_t>();
		}
	}
	}
}

void MemoryCompare::MemCompare::selectPrimitiveKnownSuccessive()
{
	switch (_subsidiaryDatatype)
	{
	case INT8:
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveKnownSuccessive<uint16_t, int8_t>() : primitiveKnownSuccessive<uint16_t, uint8_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveKnownSuccessive<uint64_t, int8_t>() : primitiveKnownSuccessive<uint64_t, uint8_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveKnownSuccessive<uint32_t, int8_t>() : primitiveKnownSuccessive<uint32_t, uint8_t>();
		}
	}
	break;
	case INT16:
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveKnownSuccessive<uint16_t, int16_t>() : primitiveKnownSuccessive<uint16_t, uint16_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveKnownSuccessive<uint64_t, int16_t>() : primitiveKnownSuccessive<uint64_t, uint16_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveKnownSuccessive<uint32_t, int16_t>() : primitiveKnownSuccessive<uint32_t, uint16_t>();
		}
	}
	break;
	case INT64:
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveKnownSuccessive<uint16_t, int64_t>() : primitiveKnownSuccessive<uint16_t, uint64_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveKnownSuccessive<uint64_t, int64_t>() : primitiveKnownSuccessive<uint64_t, uint64_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveKnownSuccessive<uint32_t, int64_t>() : primitiveKnownSuccessive<uint32_t, uint64_t>();
		}
	}
	break;
	case FLOAT:
	{
		switch (_addressWidth)
		{
		case 2:
			primitiveKnownSuccessive<uint16_t, float>();
			break;
		case 8:
			primitiveKnownSuccessive<uint64_t, float>();
			break;
		default:
			primitiveKnownSuccessive<uint32_t, float>();
		}
	}
	break;
	case DOUBLE:
	{
		switch (_addressWidth)
		{
		case 2:
			primitiveKnownSuccessive<uint16_t, double>();
			break;
		case 8:
			primitiveKnownSuccessive<uint64_t, double>();
			break;
		default:
			primitiveKnownSuccessive<uint32_t, double>();
		}
	}
	break;
	default: //INT32
	{
		switch (_addressWidth)
		{
		case 2:
			_setupFlags & SIGNED ? primitiveKnownSuccessive<uint16_t, int32_t>() : primitiveKnownSuccessive<uint16_t, uint32_t>();
			break;
		case 8:
			_setupFlags & SIGNED ? primitiveKnownSuccessive<uint64_t, int32_t>() : primitiveKnownSuccessive<uint64_t, uint32_t>();
			break;
		default:
			_setupFlags& SIGNED ? primitiveKnownSuccessive<uint32_t, int32_t>() : primitiveKnownSuccessive<uint32_t, uint32_t>();
		}
	}
	}
}

void MemoryCompare::MemCompare::selectColorKnownInitial()
{
	switch (_addressWidth)
	{
	case 2:
		colorKnownInitial<uint16_t>();
		break;
	case 8:
		colorKnownInitial<uint64_t>();
		break;
	default:
		colorKnownInitial<uint32_t>();
	}
}

void MemoryCompare::MemCompare::selectColorKnownSuccessive()
{
	switch (_addressWidth)
	{
	case 2:
		colorKnownSuccessive<uint16_t>();
		break;
	case 8:
		colorKnownSuccessive<uint64_t>();
		break;
	default:
		colorKnownSuccessive<uint32_t>();
	}
}

void MemoryCompare::MemCompare::selectTextKnownInitial()
{
	switch (_subsidiaryDatatype)
	{
	case 2:
		textKnownInitial<uint16_t>();
		break;
	case 8:
		textKnownInitial<uint64_t>();
		break;
	default:
		textKnownInitial<uint32_t>();
	}
}

void MemoryCompare::MemCompare::selectArrayKnownInitial() //ToDo, signed values, floats
{
	switch (_subsidiaryDatatype)
	{
	case INT8:
	{
		switch (_addressWidth)
		{
		case 2:
			arrayKnownInitial<uint16_t, uint8_t>();
			break;
		case 8:
			arrayKnownInitial<uint64_t, uint8_t>();
			break;
		default:
			arrayKnownInitial<uint32_t, uint8_t>();
		}
	}
	break;
	case INT16:
	{
		switch (_addressWidth)
		{
		case 2:
			arrayKnownInitial<uint16_t, uint16_t>();
			break;
		case 8:
			arrayKnownInitial<uint64_t, uint16_t>();
			break;
		default:
			arrayKnownInitial<uint32_t, uint16_t>();
		}
	}
	break;
	case INT64:
	{
		switch (_addressWidth)
		{
		case 2:
			arrayKnownInitial<uint16_t, uint64_t>();
			break;
		case 8:
			arrayKnownInitial<uint64_t, uint64_t>();
			break;
		default:
			arrayKnownInitial<uint32_t, uint64_t>();
		}
	}
	break;
	default: //INT32
	{
		switch (_addressWidth)
		{
		case 2:
			arrayKnownInitial<uint16_t, uint32_t>();
			break;
		case 8:
			arrayKnownInitial<uint64_t, uint32_t>();
			break;
		default:
			arrayKnownInitial<uint32_t, uint32_t>();
		}
	}
	}
}

void MemoryCompare::MemCompare::selectArrayKnownSuccessive() //ToDo, signed values, floats
{
	switch (_subsidiaryDatatype)
	{
	case INT8:
	{
		switch (_addressWidth)
		{
		case 2:
			arrayKnownSuccessive<uint16_t, uint8_t>();
			break;
		case 8:
			arrayKnownSuccessive<uint64_t, uint8_t>();
			break;
		default:
			arrayKnownSuccessive<uint32_t, uint8_t>();
		}
	}
	break;
	case INT16:
	{
		switch (_addressWidth)
		{
		case 2:
			arrayKnownSuccessive<uint16_t, uint16_t>();
			break;
		case 8:
			arrayKnownSuccessive<uint64_t, uint16_t>();
			break;
		default:
			arrayKnownSuccessive<uint32_t, uint16_t>();
		}
	}
	break;
	case INT64:
	{
		switch (_addressWidth)
		{
		case 2:
			arrayKnownSuccessive<uint16_t, uint64_t>();
			break;
		case 8:
			arrayKnownSuccessive<uint64_t, uint64_t>();
			break;
		default:
			arrayKnownSuccessive<uint32_t, uint64_t>();
		}
	}
	break;
	default: //INT32
	{
		switch (_addressWidth)
		{
		case 2:
			arrayKnownSuccessive<uint16_t, uint32_t>();
			break;
		case 8:
			arrayKnownSuccessive<uint64_t, uint32_t>();
			break;
		default:
			arrayKnownSuccessive<uint32_t, uint32_t>();
		}
	}
	}
}

void MemoryCompare::MemCompare::setValueWidth()
{
	switch (_superiorDatatype)
	{
	case ARRAY:
	{
		switch (_subsidiaryDatatype)
		{
		case INT8:case BOOL:
			_valueWidth = 1;
			break;
		case INT16:
			_valueWidth = 2;
			break;
		case INT64: case DOUBLE:
			_valueWidth = 8;
			break;
		default: //INT32, FLOAT
			_valueWidth = 4;
		}

		if (_subsidiaryDatatype <= INT64)
		{
			const OperativeArray<uint64_t> arr(_primaryKnownValueStr);
			_valueWidth *= arr.ItemCount();
		}
		else
		{
			const OperativeArray<double> arr(_primaryKnownValueStr);
			_valueWidth *= arr.ItemCount();
		}
	} break;
	case COLOR:
		switch (_subsidiaryDatatype)
		{
		case LitColor::RGBF:
			_valueWidth = 12;
			break;
		case LitColor::RGBAF:
			_valueWidth = 16;
			break;
		case LitColor::RGB565:
			_valueWidth = 2;
			break;
		default: //RGB888, RGBA8888
			_valueWidth = 4;
		}
		break;
	case TEXT:
		switch (_subsidiaryDatatype)
		{
		case MorphText::UTF16BE: case MorphText::UTF16LE: case MorphText::SHIFTJIS:
			_valueWidth = 2;
			break;
		case MorphText::UTF32BE: case MorphText::UTF32LE:
			_valueWidth = 4;
			break;
		default:
			_valueWidth = 1;
		}

		_valueWidth *= _primaryKnownValueStr.size() + 1;
		break;
	default: //PRIMITIVE
		switch (_subsidiaryDatatype)
		{
		case INT8:case BOOL:
			_valueWidth = 1;
			break;
		case INT16:
			_valueWidth = 2;
			break;
		case INT64: case DOUBLE:
			_valueWidth = 8;
			break;
		default: //INT32, FLOAT
			_valueWidth = 4;
		}
	}
}
	
void MemoryCompare::MemCompare::SetUp(const std::wstring& resultsDir, const uint16_t superiorDatatype, const uint16_t subsidiaryDatatype, const uint8_t addressWidth, const uint16_t alignment, const uint32_t setupFlags)
{
	MemCompareResults::SetResultsDir(resultsDir);
	MemCompareResults::ClearResultsDir(-1);
	GetInstance()._resultsDir = resultsDir;
	GetInstance()._superiorDatatype = superiorDatatype;
	GetInstance()._subsidiaryDatatype = subsidiaryDatatype;
	GetInstance()._addressWidth = addressWidth;
	GetInstance()._setupFlags = setupFlags;
	GetInstance()._alignment = alignment;
}

void MemoryCompare::MemCompare::NewIteration(const uint8_t condition, const uint16_t counterIteration, std::string& primaryKnownValue, std::string& secondaryKnownValue, const float precision, const uint32_t iterationFlags)
{
	GetInstance()._condition = condition;
	GetInstance()._iterationFlags = iterationFlags;
	GetInstance()._primaryKnownValueStr = primaryKnownValue;
	GetInstance()._secondaryKnownValueStr = secondaryKnownValue;
	GetInstance()._precision = precision;
	GetInstance()._counterIteration = counterIteration;
	GetInstance()._counterIterationIndex = counterIteration - 1;

	if (counterIteration < GetInstance()._iterationCount)
	{
		GetInstance()._results.erase(GetInstance()._results.begin() + counterIteration, GetInstance()._results.end());
		GetInstance()._results.back().LoadResults(false);
	}

	if (GetInstance()._iterationCount)
		GetInstance()._iterationCount = counterIteration + 1;
	else
		GetInstance()._iterationCount = 1;

	if (GetInstance()._iterationCount > 2 && !GetInstance()._setupFlags & CACHED) //clear results more than 1 iteration ago
		GetInstance()._results[GetInstance()._counterIterationIndex - 1].Clear();

	GetInstance().setValueWidth();

	//if(GetInstance()._iterationCount > 1)
		//GetInstance()._iterationCount = counterIteration;

	/*
	GetInstance()._iterationCount = GetInstance()._iterationCount ? counterIteration + 1 : 1;
	GetInstance()._counterIteration = GetInstance()._iterationCount > 1 ? counterIteration : 0;*/

	GetInstance()._results.emplace_back(GetInstance()._resultsDir, GetInstance()._iterationCount, GetInstance()._addressWidth, GetInstance()._valueWidth/*, false, false*/);
}

void MemoryCompare::MemCompare::ProcessNextRange(MemDump* range)
{
	if (GetInstance()._iterationCount > 1)
		GetInstance()._previousIterationRangeIndex = GetInstance()._results[GetInstance()._counterIterationIndex].GetRangeIndexOfStartingAddress(range->GetBaseAddress());

	GetInstance()._currentDumpAddress = range->GetDump<char*>();
	GetInstance()._currentDumpSize = range->GetSize();
	GetInstance()._currentBaseAddress = range->GetBaseAddress();
	GetInstance()._results.back().SetNewRange(range->GetBaseAddress());

	if (GetInstance()._superiorDatatype == ARRAY)
	{
		if (GetInstance()._iterationCount < 2)
		{
			//if (isKnownValue)
			GetInstance().selectArrayKnownInitial();
			//else
		}
		else
		{
			//if (isKnownValue)
			GetInstance().selectArrayKnownSuccessive();
			//else
		}
	}
	else if (GetInstance()._superiorDatatype == TEXT)
	{
		GetInstance().selectTextKnownInitial();
	}
	else if (GetInstance()._superiorDatatype == COLOR)
	{
		if (GetInstance()._iterationCount < 2)
		{
			//if (isKnownValue)
			GetInstance().selectColorKnownInitial();
			//else
		}
		else
		{
			//if (isKnownValue)
			GetInstance().selectColorKnownSuccessive();
			//else
		}
	}
	else // PRIMITIVE
	{
		if (GetInstance()._iterationCount < 2)
		{
			if (GetInstance()._iterationFlags & KNOWN)
				GetInstance().selectPrimitiveKnownInitial();
			else
				GetInstance().selectPrimitiveUnknownInitial();
		}
		else
		{
			if (GetInstance()._iterationFlags & KNOWN)
				GetInstance().selectPrimitiveKnownSuccessive();
			else
				GetInstance().selectPrimitiveUnknownSuccessive();
		}
	}

	if (!GetInstance()._setupFlags & CACHED)
		GetInstance().saveResults();

	GetInstance()._resultCount = GetInstance()._results.back().GetTotalResultCount();
}

const std::pair<uint64_t, uint16_t> MemoryCompare::MemCompare::GetSearchStats()
{
	return std::pair<uint64_t, uint16_t>(GetInstance()._resultCount, GetInstance()._iterationCount);
}

MemoryCompare::MemCompareResults& MemoryCompare::MemCompare::GetResults()
{
	return GetInstance()._results.back();
}

void MemoryCompare::MemCompare::Reset()
{
	MemCompareResults::ClearResultsDir(-1);
	GetInstance()._results.clear();
	GetInstance()._iterationCount = 0;
	GetInstance()._resultCount = 0;
	GetInstance()._resultsDir.clear();
	GetInstance()._superiorDatatype = 0;
	GetInstance()._subsidiaryDatatype = 2;
	GetInstance()._addressWidth = 4;
	GetInstance()._valueWidth = 4;
	GetInstance()._setupFlags = 0;
	GetInstance()._rangeCount = 0;
	GetInstance()._alignment = 4;
	GetInstance()._primaryKnownValueStr.clear();
	GetInstance()._secondaryKnownValueStr.clear();
	GetInstance()._condition = 0;
	GetInstance()._iterationFlags = 0;
	GetInstance()._counterIteration = 0;
	GetInstance()._precision = 1.0f;
	GetInstance()._counterIterationIndex = 0;
	GetInstance()._rangeCount = 0;
	GetInstance()._previousIterationRangeIndex = -1;
	GetInstance()._currentDumpAddress = nullptr;
	GetInstance()._currentDumpSize = 0;
	GetInstance()._currentBaseAddress = 0;
}

bool MemoryCompare::MemCompare::saveResults()
{
	return _results.back().SaveResults(_results.back().GetRangeCount() - 1, _setupFlags & ZIP_RESULTS);
}