#include "LZWTable.h"

LZWTable::LZWTable(uint16_t aInitialCharacters):
	fInitialCharacters(aInitialCharacters > 128 ? 128 : aInitialCharacters)

{
	initialize();
}

void LZWTable::initialize()
{
	for (uint16_t i = 0; i < fInitialCharacters; i++)
	{
		fEntries[i] = PrefixString(static_cast<char>(i));
		fEntries[i].setCode(i);
	}
	fIndex = fInitialCharacters;
}

const PrefixString& LZWTable::lookupStart(char aK) const noexcept
{
	return fEntries[static_cast<uint16_t>(aK)];
}

bool LZWTable::contains(PrefixString& aWK) const noexcept
{
	if (aWK.w() != static_cast<uint16_t>(-1) )
	{
		for (uint16_t i = fIndex - 1; i >= aWK.w(); i--)
		{
			if (aWK == fEntries[i])
			{
				aWK.setCode(fEntries[i].getCode());
				return true;
			}
		}
	}
	return false;
}

void LZWTable::add(PrefixString& aWK) noexcept
{
	if (aWK.w() != static_cast<uint16_t>(-1))
	{
		aWK.setCode(fIndex);
		fEntries[fIndex] = aWK;		
		fIndex++;
	}
}
