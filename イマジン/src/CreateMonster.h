#pragma once
#include "ScreenMake.h"
#include "Collision.h"
#include <vector>
#include <list>
#define UIBOX_HEIGHT WINDOW_WIDTH/5 - 50
#define UIBOX_WIDTH WINDOW_WIDTH/3 -20

struct CreateCombination
{
  CreateCombination(char* material1_, char* material2_, char* monster_)
  {
    material1 = material1_;
    material2 = material2_;
    monster = monster_;
  }
  char* material1;
  char* material2;
  char* monster;    // ‰½Œ^‚É‚È‚é‚©‚í‚©‚ç‚È‚¢
};


class CreateMonster
{
public:
  
  void SetUp();
  void Update();
  void Draw();
  void Select();
  void SetMaterial();
  bool Search(char* material1_, char* material2_, char* monster_);
  void PatternMake(char* material1_, char* material2_, char* monster_); // ˆê‰ñ‚¾‚¯‚æ‚Ô‚±‚Æ

  ~CreateMonster()
  {
    pattern.clear();
  }
private:

  int selectedFrame = 0;
  char* str[12];
  Font font = Font("res/meiryo.ttc");
  Vec2f mousePos;
  Color color[12];
  Color frameColor[2];
  char* monster;
  char* material[2];
  std::vector<CreateCombination> pattern;

};