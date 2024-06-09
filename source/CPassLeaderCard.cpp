#include "CPassLeaderCard.h"

#include "CProfessor.h"
int CPassLeaderCard::GetPower(CombatRef combat) const
{
    // use the base logic so we get the effects of our
    // management cards applied
    int basePower = 0;
    // TODO: rework to get player cards straight from combat
    auto& combatData = combat.get().GetPlayerCombatData(this->GetOwner());

    auto friendlyCards = combatData.mField->GetCards();
    for (auto& card : friendlyCards)
        {
            if (card.get().GetType() == ECardType::EPassLeader)
                {
                    basePower += 1;
                }
        }

    return basePower;
};
