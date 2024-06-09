#include "CCourseAccreditationCard.h"

#include "CCombat.h"

void CCourseAccreditationCard::Play(CombatRef combat)
{
    auto targets = combat.get().SelectAllEnemies(std::ref(*this));

    // deal damage to each enemy
    for (auto target : targets)
        {
            target.get().TakeDamage(
                std::ref(*this),
                std::ref(combat),
                this->GetPower(combat));
        }
}