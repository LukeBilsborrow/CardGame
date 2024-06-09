#include "CGraduateStudent.h"
void CGraduateStudentCard::Activate(CombatRef combat)
{
    // run base card logic
    CStudentCard::Activate(combat);
    // apply the heal from this derived type
    this->GetOwner().get().GainHealth(
        std::ref(*this),
        combat,
        this->GetHealthBoost());
}

int CGraduateStudentCard::GetHealthBoost() const
{
    return this->mAttributes.mAttributes.at(2);
}