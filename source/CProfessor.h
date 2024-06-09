#pragma once
#include <optional>
#include <string>

#include "CDeck.h"
#include "CIAttackable.h"
#include "Types.h"
// base concrete implementation
class CProfessor : public CIAttackable
{
  public:
    explicit CProfessor(int id, const std::string& name, int prestige = 30);

    int GetId() const;
    std::string GetName() const;
    int GetPrestige() const;

    // IAttackable interface methods
    int GetHealth(CombatRef combat) const override;
    void GainHealth(CardRef card, CombatRef combat, int gainedAmount) override;

    bool IsDead() const override;
    bool IsFriendly(CardRef card) const override;

    bool IsEliminated() const;
    void SetEliminated(bool eliminationStatus);

    void OnDeath();
    void TakeDamage(CardRef attackingCard, CombatRef combat, int damageAmount)
        override;
    DeckRef GetDeck();
    void SetDeck(DeckRef deck);

  private:
    bool mEliminated = false;
    std::optional<DeckRef> mBaseDeck;
    int mId;
    int mPrestige;
    std::string mName;
};
