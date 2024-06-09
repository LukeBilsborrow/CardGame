// CardGame.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <cstdlib>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <vector>

#include "CCombat.h"
#include "CDeck.h"
#include "CICard.h"
#include "Config.h"
#include "Types.h"
#include "Utils.h"
#include "WinnowingGame.h"

int main()
{
    {
        const std::string SEED_PATH = "seed.txt";
        auto game = CWinnowingGame(SEED_PATH);
        game.StartGame();
    }
    _CrtDumpMemoryLeaks();
}