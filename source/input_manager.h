#include <SDL2/SDL.h>

struct InputState {
    bool quit;
};

void do_input(InputState& state) {
    SDL_Event sevent;
    while (SDL_PollEvent(&sevent)) {
        switch (sevent.type) {
            case SDL_KEYDOWN:
            {
                if (sevent.key.keysym.sym == SDLK_ESCAPE)
                state.quit = true;
                break;
            }
            case SDL_QUIT:
            {
                state.quit = true;
                break;
            }
        }
    }
}