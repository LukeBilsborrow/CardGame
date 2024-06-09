#pragma once
#include "CAdminCard.h"
#include "Config.h"
#include "SCardAttributes.h"

class CPlagiarismHearingCard : public CAdminCard
{
  public:
    CPlagiarismHearingCard(SAttributeMap attributes, PlayerRef owner)
        : CAdminCard(attributes, owner){};

    void Play(CombatRef combat) override;
};
