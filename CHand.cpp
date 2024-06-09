#include "CHand.h"

#include "Types.h"

int CHand::GetSize() const
{
    return mCards.size();
};

bool CHand::AddCard(CardRef card)
{
    this->mCards.push_back(std::move(card));
    return true;
};

CardRef CHand::RemoveCard(int index)
{
    auto val = mCards.at(index);
    mCards.erase(mCards.begin() + index);
    return val;
};
