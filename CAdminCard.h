#pragma once
#include "CCard.h"
#include "Config.h"
// this class doesn't actually do anything
// it's just here to show how that i understand that it fits
// into the hierarchy
class CAdminCard : public CCard
{
  public:
    explicit CAdminCard(SAttributeMap attributes, PlayerRef owner)
        : CCard(attributes, owner){};
};
