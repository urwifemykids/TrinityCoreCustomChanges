#include "ScriptMgr.h"
#include "Player.h"
#include "Group.h"
#include "ObjectAccessor.h"

enum MiscCrossFactionPVE
{
    ZONE_ICECROWN_CITADEL = 4812,
    ICC_MAP_ID = 631,
    ZONE_TRIAL_OF_THE_CHAMPION = 4723,
    TOCHAMPION_MAP_ID = 650,
    ZONE_TRIAL_OF_THE_CRUSADER = 4722,
    TOCRUSADER_MAP_ID = 649,
    ZONE_PIT_OF_SARON = 4813,
    POS_MAP_ID = 658,
    ZONE_HALLS_OF_REFLECTION = 4820,
    HOR_MAP_ID = 668,
    ZONE_FORGE_OF_SOULS = 4809,
    FOS_MAP_ID = 632,
    ZONE_HALLS_OF_STONE = 4264,
    HOS_MAP_ID = 599,
    ZONE_THE_NEXUS = 4265,
    TN_MAP_ID = 576,
    ZONE_WARSONG_GULCH = 3277,
    WSG_MAP_ID = 489,
    ZONE_ARATHI_BASIN = 3358,
    AB_MAP_ID = 529
};

void TemporaryFactionChange(Player* player)
{
    if (Group* group = player->GetGroup())
    {
        if (Player* leader = ObjectAccessor::FindPlayer(group->GetLeaderGUID()))
        {
            player->SetFaction(leader->GetFaction());
        }
    }
}

class CfPlayerScript : public PlayerScript
{
public:
    CfPlayerScript() : PlayerScript("CfPlayerScript") {}

    // Called when a player enters the world (logs in or teleports)
    void OnLogin(Player* player, bool firstLogin) override
    {
        switch (player->GetMapId())
        {
        case ICC_MAP_ID:
        case TOCHAMPION_MAP_ID:
        case TOCRUSADER_MAP_ID:
        case POS_MAP_ID:
        case HOR_MAP_ID:
        case FOS_MAP_ID:
        case HOS_MAP_ID:
        case TN_MAP_ID:
        case WSG_MAP_ID:
        case AB_MAP_ID:
            TemporaryFactionChange(player);
            break;
        }
    }

    // Called when a player changes zones
    void OnUpdateZone(Player* player, uint32 newZone, uint32 /*newArea*/) override
    {
        switch (newZone)
        {
        case ZONE_ICECROWN_CITADEL:
        case ZONE_TRIAL_OF_THE_CHAMPION:
        case ZONE_TRIAL_OF_THE_CRUSADER:
        case ZONE_PIT_OF_SARON:
        case ZONE_HALLS_OF_REFLECTION:
        case ZONE_FORGE_OF_SOULS:
        case ZONE_HALLS_OF_STONE:
        case ZONE_THE_NEXUS:
        case ZONE_WARSONG_GULCH:
        case ZONE_ARATHI_BASIN:
            TemporaryFactionChange(player);
            break;
        }
    }
};

void AddSC_cfpve()
{
    new CfPlayerScript();
}
