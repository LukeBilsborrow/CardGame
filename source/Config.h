#pragma once
#include <string>
#include <vector>

#include "CDeck.h"
#include "SCardAttributes.h"
#include "Types.h"

struct SAttributeMap
{
    SAttributeMap(ECardType type, std::string name, std::vector<int> attributes)
        : mName{name},
          mType{type},
          mAttributes{attributes}
    {
    }
    std::string mName;
    ECardType mType;
    std::vector<int> mAttributes;
};

std::vector<std::string> GetLineWords(const std::string& line);
SAttributeMap AttributeMapFromString(const std::string& words);
CardPtr GetCardFromAttributeString(
    const std::string& cardTemplate,
    PlayerRef owner);
CardOwnerVector GetCardsFromCardTemplateArray(
    const std::vector<std::string>& templates,
    PlayerRef owner);