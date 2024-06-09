#pragma once
#include <optional>
#include <vector>

#include "CHand.h"
#include "CICard.h"
#include "CIDeck.h"
#include "CPlayerField.h"
#include "Types.h"
class CWinnowingGame;

struct SPlayerCombatData
{
    PlayerRef mPlayer;
    DeckRef mDeck;
    HandPtr mHand;
    PlayerFieldPtr mField;
};

class CCombat
{
  public:
    CCombat(CWinnowingGame& game);
    void AddPlayer(CProfessor& player);
    std::optional<CardRef> DrawCard(PlayerRef player, bool print = true);
    CardRef RemoveCardFromPlayer(CProfessor& professor, int index);
    bool PerformFieldAttacks(CProfessor& player);
    void AddToField(CProfessor& player, FieldCardRef card);
    SPlayerCombatData& GetPlayerCombatData(PlayerRef player) const;
    void Destroy(FieldCardRef card);
    AttackableRef SelectRandomEnemy(PlayerRef player);
    AttackableRef SelectRandomTarget();
    std::optional<AttackableRef> SelectFieldCardTarget(CardRef card);
    std::vector<AttackableRef> SelectAllEnemies(CardRef card);
    std::optional<FieldCardRef> SelectRandomFriendlyCard(CardRef card);
    PlayerRef SelectRandomEnemyPlayer(CardRef card);
    PlayerRefVector GetOtherLivingPlayers(PlayerRef player) const;

    int GetFieldSize(PlayerRef player) const;
    int GetHandSize(PlayerRef player) const;

    void RemoveFromPlayOrder(CardRef card);
    bool IsGameOver() const;
    void OnPlayerDeath(PlayerRef player);

    // void PlayCard(int playerId, CardRef card);

  private:
    CWinnowingGame& mGameRef;
    std::vector<CardRef> mFieldPlayedOrder;
    std::map<int, std::unique_ptr<SPlayerCombatData>> mPlayerData{};
};
