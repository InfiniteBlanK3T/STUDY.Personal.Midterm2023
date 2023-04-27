#include "PrefixString.h"

PrefixString::PrefixString(char aExtension) noexcept :
	fExtension(aExtension)
{}

PrefixString::PrefixString(uint16_t aPrefix, char aExtension) noexcept :
	fPrefix(aPrefix),
	fExtension(aExtension)
{}

uint16_t PrefixString::getCode() const noexcept
{
	return fCode;
}

void PrefixString::setCode(uint16_t aCode) noexcept
{
	fCode = aCode;
}

uint16_t PrefixString::w() const noexcept
{
	return fPrefix;
}

char PrefixString::K() const noexcept
{
	return fExtension;
}

PrefixString PrefixString::operator+(char aExtension) const noexcept
{
	if (fCode != static_cast<uint16_t>(-1))
	{
		return PrefixString(fCode, aExtension);
	}
	return *this;
}

bool PrefixString::operator==(const PrefixString& aOther) const noexcept
{
	return this->fPrefix == aOther.fPrefix && this->fExtension == aOther.fExtension;
}

std::ostream& operator<<(std::ostream& aOStream, const PrefixString& aObject)
{
	aOStream << "(" << aObject.fCode << "," << aObject.fPrefix << "," << aObject.fExtension << ")";

	return aOStream;
}