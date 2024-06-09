#include "CCombat.h"

#include <iostream>
#include <optional>

#include "CDeck.h"
#include "CFieldCard.h"
#include "CHand.h"
#include "CPlayerField.h"
#include "CProfessor.h"
#include "Utils.h"
#include "WinnowingGame.h"

const int BASE_PRECEDENCE{0};

CCombat::CCombat(CWinnowingGame& gameRef) : mGameRef{gameRef}
{
}
void CCombat::AddPlayer(CProfessor& player)
{
    // create the new required elements for the player
    // and add the results to a player data struct

    // this might create a copy before adding to the array
    // which is a problem because of the unique ptrs

    auto newPlayerData = std::make_unique<SPlayerCombatData>(
        std::ref(player),
        player.GetDeck(),
        std::make_unique<CHand>(),
        std::make_unique<CPlayerField>());
    mPlayerData.try_emplace(player.GetId(), std::move(newPlayerData));
}

std::optional<CardRef> CCombat::DrawCard(PlayerRef player, bool print)
{
    std::optional<CardRef> drawnCard{};
    const auto& playerData = *(mPlayerData.at(player.get().GetId()));

    // maybe this should be added to the player data scruct

    if (playerData.mDeck.get().GetRemainingCards() == 0)
        {
            if (print)
                {
                    std::cout << player.get().GetName()
                              << " has no more cards to draw." << std::endl;
                }
        }
    else
        {
            drawnCard = playerData.mDeck.get().DrawCard();
            playerData.mHand->AddCard(drawnCard.value());
            // print player draws card
            if (print)
                {
                    std::cout << player.get().GetName() << " draws "
                              << drawnCard.value().get().GetName() << "."
                              << std::endl;
                }
        }

    return drawnCard;
}

CardRef CCombat::RemoveCardFromPlayer(CProfessor& professor, int index)
{
    auto& combatData = this->GetPlayerCombatData(std::ref(professor));
    auto removedCard = combatData.mHand->RemoveCard(index);
    return removedCard;
};

void CCombat::Destroy(FieldCardRef card)
{
    // targetCard.get().OnDestroy();
    auto& combatData = this->GetPlayerCombatData(card.get().GetOwner());

    combatData.mField->RemoveCard(card);
};

// returns a bool representing whether a player died or not
// true if nobody died, false otherwise
bool CCombat::PerformFieldAttacks(CProfessor& player)
{
    bool gameOver = false;
    auto& combatData = GetPlayerCombatData(player);

    std::optional<PlayerRef> deadPlayer{};

    for (auto& card : combatData.mField->GetCards())
        {
            card.get().Activate(*this);
            // Do not continue with attacks if the game is over
            if (IsGameOver())
                {
                    gameOver = true;
                    break;
                }
        }

    return gameOver;
};

SPlayerCombatData& CCombat::GetPlayerCombatData(PlayerRef player) const
{
    return *(mPlayerData.at(player.get().GetId()));
};

void CCombat::AddToField(CProfessor& player, FieldCardRef card)
{
    auto& combatData = GetPlayerCombatData(player);
    combatData.mField->AddCard(card);
};

void CCombat::RemoveFromPlayOrder(CardRef card)
{
    for (int i = 0; i < mFieldPlayedOrder.size(); i++)
        {
            auto candidateCard = mFieldPlayedOrder.at(i);
            if (&(card.get()) == &(candidateCard.get()))
                {
                    // remove this value from the order
                    mFieldPlayedOrder.erase(mFieldPlayedOrder.begin() + i);
                }
        }
}
int CCombat::GetHandSize(PlayerRef player) const
{
    auto& combatData = GetPlayerCombatData(player);
    return combatData.mHand->GetSize();
}
int CCombat::GetFieldSize(PlayerRef player) const
{
    auto& combatData = GetPlayerCombatData(player);
    return combatData.mField->GetSize();
};

// There should always be at least one enemy (an enemy player)
// otherwise the game should have ended
AttackableRef CCombat::SelectRandomEnemy(PlayerRef player)
{
    // the potential targets will be selected from the highest precedence level
    // almost all cards and players have a precedence of 0
    // special cards may have a precedence of 1+ to override this
    std::map<int, std::vector<AttackableRef>> precedenceLevels{};

    for (auto& pair : mPlayerData)
        {
            auto& id = pair.first;
            auto& data = pair.second;
            // skip the player making the request and dead players
            if (data->mPlayer.get().GetId() == player.get().GetId() ||
                data->mPlayer.get().IsEliminated())
                {
                    continue;
                }

            precedenceLevels[BASE_PRECEDENCE].push_back(data->mPlayer);

            for (auto& card : data->mField->GetCards())
                {
                    precedenceLevels[card.get().GetPrecedence()].push_back(
                        card);
                }
        }

    int highestPrecedence = -1;
    std::vector<std::reference_wrapper<CIAttackable>> potentialTargets{};

    for (auto& pair : precedenceLevels)
        {
            if (pair.first > highestPrecedence)
                {
                    highestPrecedence = pair.first;
                    potentialTargets = pair.second;
                }
        }
    // potential targets will be our highest precedence level now

    // the largest number this can generate is the index of the last element
    int selectedIndex = Random(potentialTargets.size());
    return potentialTargets.at(selectedIndex);
};

// select any target. includes players and cards
// it should not be possible for there to be no targets
// as the player that played the card must still be alive

// this method returns a player or a card
std::reference_wrapper<CIAttackable> CCombat::SelectRandomTarget()
{
    std::vector<AttackableRef> potentialTargets{};

    for (auto& pair : mPlayerData)
        {
            auto& id = pair.first;
            auto& data = pair.second;

            // exclude this player from the results if they are eliminated
            if (data->mPlayer.get().IsEliminated())
                {
                    continue;
                }

            potentialTargets.push_back(data->mPlayer);

            for (auto& card : data->mField->GetCards())
                {
                    potentialTargets.push_back(card);
                }
        }

    // return the target
    int selectedIndex = Random(potentialTargets.size());
    return potentialTargets.at(selectedIndex);
}

// TODO: make optional
std::optional<AttackableRef> CCombat::SelectFieldCardTarget(CardRef card)
{
    auto owner = card.get().GetOwner();

    std::vector<PlayerRef> otherPlayers = GetOtherLivingPlayers(owner);
    std::map<int, std::vector<std::reference_wrapper<CIAttackable>>>
        precedenceLevels{};
    for (auto& player : otherPlayers)
        {
            auto& playerCombatData = GetPlayerCombatData(player);

            for (auto& card : playerCombatData.mField->GetCards())
                {
                    precedenceLevels[card.get().GetPrecedence()].push_back(
                        card);
                }
        }

    int highestPrecedence = -1;
    std::vector<std::reference_wrapper<CIAttackable>> potentialTargets{};

    for (auto& pair : precedenceLevels)
        {
            if (pair.first > highestPrecedence)
                {
                    highestPrecedence = pair.first;
                    potentialTargets = pair.second;
                }
        }
    // potential targets will be our highest precedence level now

    // if no valid field cards were found
    std::optional<AttackableRef> chosenTarget{};
    if (potentialTargets.size() > 0)
        {
            // return the field card
            int selectedIndex = Random(potentialTargets.size());
            chosenTarget = potentialTargets.at(selectedIndex);
        }
    else if (otherPlayers.size() > 0)
        {
            // return an enemy player

            int selectedIndex = Random(otherPlayers.size());
            chosenTarget = otherPlayers.at(selectedIndex);
        }

    return chosenTarget;
};

std::vector<AttackableRef> CCombat::SelectAllEnemies(CardRef card)
{
    auto owner = card.get().GetOwner();
    std::vector<PlayerRef> otherPlayers = GetOtherLivingPlayers(owner);
    std::vector<std::reference_wrapper<CIAttackable>> potentialTargets{};

    for (auto player : otherPlayers)
        {
            auto& playerCombatData = GetPlayerCombatData(player);
            potentialTargets.push_back(player);

            for (auto& card : playerCombatData.mField->GetCards())
                {
                    potentialTargets.push_back(card);
                }
        }

    return potentialTargets;
};

std::optional<FieldCardRef> CCombat::SelectRandomFriendlyCard(CardRef card)
{
    std::vector<FieldCardRef> potentialTargets{};

    auto& combatData = GetPlayerCombatData(card.get().GetOwner());
    for (auto& card : combatData.mField->GetCards())
        {
            potentialTargets.push_back(card);
        }

    // set the value of the optional if we have a target, else leave it empty
    std::optional<FieldCardRef> selectedTarget{};
    if (potentialTargets.size() > 0)
        {
            int selectedIndex = Random(potentialTargets.size());
            selectedTarget = potentialTargets.at(selectedIndex);
        }

    return selectedTarget;
};

PlayerRef CCombat::SelectRandomEnemyPlayer(CardRef card)
{
    std::vector<PlayerRef> otherPlayers =
        GetOtherLivingPlayers(card.get().GetOwner());
    // random does not include the top of the range
    // so we use the length of the vector as the random value
    int selectedIndex = Random(otherPlayers.size());
    return otherPlayers.at(selectedIndex);
}

PlayerRefVector CCombat::GetOtherLivingPlayers(PlayerRef player) const
{
    PlayerRefVector outVec{};
    for (auto& pair : mPlayerData)
        {
            auto candidatePlayer = pair.second->mPlayer;
            // if the player is eliminated or is the target player
            // skip this loop
            if (candidatePlayer.get().IsEliminated() ||
                (candidatePlayer.get().GetId() == player.get().GetId()))
                {
                    continue;
                }

            outVec.push_back(std::ref(candidatePlayer));
        }

    return outVec;
};

bool CCombat::IsGameOver() const
{
    int deadCount = 0;
    int maxCount = 0;
    for (auto& pair : mPlayerData)
        {
            maxCount += 1;
            auto& data = pair.second;
            if (data->mPlayer.get().IsEliminated())
                {
                    deadCount += 1;
                }
        }
    // check whether the number of remaining players is 1 or less
    return (maxCount - deadCount) <= 1;
}
