#pragma once

#include "gui_context.h"
#include "render.h"

class GUIRender : public IRender {
   public:
    GUIRender(const World* w, int with, int height);

    void run() override;
    void flash() override;

   protected:
    GUIContext c;
    int actorSize = 20;

    void render(const Actor& a);
};