#include "CCard.h"

#include <iostream>

#include "CProfessor.h"
#include "Config.h"

CCard::CCard(SAttributeMap attributes, PlayerRef owner)
    : mAttributes{attributes},
      mOwner{owner} {};

std::string CCard::GetName() const
{
    return this->mAttributes.mName;
}

std::string CCard::GetDisplay(CombatRef combat) const
{
    return this->GetName();
}
int CCard::GetPower(CombatRef combat) const
{
    return this->mAttributes.mAttributes.at(0);
}

PlayerRef CCard::GetOwner() const
{
    return this->mOwner.value();
};
void CCard::SetOwner(PlayerRef newOwner)
{
    this->mOwner = newOwner;
};

ECardType CCard::GetType() const
{
    return this->mAttributes.mType;
};

// ECardType CCard::_GetType() const
//{
//     return this->mAttributes.mType;
// }
