#pragma once

#include "world.h"
#include "updater.h"
#include "render/char_render.h"
#include "render/gui_render.h"

class Manager final: public IUpdatable{
public:
    Manager(const World::CreateConf& w_conf, const Second& phys_dt, const CharRender::CreateConf& r_conf);
    Manager(const World::CreateConf& w_conf, const Second& phys_dt, const GuiRender::CreateConf& r_conf);
    ~Manager();

    void tick(Second dt) override;

private:
    Second physDt;
    World world;
    IRender *render;

    void tickPhys(Second dt);
    void tickInput();
};