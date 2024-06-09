#pragma once
#include "CCard.h"
#include "CCombat.h"
#include "CFieldCard.h"
#include "CIAttackable.h"
class CStudentCard : public CFieldCard
{
  public:
    CStudentCard(SAttributeMap attributes, PlayerRef owner);
    void Play(CombatRef combat) override;
    void Activate(CombatRef combat) override;

    void GetAttackModifiers() const;
};
