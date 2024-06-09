#pragma once
#include "CProfessor.h"
#include "CStudentCard.h"
class CGraduateStudentCard : public CStudentCard
{
  public:
    CGraduateStudentCard(SAttributeMap attributes, PlayerRef owner)
        : CStudentCard(attributes, owner){};

    void Activate(CombatRef combat) override;

    int GetHealthBoost() const;
};
