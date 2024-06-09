#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

// forward declaration to avoid circular reference
class CICard;  // NOLINT
class CIDeck;  // NOLINT
class CPlayerField;
class CHand;
class CCombat;
class CProfessor;
class CFieldCard;
class CIAttackable;
class CManagementCard;
struct SAttributeMap;

enum class ETemplateAttritbute;
enum class ECardType;

enum class ETemplateAttribute
{
    EType,
    EName,
    EPower,
    EResilience
};

enum class ECardType
{
    EStudent,
    EPlagiarismHearing,
    ECourseAccreditation,
    EFeedbackForum,
    EIndustrialPlacement,
    EPassLeader,
    EResearchFunding,
    EMitigatingCircumstances,
    EEasyTarget,
    ESerialOffender,
    EGraduateStudent
};
using CardPtr = std::unique_ptr<CICard>;
using FieldCardPtr = std::unique_ptr<CFieldCard>;

using DeckPtr = std::unique_ptr<CIDeck>;
using HandPtr = std::unique_ptr<CHand>;

using PlayerPtr = std::unique_ptr<CProfessor>;
using PlayerFieldPtr = std::unique_ptr<CPlayerField>;

using CardRef = std::reference_wrapper<CICard>;
using DeckRef = std::reference_wrapper<CIDeck>;
using PlayerRef = std::reference_wrapper<CProfessor>;
using CombatRef = std::reference_wrapper<CCombat>;
using PlayerRefVector = std::vector<PlayerRef>;
using AttackableRef = std::reference_wrapper<CIAttackable>;
using ManagementCardRef = std::reference_wrapper<CManagementCard>;

using PlayerFieldRef = std::reference_wrapper<CPlayerField>;

using CardOwnerVector = std::vector<CardPtr>;
using DeckOwnerVector = std::vector<DeckPtr>;

using CardStack = std::vector<CardRef>;

using FieldCardRef = std::reference_wrapper<CFieldCard>;
using FieldCardArray = std::vector<FieldCardRef>;

using AttributeMap = std::map<ETemplateAttribute, std::string>;
