#pragma once
#include "CCard.h"
#include "CICard.h"
class CCardFactory
{
  public:
    static CardPtr GetCard(std::string rawLine, PlayerRef owner);
    static CardOwnerVector GetCards(
        const std::vector<std::string>& rawLines,
        PlayerRef owner);
};
