#include "CProfessor.h"

#include <iostream>
#include <string>

CProfessor::CProfessor(int id, const std::string& name, int prestige)
    : mId{id},
      mPrestige{prestige},
      mName{name}
{
}

int CProfessor::GetId() const
{
    return mId;
};

std::string CProfessor::GetName() const
{
    return mName;
};

int CProfessor::GetPrestige() const
{
    return mPrestige;
};

// fulfil iattackable interface with wrapper
int CProfessor::GetHealth(CombatRef combat) const
{
    return this->GetPrestige();
};

bool CProfessor::IsDead() const
{
    return this->mPrestige <= 0;
}

DeckRef CProfessor::GetDeck()
{
    // this can reference null
    // it relies on the fact that the deck is set just after instantiation
    // they both depend on references to the other so one must be constructed
    // first, or they must all be optional (which is a headache)
    return this->mBaseDeck.value();
};
void CProfessor::SetDeck(DeckRef deck)
{
    this->mBaseDeck = deck;
};

void CProfessor::OnDeath()
{
    SetEliminated(true);
}
void CProfessor::TakeDamage(
    CardRef attackingCard,
    CombatRef combat,
    int damageAmount)
{
    this->mPrestige -= damageAmount;

    std::cout << attackingCard.get().GetName() << " attacks " << this->GetName()
              << " for " << damageAmount << " damage. ";
    // no output for now

    std::cout << this->GetName() << "'s prestige is now " << this->GetPrestige()
              << std::endl;
    if (GetPrestige() <= 0)
        {
            OnDeath();
        }
};

void CProfessor::GainHealth(
    CardRef otherCard,
    CombatRef combat,
    int gainedAmount)
{
    std::cout << otherCard.get().GetName() << " heals " << this->GetName()
              << ". ";
    this->mPrestige += gainedAmount;

    std::cout << this->GetName() << "'s prestige is now " << this->GetPrestige()
              << std::endl;
};
bool CProfessor::IsFriendly(CardRef card) const
{
    return this->GetId() == card.get().GetOwner().get().GetId();
};

bool CProfessor::IsEliminated() const
{
    return mEliminated;
};

void CProfessor::SetEliminated(bool eliminationStatus)
{
    std::cout << GetName() << " is eliminated." << std::endl;
    mEliminated = eliminationStatus;
};
