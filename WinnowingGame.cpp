#include "WinnowingGame.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "CCardFactory.h"
#include "CFieldCard.h"
#include "CHand.h"
#include "Config.h"
#include "Utils.h"

CWinnowingGame::CWinnowingGame(std::string seedpath)
{
    int seed = ReadSeed(seedpath);
    srand(seed);
    // pass a reference to the game to the combat
    mCurrentCombat = std::make_unique<CCombat>(*this);
    std::vector<std::pair<std::string, std::string>> playerFiles{
        {"plagiarist", "plagiarist.txt"},
        {"piffle paper", "piffle-paper.txt"},
        {"pointless", "pointless.txt"},
        {"perdition", "perdition.txt"}};

    // create the players and add them to the game
    for (const auto& playerFileData : playerFiles)
    {
        auto player =
            GetProfessorFromPath(playerFileData.first, playerFileData.second);

        // add the new player to the current list
        mCurrentCombat->AddPlayer(*player);
        this->mCurrentPlayers.push_back(std::move(player));
    }
}

// generates a unique id each time called
int CWinnowingGame::GetUniqueId()
{
    return mNextId++;
}

// begins the game, blocks until the game is over
void CWinnowingGame::StartGame()
{
    std::cout << "Welcome to U-Can’t. Let the winnowing begin..." << std::endl;

    this->DoFirstDraw();

    // iterate ROUND_COUNT times, or exit early if the game is over
    for (size_t i = 0; i <= mMaxRounds; i++)
    {
        mRoundCount = i;
        // do round
        this->PerformRound();
        if (IsGameOver())
        {
            ProclaimWinner(this->mWinners.at(0));
            return;
        }
    }
    std::cout << "Game over" << std::endl;
    // here we output a natural end to the game
    // check all alive players, the one with the highest
    // prestige wins
    this->AnnounceNaturalWinner();
}

// draw the first card for each player and handle output
void CWinnowingGame::DoFirstDraw()
{
    for (const auto& player : mCurrentPlayers)
    {
        auto card = mCurrentCombat->DrawCard(*player, false);
        std::cout << player->GetName() << " starts with "
                  << card.value().get().GetName() << std::endl;
    }
}

// performs all of the actions for a single round
void CWinnowingGame::PerformRound()
{
    std::cout << "Round " << (mRoundCount) << std::endl;

    for (auto& player : mCurrentPlayers)
    {
        // continue if the current player has been eliminated
        if (player->IsEliminated())
        {
            continue;
        }
        DrawCardAndPrint(*player);
        // at this point, the player has a max of two cards in hand
        /// but they may have none
        int handSize = mCurrentCombat->GetHandSize(std::ref(*player));
        if (handSize != 0)
        {
            auto card = this->SelectRandomCardAndPrint(*player);
            // now they will have one card

            card.get().Play(*mCurrentCombat);
        }
        else
        {
            std::cout << player->GetName() << " has no cards left to play "
                      << std::endl;
        }
        // check if this player was eliminated

        // check for game over, since playing a card could kill a player
        auto gameOver = CheckWinner();
        if (gameOver)
        {
            return;
        }

        // output the current player's board
        OutputCurrentBoard(std::ref(*player.get()));

        // false if the game is not over
        auto result = mCurrentCombat->PerformFieldAttacks(*player);

        // check for a winner again
        gameOver = CheckWinner();
        if (gameOver)
        {
            return;
        }
    }
}

void CWinnowingGame::AnnounceNaturalWinner()
{
    // It should not be possible for all players to be dead
    auto livingPlayers = this->GetLivingPlayers();

    if (livingPlayers.size() == 1)
    {
        ProclaimWinner(livingPlayers.back());
        return;
    }

    // we have multiple living players here
    int maxPrestige = -1;
    // this list will contain at least one player
    // if it contains multiple, they all have the same prestige
    PlayerRefVector drawers{};
    for (const auto& player : livingPlayers)
    {
        int thisPrestige = player.get().GetPrestige();
        if (thisPrestige > maxPrestige)
        {
            // remove all other entries
            drawers.clear();
            maxPrestige = thisPrestige;
        }

        if (thisPrestige == maxPrestige)
        {
            drawers.push_back(player);
        }
    }

    if (drawers.size() == 1)
    {
        this->ProclaimWinner(drawers.back());
    }
    else
    {
        this->ProclaimDraw(drawers);
    }
}

// only to check victory from combat
// checks if all but one player is dead
bool CWinnowingGame::CheckWinner()
{
    std::optional<PlayerRef> potentialWinner{};
    int aliveCount = 0;
    for (const auto& player : mCurrentPlayers)
    {
        if (!player->IsEliminated())
        {
            aliveCount++;
            potentialWinner.emplace(std::ref(*player));
        }
    }

    if (aliveCount > 1)
    {
        // return no winner
        potentialWinner.reset();
    }

    // we have a winner, set the correct values
    if (potentialWinner.has_value())
    {
        mWinners.push_back(potentialWinner.value());
        mGameOver = true;
    }

    return IsGameOver();
}

void CWinnowingGame::ProclaimWinner(PlayerRef winner)
{
    PlayerRefVector losers{};
    // assemble the list of losers
    for (const auto& player : this->mCurrentPlayers)
    {
        if (player->GetId() != winner.get().GetId())
        {
            losers.push_back(std::ref(*player));
        }
    }

    // output the winner's prestige first
    std::cout << winner.get().GetName() << "’s prestige amount is "
              << winner.get().GetPrestige() << std::endl;

    // then output the losers
    for (const auto& loser : losers)
    {
        std::cout << loser.get().GetName() << "’s prestige amount is "
                  << loser.get().GetPrestige() << std::endl;
    }

    // finally announce the winner
    std::cout << winner.get().GetName() << " wins." << std::endl;
}

// this only handles a draw between two players
void CWinnowingGame::ProclaimDraw(PlayerRefVector players)
{
    for (auto& player : mCurrentPlayers)
    {
        std::cout << player->GetName() << "’s prestige amount is "
                  << player->GetPrestige() << std::endl;
    }

    std::string delimiter = " and ";

    std::stringstream ss;
    for (int i = 0; i < players.size(); i++)
    {
        ss << players[i].get().GetName();
        if (i != players.size() - 1)
        {
            ss << delimiter;
        }
    }
    std::string result = ss.str();
    std::cout << result << " have the same prestige" << std::endl;
    std::cout << "The game ends with a draw." << std::endl;
}

// gets a list of living players
PlayerRefVector CWinnowingGame::GetLivingPlayers() const
{
    PlayerRefVector livingPlayers{};
    for (const auto& player : this->mCurrentPlayers)
    {
        if (!player->IsEliminated())
        {
            livingPlayers.push_back(std::ref(*player));
        }
    }

    return livingPlayers;
}

// outputs the board for a single player
void CWinnowingGame::OutputCurrentBoard(PlayerRef player)
{
    std::cout << "Cards on table: ";

    std::vector<std::string> cardInfoArray;

    const auto& playerData = mCurrentCombat->GetPlayerCombatData(player);
    for (const auto& card : playerData.mField->GetCards())
    {
        std::stringstream data{};
        data << card.get().GetName() << "("
             << card.get().GetResilience(std::ref(*mCurrentCombat)) << ")";

        cardInfoArray.push_back(data.str());
    }

    std::string joined{};
    for (size_t i = 0; i < cardInfoArray.size(); i++)
    {
        if (i > 0)
        {
            joined += ", ";
        }
        joined += cardInfoArray.at(i);
    }
    std::cout << joined << std::endl;
}

void CWinnowingGame::EliminatePlayer(PlayerRef player)
{
    // the player must be dead already at this point
    std::cout << player.get().GetName() << " has no prestige and is sacked!"
              << std::endl;
    // remove the player from the field data
}
void CWinnowingGame::DrawCardAndPrint(CProfessor& player)
{
    mCurrentCombat->DrawCard(player);
}

CardRef CWinnowingGame::SelectRandomCardAndPrint(CProfessor& player)
{
    int handSize = mCurrentCombat->GetHandSize(std::ref(player));
    int playedCardIndex = Random(handSize);
    auto card = mCurrentCombat->RemoveCardFromPlayer(player, playedCardIndex);
    std::cout << player.GetName() << " plays " << card.get().GetName()
              << std::endl;
    return card;
}

// factory ish method
PlayerPtr CWinnowingGame::GetProfessorFromPath(
    const std::string& professorName,
    const std::string& fileName)
{
    std::vector<std::string> playerCardsTemplate =
        CWinnowingGame::ReadProfessorFileLines(fileName);

    int newId{this->GetUniqueId()};

    auto newProfessor =
        std::make_unique<CProfessor>(CProfessor(newId, professorName));
    DeckRef newDeck =
        GetDeckFromTemplates(playerCardsTemplate, std::ref(*newProfessor));

    newProfessor->SetDeck(newDeck);

    return std::move(newProfessor);
}

std::vector<std::string> CWinnowingGame::ReadProfessorFileLines(
    const std::string& fileName)
{
    std::vector<std::string> lines{};
    std::ifstream inFile = openFile(fileName);

    std::string line;
    while (std::getline(inFile, line))
    {
        if (!line.empty())
        {
            lines.push_back(line);
        }
    }

    return lines;
}

DeckRef CWinnowingGame::GetDeckFromTemplates(
    const std::vector<std::string>& templates,
    PlayerRef owner)
{
    CardOwnerVector newCards = CCardFactory::GetCards(templates, owner);
    // these cards need moving to our ownership collection
    // but we leave it to the end of the function

    auto newDeck = std::make_unique<CDeck>();
    auto newDeckRef = std::ref(*newDeck);
    mCurrentDecks.push_back(std::move(newDeck));
    // add this deck to our list of decks

    for (const auto& card : newCards)
    {
        // create a reference wrapped version of the actual card
        // and add to our vector
        newDeckRef.get().AddCard(std::ref(*card));
    }
    // move the cards to the collection
    for (auto& card : newCards)
    {
        mCurrentCards.push_back(std::move(card));
    }

    return newDeckRef;
};

bool CWinnowingGame::IsGameOver() const
{
    return mGameOver;
};

PlayerRefVector CWinnowingGame::GetOtherPlayers(PlayerRef targetPlayer) const
{
    PlayerRefVector otherPlayers{};
    for (const auto& player : mCurrentPlayers)
    {
        auto passedPlayer = &(targetPlayer.get());
        auto otherPlayer = (player.get());

        if (passedPlayer != otherPlayer)
        {
            otherPlayers.push_back(std::ref(*passedPlayer));
        }
    }
    return otherPlayers;
};

int CWinnowingGame::ReadSeed(std::string filepath)
{
    std::ifstream inFile = openFile(filepath);
    std::string line;
    std::getline(inFile, line);

    inFile.close();

    return std::stoi(line);
};
