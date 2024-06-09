#pragma once
#include "CCard.h"
#include "CFieldCard.h"
#include "Types.h"

class CPlayerField
{
  public:
    CPlayerField() = default;
    void AddCard(FieldCardRef card);
    void RemoveCard(FieldCardRef card);
    const FieldCardArray& GetCards() const;
    int GetSize() const;
    // CardRef GetCardIndex(int cardIndex);

  private:
    FieldCardArray mField;
};
