#pragma once
#include "CICard.h"
#include "Types.h"

class CHand
{
  public:
    int GetSize() const;
    bool AddCard(CardRef card);
    CardRef RemoveCard(int index);

  private:
    CardStack mCards;
};
