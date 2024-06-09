#include "CResearchFundingCard.h"
int CResearchFundingCard::GetAttackChange(int basePower, CombatRef combat) const
{
    return basePower + this->GetPowerIncrement();
}

int CResearchFundingCard::GetPowerIncrement() const
{
    return this->mAttributes.mAttributes.at(0);
};
