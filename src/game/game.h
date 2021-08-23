/**
 * @file game.h
 * @author Spencer Elliott (spencer@sharpthinking.ca)
 * @brief Exposes a platform-agnostic API for executing game code.
 * @version 0.1
 * @date 2021-08-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __GAME_GAME_H__
#define __GAME_GAME_H__

#include <stdbool.h>
#include "../platform/platform.h"

class Game {
    public:
        Game();
        void Init(void);
        void Update(void);
        void Draw(void);
        void Cleanup(void);
        void SetPlatform(Platform*);

        bool IsRunning(void);
        
    private:
        void StartRunning();
        void StopRunning();

        Platform *platform;
        bool running;
};

#endif