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
//            �����X�^�[             //
//----------------------------------//
enum
{
  FAILURE,
  CUSTARD_PUDDING,
  CREAM_PUFF,
  STRAWBERRY�QSPONGE_CAKE,
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
  void PatternMake(Material material1_, Material material2_, Material material3_, int monster_); // ��񂾂���Ԃ���
  void SetMaterual();
  void ChangeColor(int i);
  void ChoicedMaterialCount();
  void FinalDecide();
  void Finish();
  void CreateCommand();

  //���邩�ǂ����킩��Ȃ�
  int CheckMakedMonster(){ return monster; }
  bool IsEnd(){ return isEnd; }

  ~CreateMonster()
  {
    pattern.clear();
  }
private:
  
  Material material[MATERIAL_NUM];                 // �I���ł���f��
  Vec2f mousePos;                                  // �}�E�X�̈ʒu
  int selectMaterialNum;                           // �I������Ă���f�ނ̐�
  int monster;                                     // �������ʂ̃����X�^�[
  bool isEnd;                                      // �I��������ǂ���
  bool nowDecide;                                  // �ŏI�m�F���ǂ���
  Color color[MATERIAL_NUM];                       // �{�b�N�X�̐F
  Material choiceMaterial[SELECT_MATERIAL_NUM];    // ����I�΂ꂽ�f��
  std::vector<CreateCombination> pattern;          // ���ʂ̃p�^�[��
  Font font = Font("res/meiryo.ttc");              
};