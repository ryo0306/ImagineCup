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

  void Acceleration();                // ��������

  void SlowDown();                    // ��������

  Vec2f pos = Vec2f(0,0);             // ��]����摜�̈ʒu(���S�_)
  Vec2f size = Vec2f(WINDOW_WIDTH,WINDOW_HEIGHT);
  Vec2f mousePos;                     // �}�E�X�̈ʒu
  float angle = 0;                    // �}�E�X�Ɗp�x
  float defAngle = 0;                 // �ŏ��Ƀ^�b�`�����p�x
  float speed = 0;                    // ��]���x
  float textureAbgle = 0;             // ��Texture�̊p�x
  int updateCount = 0;
};