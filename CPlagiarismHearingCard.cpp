#include "CPlagiarismHearingCard.h"

#include "CCombat.h"
void CPlagiarismHearingCard::Play(CombatRef combat)
{
    auto target = combat.get().SelectRandomEnemy(GetOwner());

    // maybe we should override the print
    target.get().TakeDamage(
        std::ref(*this),
        std::ref(combat),
        this->GetPower(combat));
}