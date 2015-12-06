#pragma once
#include "ScreenMake.h"
#include "Collision.h"
#include <vector>,
#include <list>
#include <string>

enum
{
  MATERIAL_UI_POS_X = -WINDOW_WIDTH/2,
  MATERIAL_UI_POS_Y = -WINDOW_HEIGHT/2,
  SELECT_MATERIAL_NUM = 3,
  MATERIAL_NUM = 12,
};

//---------------------------------//
//             UI                  //
//---------------------------------//
enum
{
  MATERIAL_UIBOX_SIZEX = 130,
  MATERIAL_UIBOX_SIZEY = 50,
  CREATE_COMMAND_UIBOX_POSX = -100,
  CREATE_COMMAND_UIBOX_POSY = 100,
  CREATE_COMMAND_UIBOX_SIZEX = 200,
  CREATE_COMMAND_UIBOX_SIZEY = 100,
  FINAL_DECIDE_UIBOX_POSX = -200,
  FINAL_DECIDE_UIBOX_POSY = -200,
  FINAL_DECIDE_UIBOX_SIZEX = 400,
  FINAL_DECIDE_UIBOX_SIZEY = 400,
  YES_UIBOX_POSX = -175,
  YES_UIBOX_POSY = -100,
  YES_UIBOX_SIZEX = 150,
  YES_UIBOX_SIZEY = 100,
  NO_UIBOX_POSX = 25,
  NO_UIBOX_POSY = -100,
  NO_UIBOX_SIZEX = 150,
  NO_UIBOX_SIZEY = 100,
};

//----------------------------------//
//            モンスター             //
//----------------------------------//
enum
{
  FAILURE,
  CUSTARD_PUDDING,
  CREAM_PUFF,
  STRAWBERRY＿SPONGE_CAKE,
  JELLY,
  BAVARIAN_CREAM,
  CHOCOLATE,
  BISCUIT,
  CARAMEL,
  ICECREAM,
  MANJU,
};

struct Material
{
  std::string name;
  int id;
  bool select;
  bool active;
};

struct CreateCombination
{
  Material material[SELECT_MATERIAL_NUM];
  int monster;
  CreateCombination(Material material1_, Material material2_, Material material3_, int monster_)
  {
    material[0]= material1_;
    material[1] = material2_;
    material[2] = material3_;
    monster = monster_;
  } 
};




class CreateMonster
{
public:
  
  void SetUp();
  void Update();
  void Draw();
  void Select();
  void SelectMaterial(int i);
  bool Search(CreateCombination createcombination_);
  void PatternMake(Material material1_, Material material2_, Material material3_, int monster_); // 一回だけよぶこと
  void SetMaterual();
  void ChangeColor(int i);
  void ChoicedMaterialCount();
  void FinalDecide();
  void Finish();
  void CreateCommand();

  //いるかどうかわからない
  int CheckMakedMonster(){ return monster; }
  bool IsEnd(){ return isEnd; }

  ~CreateMonster()
  {
    pattern.clear();
  }
private:
  
  Material material[MATERIAL_NUM];                 // 選択できる素材
  Vec2f mousePos;                                  // マウスの位置
  int selectMaterialNum;                           // 選択されている素材の数
  int monster;                                     // 合成結果のモンスター
  bool isEnd;                                      // 終わったかどうか
  bool nowDecide;                                  // 最終確認かどうか
  Color color[MATERIAL_NUM];                       // ボックスの色
  Material choiceMaterial[SELECT_MATERIAL_NUM];    // 今回選ばれた素材
  std::vector<CreateCombination> pattern;          // 結果のパターン
  Font font = Font("res/meiryo.ttc");              
};