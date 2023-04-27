#include "LZWCompressor.h"

bool LZWCompressor::readK() noexcept
{
    if (fIndex >= fInput.size())
    {
        fK = -1;
        return false;
    }
    fK = fInput[fIndex++];
    return true;
}

void LZWCompressor::start()
{
    fTable.initialize();
    if (readK())
    {
        fW.setCode(fK);
        fCurrentCode = nextCode();
    }
}

uint16_t LZWCompressor::nextCode()
{
    if (fK == -1)
    {
        fIndex++;
        return fCurrentCode;
    }

    while (readK())
    {
        PrefixString tempK = fW + fK;

        if (fTable.contains(tempK))
        {
            fW = tempK;
        }
        else
        {
            uint16_t outputCode = fW.getCode();
            fTable.add(tempK);
            fW = fTable.lookupStart(fK);
            fCurrentCode = fW.getCode();

            return outputCode;
        }
    }
    fCurrentCode = fW.getCode();
    return fCurrentCode;
}

LZWCompressor::LZWCompressor(const std::string& aInput) :
    fInput(aInput), fIndex(0)
{
    start();
}

const uint16_t& LZWCompressor::operator*() const noexcept
{
    return fCurrentCode;
}

LZWCompressor& LZWCompressor::operator++() noexcept
{
    fCurrentCode = nextCode();
    return *this;
}

LZWCompressor LZWCompressor::operator++(int) noexcept
{
    LZWCompressor temp(*this);
    ++(*this);
    return temp;
}

bool LZWCompressor::operator==(const LZWCompressor& aOther) const noexcept
{
    return (fInput == aOther.fInput) && (fIndex == aOther.fIndex) && (fK == aOther.fK) && (fCurrentCode == aOther.fCurrentCode);
}

bool LZWCompressor::operator!=(const LZWCompressor& aOther) const noexcept
{
    return !(*this == aOther);
}

LZWCompressor LZWCompressor::begin() const noexcept
{
    LZWCompressor temp(*this);
    temp.fIndex = 0;
    temp.start();
    return temp;
}

LZWCompressor LZWCompressor::end() const noexcept
{
    LZWCompressor temp(*this);
    temp.fK = -1;
    temp.fIndex = fInput.size() + 1;
    return temp;
}
