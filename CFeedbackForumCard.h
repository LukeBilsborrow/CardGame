#pragma once

#include "CAdminCard.h"
#include "Config.h"
#include "SCardAttributes.h"

class CFeedbackForumCard : public CAdminCard
{
  public:
    CFeedbackForumCard(SAttributeMap attributes, PlayerRef owner)
        : CAdminCard(attributes, owner){};

    void Play(CombatRef combat) override;
    int GetSpecialDamage() const;
    int GetHealValue() const;
};
