#pragma once
#include "CManagementCard.h"
class CResearchFundingCard : public CManagementCard
{
  public:
    CResearchFundingCard(SAttributeMap attributes, PlayerRef owner)
        : CManagementCard(attributes, owner){};
    int GetAttackChange(int basePower, CombatRef combat) const override;
    int GetPowerIncrement() const;
};
