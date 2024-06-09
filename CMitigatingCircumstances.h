#pragma once
#include "CManagementCard.h"
class CMitigatingCircumstances : public CManagementCard
{
  public:
    CMitigatingCircumstances(SAttributeMap attributes, PlayerRef owner)
        : CManagementCard(attributes, owner){};
    int GetModifiedDamage(int baseDamage, CombatRef combat) const override;
    int GetMitigation() const;
};
