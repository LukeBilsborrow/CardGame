#pragma once
#include "CCard.h"
#include "CIAttackable.h"
#include "CManagementCard.h"
#include "Config.h"

// represents a card that can be played to the field
class CFieldCard : public CCard, public CIAttackable
{
  public:
    CFieldCard(SAttributeMap attributes, PlayerRef owner);
    virtual void Activate(CombatRef combat) = 0;
    int GetResilience(CombatRef combat) const;

    bool IsDead() const override;
    void Destroy();
    void TakeDamage(CardRef attackingCard, CombatRef combat, int damageAmount)
        override;
    bool IsFriendly(CardRef card) const override;
    void GainResilience(CardRef card, CombatRef combat, int gainedAmount);

    // wrapper for gain resilience for i attackable interface
    void GainHealth(CardRef card, CombatRef combat, int gainedAmount) override;
    int GetHealth(CombatRef combatRef) const override;

    void AddManagementCard(ManagementCardRef card, CombatRef combat);
    int GetPower(CombatRef combat) const override;
    virtual int GetPrecedence() const;

    std::string GetDisplay(CombatRef combat) const override;

  protected:
    bool mDestroyed = false;
    std::vector<ManagementCardRef> mManagementCards;

    int GetModifiedDamage(int damageAmount, CombatRef combat) const;

    // functions that provide effects with no print
    void TakeDamageNoPrint(int damageAmount);
    void GainResilienceNoPrint(int gainedAmount);
};
