#pragma once
#include <fstream>

#include "CCombat.h"
#include "CProfessor.h"
#include "Types.h"

struct SPlayerCombatData;
class CWinnowingGame
{
  public:
    explicit CWinnowingGame(std::string seedpath);
    SPlayerCombatData& CreatePlayerCombatData(CProfessor& player);
    void StartGame();
    void DoFirstDraw();
    PlayerPtr GetProfessorFromPath(
        const std::string& professorName,
        const std::string& fileName);

    static std::vector<std::string> ReadProfessorFileLines(
        const std::string& fileName);
    void PerformRound();
    void PerformProfessorTurn();
    int GetUniqueId();
    void DrawCardAndPrint(CProfessor& player);
    void PerformFieldAttacks();
    void OutputCurrentBoard(PlayerRef player);
    SPlayerCombatData& GetPlayerCombatData(CProfessor& player);
    DeckRef GetDeckFromTemplates(
        const std::vector<std::string>& templates,
        PlayerRef owner);
    CardRef SelectRandomCardAndPrint(CProfessor& player);
    bool CheckWinner();

    void EliminatePlayer(PlayerRef player);

    // called when the game ends via round limit
    void AnnounceNaturalWinner();
    // this can only happen via round limit
    void ProclaimDraw(PlayerRefVector players);
    // called when only one player remains
    void ProclaimWinner(PlayerRef winner);
    bool IsGameOver() const;
    // gets other players not equal to the given player
    PlayerRefVector GetOtherPlayers(PlayerRef player) const;

    PlayerRefVector GetLivingPlayers() const;
    int ReadSeed(std::string filepath);

  private:
    CardOwnerVector mCurrentCards;
    DeckOwnerVector mCurrentDecks;

    std::unique_ptr<CCombat> mCurrentCombat;
    std::vector<PlayerPtr> mCurrentPlayers;
    PlayerRefVector mWinners;
    const int mMaxRounds{30};
    // tracks whether the game is over
    bool mGameOver{false};
    int mRoundCount{0};
    int mNextId{1};
};
