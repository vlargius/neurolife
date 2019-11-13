#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#include "irender.h"

class GuiRender : public IRender {
public:
    struct CreateConf {
       IntRect outBox = {640, 480};
    };

    GuiRender(const CreateConf& conf);

    void render(const World& world) override;

private:
    IntRect windowBox;

    SDL_Window *SdlWindow;
	SDL_Renderer *SdlRender;
};