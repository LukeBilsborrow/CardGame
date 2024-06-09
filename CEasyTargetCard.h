#pragma once
#include "CStudentCard.h"
class CEasyTargetCard : public CStudentCard
{
  public:
    CEasyTargetCard(SAttributeMap attributes, PlayerRef owner)
        : CStudentCard(attributes, owner){};

    int GetPrecedence() const override;
};
