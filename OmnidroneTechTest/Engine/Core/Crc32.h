#pragma once
#include <Engine/Core/BasicTypes.h>

namespace CrcUtils
{
	U32 ComputeCrc32(const char* pData);
}

////////////////////////////////////////////////////////////////////////////////
class Crc32
{
public:
	Crc32();
	Crc32( const char* pData );
	~Crc32() = default;
	void Reset();
	void AddData( const char* pData );
	U32 GetCrc32() const;

private:
	U32 _crc;
};