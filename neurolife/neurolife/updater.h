#pragma once

#include <stdio.h>

#include "render.h"
#include "world.h"
#include "server.h"
#include "client.h"

#ifdef CLI
#include <SDL_main.h>
#endif

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

  Server server;
  Client client;

protected:

	bool isActive;
	World &world;
	Render *render;

	RC type;
	int stepSize;

	void handleEvent();

#ifdef CLI
	//SDL_Event e;
#endif // CLI

};
