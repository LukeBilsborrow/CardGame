#pragma once
#include "CCard.h"
#include "Config.h"

class CManagementCard : public CCard
{
  public:
    explicit CManagementCard(SAttributeMap attributes, PlayerRef owner)
        : CCard(attributes, owner){};
    void Play(CombatRef combat) override;

    virtual int GetModifiedDamage(int baseDamage, CombatRef combat) const;
    virtual int GetAttackChange(int basePower, CombatRef combat) const;

  private:
    const int HEAL_VALUE = 2;
};
