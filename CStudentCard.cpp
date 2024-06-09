#include "CStudentCard.h"

#include <iostream>

#include "CCombat.h"
#include "CFieldCard.h"
#include "CProfessor.h"
#include "Config.h"

CStudentCard::CStudentCard(SAttributeMap attributes, PlayerRef owner)
    : CFieldCard(attributes, owner){};

void CStudentCard::Play(CombatRef combat)
{
    // add to table
    combat.get().AddToField(this->GetOwner(), std::ref(*this));
    // std::cout << owner.GetName() << " plays " << this->GetName() <<
    // std::endl;
};

void CStudentCard::Activate(CombatRef combat)
{
    auto target = combat.get().SelectFieldCardTarget(std::ref(*this));

    if (!target.has_value())
        {
            return;
        }
    target.value().get().TakeDamage(
        std::ref(*this),
        std::ref(combat),
        this->GetPower(combat));
};

void CStudentCard::GetAttackModifiers() const {};
