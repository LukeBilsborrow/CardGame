#pragma once
#include "CStudentCard.h"
class CPassLeaderCard : public CStudentCard
{
  public:
    CPassLeaderCard(SAttributeMap attributes, PlayerRef owner)
        : CStudentCard(attributes, owner){};

    int GetPower(CombatRef combat) const override;
};
