#include "CIndustrialPlacementCard.h"

#include <iostream>

void CIndustrialPlacementCard::Activate(CombatRef combat)
{
    // activate as normal
    CStudentCard::Activate(combat);
    // gain one resilience
    this->GainResilienceNoPrint(this->GetHealthBoostAmount());
    std::cout << this->GetName() << " increases it's resilience by "
              << this->GetHealthBoostAmount() << " to a total of "
              << this->GetResilience(combat) << std::endl;
};

int CIndustrialPlacementCard::GetHealthBoostAmount() const
{
    return this->mAttributes.mAttributes.at(2);
}
