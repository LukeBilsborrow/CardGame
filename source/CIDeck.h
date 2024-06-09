#pragma once
#include <memory>
#include <vector>

#include "Types.h"

class CIDeck
{
  public:
    virtual ~CIDeck() = default;
    virtual bool AddCard(CardRef card) = 0;
    virtual CardRef DrawCard() = 0;
    virtual int GetRemainingCards() = 0;
};
