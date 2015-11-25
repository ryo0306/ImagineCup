#pragma once
#include "ScreenMake.h"
#include <iostream>
#define MAX_SPEED 0.3
#define ACCELERATION 0.001
#define SLOWDOWN 0.005

class CreateAction
{
public:

  void Update();
  void Draw();
  void SetAngle();
  void SetDefAngle();
private:

  void Acceleration();                // 加速処理

  void SlowDown();                    // 減速処理

  Vec2f pos = Vec2f(0,0);             // 回転する画像の位置(中心点)
  Vec2f size = Vec2f(WINDOW_WIDTH,WINDOW_HEIGHT);
  Vec2f mousePos;                     // マウスの位置
  float angle = 0;                    // マウスと角度
  float defAngle = 0;                 // 最初にタッチした角度
  float speed = 0;                    // 回転速度
  float textureAbgle = 0;             // 回すTextureの角度
  int updateCount = 0;
};