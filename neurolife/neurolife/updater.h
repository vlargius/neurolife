#pragma once


#include "render.h"
#include "world.h"
#include "server.h"
#include "client.h"

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
  World &world;
  Render *render;

  RC type;

  int stepSize;
};
