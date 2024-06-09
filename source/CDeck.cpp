#include "CDeck.h"

#include "CCard.h"
bool CDeck::AddCard(CardRef card)
{
    this->mCards.push_back(card);
    return true;
};

// this can fail
CardRef CDeck::DrawCard()
{
    CardRef output{std::ref(mCards.back())};
    mCards.pop_back();

    return output;
};

int CDeck::GetRemainingCards()
{
    return mCards.size();
}
