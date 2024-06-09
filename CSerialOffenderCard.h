#pragma once
#include "CStudentCard.h"
class CSerialOffenderCard : public CStudentCard
{
  public:
    explicit CSerialOffenderCard(SAttributeMap attributes, PlayerRef owner)
        : CStudentCard(attributes, owner){};

    void Activate(CombatRef combat) override;
    int GetNextAttackPower(int power, int enemyResilience) const;
};
