#pragma once
#include <optional>

#include "CICard.h"
#include "Config.h"
#include "SCardAttributes.h"

// this class is abstract as it does not implement all
// CICard methods

// but it provides some nice base methods
class CCard : public CICard
{
  public:
    // TODO: make private
    SAttributeMap mAttributes;
    explicit CCard(SAttributeMap attributes, PlayerRef owner);
    std::string GetDisplay(CombatRef combat) const override;
    std::string GetName() const override;
    int GetPower(CombatRef combat) const override;
    PlayerRef GetOwner() const override;
    ECardType GetType() const override;
    void SetOwner(PlayerRef newOwner) override;

  private:
    std::optional<PlayerRef> mOwner;

    // ECardType _GetType() const override;
};
