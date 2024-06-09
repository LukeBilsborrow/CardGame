#pragma once
#include <string>

#include "Types.h"

struct SCardAttributes
{
    // should be static
    const std::map<std::string, ECardType> mTypeMap = {
        {"1", ECardType::EStudent},
        {"2", ECardType::EPlagiarismHearing}};
    std::string mName;
    ECardType mType;
    int mPower;
    int mResilience;

    bool TryAddValue(ETemplateAttribute key, const std::string& val);
};
