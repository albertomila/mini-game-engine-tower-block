#pragma once

#include <Engine/Core/BasicTypes.h>
#include <string>


#if defined(_DEBUG)
	#define STRINGID_USESTRINGCONTENT
#endif

class CStringID
{
public:
	typedef U32 IDType;

	CStringID();

#if (defined(STRINGID_USESTRINGCONTENT))
	CStringID(const CStringID& other);
#endif

	explicit CStringID(const char* str);
	explicit CStringID(IDType crc, const char* str);
	explicit CStringID(IDType crc );
	IDType GetUniqueID() const { return _value; }
	void SetContent(const char* content);
	bool IsValid() const;
	void Invalidate();
	bool operator==(const CStringID& other) const;
	bool operator!=(const CStringID& other) const;
	bool operator<(const CStringID& other) const;
	bool operator<=(const CStringID& other) const;
	bool operator>(const CStringID& other) const;
	bool operator>=(const CStringID& other) const;

public:
	const static IDType InvalidID = 0xFFFFFFFF;

#ifdef STRINGID_USESTRINGCONTENT
	const char* c_str() const;
#endif //STRINGID_USESTRINGCONTENT

private:
	void SetContentWithExpectedCRC(const char* content, IDType crc);

	IDType _value;

#ifdef STRINGID_USESTRINGCONTENT
private:
	std::string _content;
#endif //STRINGID_USESTRINGCONTENT
};
