#include "CMitigatingCircumstances.h"
int CMitigatingCircumstances::GetModifiedDamage(
    int baseDamage,
    CombatRef combat) const
{
    return baseDamage - this->GetMitigation();
}

int CMitigatingCircumstances::GetMitigation() const
{
    return this->mAttributes.mAttributes.at(0);
};
