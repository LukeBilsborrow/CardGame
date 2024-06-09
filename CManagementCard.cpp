#include "CManagementCard.h"

#include <iostream>

#include "CCombat.h"
#include "CProfessor.h"
void CManagementCard::Play(CombatRef combat)
{
    // select random friendly card
    auto target = combat.get().SelectRandomFriendlyCard(std::ref(*this));

    if (!target.has_value())
        {
            // restore health to player
            this->GetOwner().get().GainHealth(
                std::ref(*this),
                combat,
                this->HEAL_VALUE);

            return;
        }
    // equip ourselves to target card
    target.value().get().AddManagementCard(std::ref(*this), combat);
}

int CManagementCard::GetModifiedDamage(int baseDamage, CombatRef combat) const
{
    return baseDamage;
};

int CManagementCard::GetAttackChange(int basePower, CombatRef combat) const
{
    return basePower;
};
