#pragma once
#include"lib/framework.hpp"
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 800
//DEBUG:envはどうするかわからないので
//      一時的にシングルトンで記述

class App
{
public:
  static AppEnv& get()
  {
    static AppEnv s_env(WINDOW_WIDTH, WINDOW_HEIGHT);
    return s_env;
  }
private:
  App(){}
};