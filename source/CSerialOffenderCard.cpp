#include "CSerialOffenderCard.h"

#include <iostream>

#include "CProfessor.h"
void CSerialOffenderCard::Activate(CombatRef combat)
{
    std::optional<AttackableRef> chosenTarget{};
    int remainingDamage = this->GetPower(combat);
    bool killedTarget = false;
    bool allTargetsDead = false;

    // choose a target and apply the remaining damage to them

    // we want to break this loop if there are no more field cards to hit
    // or if we have no remaining damage left
    // or if we did not kill our target
    do
        {
            chosenTarget = combat.get().SelectFieldCardTarget(std::ref(*this));
            if (!chosenTarget.has_value())
                {
                    allTargetsDead = true;
                    break;
                }

            // this prevents this text from being printed
            // in the first iteration
            if (killedTarget)
                {
                    std::cout << this->GetName() << " continues its rampage. ";
                }

            int targetStartResilience =
                chosenTarget.value().get().GetHealth(combat);

            chosenTarget.value().get().TakeDamage(
                std::ref(*this),
                std::ref(combat),
                remainingDamage);

            // break the loop if we did not kill
            killedTarget = chosenTarget.value().get().IsDead();
            remainingDamage =
                GetNextAttackPower(remainingDamage, targetStartResilience);
        }

    // check all of our continue conditions
    while (killedTarget && remainingDamage > 0);

    // if (remainingDamage > 0)
    //     {
    //         // attack the enemy directly with our remaining damage
    //         auto enemy =
    //         combat.get().SelectRandomEnemyPlayer(std::ref(*this));
    //         enemy.get().TakeDamage(std::ref(*this), combat, remainingDamage);
    //     }
}

int CSerialOffenderCard::GetNextAttackPower(int power, int enemyResilience)
    const
{
    // as stated in the brief
    // except we clamp it to 0 to ensure we dont deal with negative attack
    return std::max(0, power - enemyResilience);
}