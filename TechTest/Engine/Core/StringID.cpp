#include "stdafx.h"
#include <Engine/Core/StringID.h>

#include <Engine/Core/Crc32.h>

void CStringID::SetContent(const char* content)
{
	if(content == NULL || content[0] == '\0')
	{
		_value = InvalidID;
#ifdef STRINGID_USESTRINGCONTENT
		_content.clear();
#endif
	}
	else
	{
		_value = CrcUtils::ComputeCrc32(content);
#ifdef STRINGID_USESTRINGCONTENT
		_content = content;
#endif
	}
}

void CStringID::SetContentWithExpectedCRC(const char* content, IDType crc)
{
	SetContent(content);

	if (crc != _value)
	{
		Invalidate();
	}
}

CStringID::CStringID()
	: _value(InvalidID)
{
}

CStringID::CStringID(const char* str)
{
	SetContent(str);
}

#if (defined(STRINGID_USESTRINGCONTENT))

CStringID::CStringID(const CStringID& other)
{
	_value = other._value;
#ifdef STRINGID_USESTRINGCONTENT
	_content = other._content;
#endif
}
#endif


CStringID::CStringID(IDType crc)
	: _value(crc)
{
}

#if defined(STRINGID_USESTRINGCONTENT)
CStringID::CStringID(IDType crc, const char* str)
{
	SetContentWithExpectedCRC(str, crc);
}

#else
CStringID::CStringID(IDType crc, const char*)
	: _value(crc)
{
}
#endif


#ifdef STRINGID_USESTRINGCONTENT
const char* CStringID::c_str() const
{
	return _content.c_str();
}
#endif 


bool CStringID::IsValid() const
{
	return _value != static_cast<IDType>(InvalidID);
}

void CStringID::Invalidate()
{
	SetContent(NULL);
}

bool CStringID::operator==(const CStringID& other) const
{
	return GetUniqueID() == other.GetUniqueID();
}
bool CStringID::operator!=(const CStringID& other) const
{
	return GetUniqueID() != other.GetUniqueID();
}

bool CStringID::operator<(const CStringID& other) const
{
	return GetUniqueID() < other.GetUniqueID();
}

bool CStringID::operator<=(const CStringID& other) const
{
	return GetUniqueID() <= other.GetUniqueID();
}

bool CStringID::operator>(const CStringID& other) const
{
	return GetUniqueID() > other.GetUniqueID();
}

bool CStringID::operator>=(const CStringID& other) const
{
	return GetUniqueID() >= other.GetUniqueID();
}