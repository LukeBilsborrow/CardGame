#pragma once
#include "CStudentCard.h"
class CIndustrialPlacementCard : public CStudentCard
{
  public:
    CIndustrialPlacementCard(SAttributeMap attributes, PlayerRef owner)
        : CStudentCard(attributes, owner){};

    void Activate(CombatRef combat) override;
    int GetHealthBoostAmount() const;
};
