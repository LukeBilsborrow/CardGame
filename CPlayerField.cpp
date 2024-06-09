#include "CPlayerField.h"

void CPlayerField::AddCard(FieldCardRef card)
{
    mField.push_back(card);
};

void CPlayerField::RemoveCard(FieldCardRef card)
{
    for (size_t i = 0; i < mField.size(); i++)
        {
            FieldCardRef candidateCard = mField.at(i);
            if (&card.get() == &candidateCard.get())
                {
                    mField.erase(mField.begin() + i);
                }
        }
};

const FieldCardArray& CPlayerField::GetCards() const
{
    return mField;
};

int CPlayerField::GetSize() const
{
    return mField.size();
};

// Cardref CPlayerField::GetCardIndex(int cardIndex)
//{
//     return mField.at(cardIndex);
// };
