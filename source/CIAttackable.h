#pragma once
#include "Types.h"
class CIAttackable
{
  public:
    virtual void
    TakeDamage(CardRef attackingCard, CombatRef combat, int damageAmount) = 0;
    virtual bool IsFriendly(CardRef target) const = 0;
    virtual bool IsDead() const = 0;
    virtual void
    GainHealth(CardRef card, CombatRef combat, int gainedAmount) = 0;
    virtual int GetHealth(CombatRef combat) const = 0;
};
