#pragma once

#include <stdio.h>

#include "render.h"
#include "world.h"
#include "net_box.h"

#ifdef LINUX
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#endif // LINUX

#ifdef WINDOWS
#include <SDL.h>
#include <SDL_main.h>
#endif // WINDOWS



class Updater {
public:
  enum class RC
  {
	  NONE,
	  SERVER,
	  CLIENT
  };

  Updater(World &w, Render *render, RC type, const string& ip);

  void setStepSize(int size);

  void run();

  ServerBox server;
  ClientBox client;

protected:
  string ip;
	bool isActive;
	World &world;
	Render *render;

	RC type;
	int stepSize;
};
