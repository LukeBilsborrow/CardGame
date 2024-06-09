#include "CFieldCard.h"

#include <iostream>
#include <sstream>

#include "CCombat.h"
#include "CProfessor.h"
CFieldCard::CFieldCard(SAttributeMap attributes, PlayerRef owner)
    : CCard(attributes, owner){};

void CFieldCard::Destroy()
{
    this->mDestroyed = true;
    std::cout << GetName() << " is destroyed" << std::endl;
}

bool CFieldCard::IsDead() const
{
    return this->mDestroyed;
}

void CFieldCard::TakeDamageNoPrint(int damageAmount)
{
    this->mAttributes.mAttributes.at(1) -= damageAmount;
}

int CFieldCard::GetPower(CombatRef combat) const
{
    int basePower = this->mAttributes.mAttributes.at(0);
    for (auto modifier : this->mManagementCards)
        {
            basePower = modifier.get().GetAttackChange(basePower, combat);
        }
    return basePower;
}

int CFieldCard::GetModifiedDamage(int damageAmount, CombatRef combat) const
{
    int baseDamage = damageAmount;
    for (auto modifier : this->mManagementCards)
        {
            baseDamage = modifier.get().GetModifiedDamage(baseDamage, combat);
        }

    // we don't want negative damages, clamp the min to 0
    return std::max(0, baseDamage);
}

void CFieldCard::TakeDamage(
    CardRef attackingCard,
    CombatRef combat,
    int damageAmount)
{
    int newDamage = this->GetModifiedDamage(damageAmount, combat);
    std::cout << attackingCard.get().GetDisplay(combat) << " attacks "
              << this->GetDisplay(combat) << " for " << newDamage
              << " damage. ";

    this->TakeDamageNoPrint(newDamage);

    // check for destruction
    if (this->GetResilience(combat) > 0)
        {
            std::cout << this->GetName() << "'s resilience is now "
                      << this->GetResilience(combat) << std::endl;
        }
    else
        {
            // card should be destroyed here
            std::cout << this->GetName() << " is defeated" << std::endl;
            this->mDestroyed = true;
            combat.get().Destroy(std::ref(*this));
        }
}

int CFieldCard::GetResilience(CombatRef combat) const
{
    return mAttributes.mAttributes.at(1);
}

void CFieldCard::GainResilienceNoPrint(int gainedAmount)
{
    this->mAttributes.mAttributes.at(1) += gainedAmount;
}

void CFieldCard::GainResilience(
    CardRef otherCard,
    CombatRef combat,
    int gainedAmount)
{
    this->GainResilienceNoPrint(gainedAmount);

    std::cout << otherCard.get().GetName() << " heals " << this->GetName()
              << " for " << gainedAmount << ". ";
    std::cout << this->GetDisplay(combat) << "'s resilience is now "
              << this->GetResilience(combat) << std::endl;
};

void CFieldCard::GainHealth(
    CardRef otherCard,
    CombatRef combat,
    int gainedAmount)
{
    this->GainResilience(otherCard, combat, gainedAmount);
};

int CFieldCard::GetHealth(CombatRef combat) const
{
    return this->GetResilience(combat);
}

bool CFieldCard::IsFriendly(CardRef card) const
{
    return card.get().GetOwner().get().GetId() ==
           this->GetOwner().get().GetId();
}

void CFieldCard::AddManagementCard(ManagementCardRef card, CombatRef combat)
{
    std::cout << card.get().GetName() << " attaches to "
              << this->GetDisplay(combat) << std::endl;
    this->mManagementCards.push_back(card);
}

std::string CFieldCard::GetDisplay(CombatRef combat) const
{
    std::stringstream outStream{};
    outStream << this->GetOwner().get().GetName() << "'s " << this->GetName()
              << "(" << this->GetResilience(combat) << ")";

    return outStream.str();
}
// set the deafult precedence level
int CFieldCard::GetPrecedence() const
{
    return 0;
}