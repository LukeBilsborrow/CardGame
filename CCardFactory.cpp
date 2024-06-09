#include "CCardFactory.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "CCard.h"
#include "CCombat.h"
#include "CCourseAccreditationCard.h"
#include "CEasyTargetCard.h"
#include "CFeedbackForumCard.h"
#include "CGraduateStudent.h"
#include "CICard.h"
#include "CIndustrialPlacementCard.h"
#include "CMitigatingCircumstances.h"
#include "CPassLeaderCard.h"
#include "CPlagiarismHearingCard.h"
#include "CResearchFundingCard.h"
#include "CSerialOffenderCard.h"
#include "CStudentCard.h"
#include "Types.h"
// words are delimited by any amount of whitespace
// if the next char after the whitespace is alpha, the selection continues
// until it reaches a space followed by a non alpha character
std::string ReadToWordEnd(std::istream& stream)
{
    bool done = false;
    std::vector<std::string> wordParts{};

    while (!done)
    {
        std::string temp{};
        // extract next word
        stream >> std::skipws >> temp;
        if (temp.empty())
        {
            break;
        }
        wordParts.push_back(temp);
        auto nextChar = (stream >> std::ws).peek();

        // if this extraction is not alpha

        if (isalpha((int)temp.at(0)) == 0)
        {
            done = true;
        }
        else
        {
            if (isalpha(nextChar) == 0)
            {
                done = true;
            }
        }
    }

    std::stringstream outStr{};
    for (size_t i = 0; i < wordParts.size(); ++i)
    {
        if (i != 0)
        {
            outStr << " ";
        }
        outStr << wordParts[i];
    }
    return outStr.str();
}

// this is to be able to parse a file consisting mainly of
// numbers but with unqoted strings without delimiters

std::vector<std::string> GetLineWords(const std::string& line)
{
    std::vector<std::string> words{};
    std::stringstream stream{line};
    std::string word;
    do
    {
        word = ReadToWordEnd(stream >> std::skipws);
        words.push_back(word);
    } while (!word.empty());

    return words;
}

// creates an attribute map from a raw string
SAttributeMap AttributeMapFromString(const std::string& rawString)
{
    std::map<std::string, ECardType> typeMap{
        {"1", ECardType::EStudent},
        {"2", ECardType::EPlagiarismHearing},
        {"3", ECardType::ECourseAccreditation},
        {"4", ECardType::EFeedbackForum},
        {"5", ECardType::EIndustrialPlacement},
        {"6", ECardType::EPassLeader},
        {"7", ECardType::EResearchFunding},
        {"8", ECardType::EMitigatingCircumstances},
        {"9", ECardType::EEasyTarget},
        {"10", ECardType::ESerialOffender},
        {"11", ECardType::EGraduateStudent}};
    // parse raw string to individual "words"
    std::vector<std::string> words{GetLineWords(rawString)};
    // std::vector<ETemplateAttribute> attributeOrder{
    //     ETemplateAttribute::EType,
    //     ETemplateAttribute::EName,
    //     ETemplateAttribute::EPower,
    //     ETemplateAttribute::EResilience};

    auto type = typeMap.at(words[0]);
    auto name = words[1];

    std::vector<int> attributes{};
    // error here if only the first two attributes are provided
    for (int i = 2; i < words.size() - 1; i++)
    {
        int parsed = std::stoi(words.at(i));
        attributes.push_back(parsed);
    }

    SAttributeMap attributeMap{SAttributeMap(type, name, attributes)};

    return attributeMap;
}

CardOwnerVector CCardFactory::GetCards(
    const std::vector<std::string>& rawLines,
    PlayerRef owner)
{
    auto cards = CardOwnerVector();
    for (size_t i = rawLines.size(); i-- != 0;)
    {
        const auto& cardTemplate = rawLines.at(i);

        CardPtr card = CCardFactory::GetCard(cardTemplate, owner);
        if (card)
        {
            cards.push_back(std::move(card));
        }
    }

    return cards;
};

CardPtr CCardFactory::GetCard(std::string rawLine, PlayerRef owner)
{
    auto attributeMap{AttributeMapFromString(rawLine)};

    // by default, return nullptr
    std::unique_ptr<CICard> outputObject;

    // if we have valid parsed attributes, return the card

    switch (attributeMap.mType)
    {
        case ECardType::EStudent:
        {
            outputObject = std::make_unique<CStudentCard>(attributeMap, owner);
            break;
        }
        case ECardType::EPlagiarismHearing:
        {
            outputObject =
                std::make_unique<CPlagiarismHearingCard>(attributeMap, owner);
            break;
        }
        case ECardType::ECourseAccreditation:
        {
            outputObject =
                std::make_unique<CCourseAccreditationCard>(attributeMap, owner);
            break;
        }
        case ECardType::EFeedbackForum:
        {
            outputObject =
                std::make_unique<CFeedbackForumCard>(attributeMap, owner);
            break;
        }
        case ECardType::EIndustrialPlacement:
        {
            outputObject =
                std::make_unique<CIndustrialPlacementCard>(attributeMap, owner);
            break;
        }
        case ECardType::EPassLeader:
        {
            outputObject =
                std::make_unique<CPassLeaderCard>(attributeMap, owner);
            break;
        }
        case ECardType::EResearchFunding:
        {
            outputObject =
                std::make_unique<CResearchFundingCard>(attributeMap, owner);
            break;
        }
        case ECardType::EMitigatingCircumstances:
        {
            outputObject =
                std::make_unique<CMitigatingCircumstances>(attributeMap, owner);
            break;
        }
        case ECardType::EEasyTarget:
        {
            outputObject =
                std::make_unique<CEasyTargetCard>(attributeMap, owner);
            break;
        }
        case ECardType::ESerialOffender:
        {
            outputObject =
                std::make_unique<CSerialOffenderCard>(attributeMap, owner);
            break;
        }
        case ECardType::EGraduateStudent:
        {
            outputObject =
                std::make_unique<CGraduateStudentCard>(attributeMap, owner);
            break;
        }
        default:
            break;
    }

    return std::move(outputObject);
};