#include "CFeedbackForumCard.h"

#include "CCombat.h"

int CFeedbackForumCard::GetSpecialDamage() const
{
    return this->mAttributes.mAttributes.at(1);
};

int CFeedbackForumCard::GetHealValue() const
{
    return this->mAttributes.mAttributes.at(0);
};

void CFeedbackForumCard::Play(CombatRef combat)
{
    auto target = combat.get().SelectRandomTarget();
    auto isTargetFriendly = target.get().IsFriendly(std::ref(*this));
    // maybe we should override the print
    if (isTargetFriendly)
        {
            target.get().GainHealth(
                std::ref(*this),
                combat,
                this->GetHealValue());
        }
    else
        {
            target.get().TakeDamage(
                std::ref(*this),
                std::ref(combat),
                this->GetSpecialDamage());
        }
}