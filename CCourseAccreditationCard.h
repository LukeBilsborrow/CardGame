#pragma once
#include "CAdminCard.h"
#include "Config.h"
#include "SCardAttributes.h"

class CCourseAccreditationCard : public CAdminCard
{
  public:
    CCourseAccreditationCard(SAttributeMap attributes, PlayerRef owner)
        : CAdminCard(attributes, owner){};

    void Play(CombatRef combat) override;
};
