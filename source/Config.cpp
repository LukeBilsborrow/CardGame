#include "Config.h"

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
#include "CICard.h"
#include "CIndustrialPlacementCard.h"
#include "CMitigatingCircumstances.h"
#include "CPassLeaderCard.h"
#include "CPlagiarismHearingCard.h"
#include "CResearchFundingCard.h"
#include "CSerialOffenderCard.h"
#include "CStudentCard.h"
#include "Types.h"

CardPtr GetCardFromAttributeString(
    const std::string& cardTemplate,
    PlayerRef owner)
{
    auto attributeMap{AttributeMapFromString(cardTemplate)};
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
        default:
            break;
    }

    return std::move(outputObject);
}
