#pragma once
#include "CICard.h"
#include "CIDeck.h"
#include "Types.h"
class CDeck : public CIDeck
{
  public:
    CDeck() = default;
    bool AddCard(CardRef card) override;
    CardRef DrawCard() override;
    int GetRemainingCards() override;

  private:
    CardStack mCards;
};
