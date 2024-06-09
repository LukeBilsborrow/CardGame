#pragma once
#include <string>

#include "SCardAttributes.h"
#include "Types.h"

enum class ECardType;
class CProfessor;
class CCombat;

class CICard
{
  public:
    virtual ~CICard() = default;
    virtual ECardType GetType() const = 0;
    virtual std::string GetName() const = 0;
    virtual int GetPower(CombatRef combat) const = 0;
    virtual void Play(CombatRef combat) = 0;
    virtual PlayerRef GetOwner() const = 0;
    virtual std::string GetDisplay(CombatRef combat) const = 0;

    virtual void SetOwner(PlayerRef newOwner) = 0;
};