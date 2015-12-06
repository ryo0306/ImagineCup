#include "CreateMonster.h"



void CreateMonster::SetUp()
{

  nowDecide = false;
  selectMaterialNum = 0;
  monster = 0;
  for (int i = 0; i < MATERIAL_NUM; i++)
  {
    material[i].id = i;
    color[i] = Color::white;
    material[i].select = false;
    material[i].active = true;
  }
  material[9].active = false;
  material[10].active = false;
  material[11].active = false;

  for (int i = 0; i < SELECT_MATERIAL_NUM; i++)
  {
    choiceMaterial[i].name = "��";
    choiceMaterial[i].id = NULL;
  }

  material[0].name = "����";
  material[1].name = "����";
  material[2].name = "��";
  material[3].name = "������";
  material[4].name = "�o�^�[";
  material[5].name = "�X�|���W";
  material[6].name = "���N���[��";
  material[7].name = "�ʕ�";
  material[8].name = "�[���`��";
  material[9].name = "�J�J�I";
  material[10].name = "����";
  material[11].name = "����";


  
  //PatternMake����ۂɂ�material�͏��������ɂȂ�悤�ɂ��Ă�������
  PatternMake(material[0], material[1], material[2], CUSTARD_PUDDING);
  PatternMake(material[2], material[3], material[4], CREAM_PUFF);
  PatternMake(material[5], material[6], material[7], STRAWBERRY�QSPONGE_CAKE);
  PatternMake(material[1], material[7], material[8], JELLY);
  PatternMake(material[1], material[2], material[8], BAVARIAN_CREAM);
  PatternMake(material[0], material[1], material[9], CHOCOLATE);
  PatternMake(material[0], material[3], material[4], BISCUIT);
  PatternMake(material[1], material[6], material[10], CARAMEL);
  PatternMake(material[1], material[4], material[6], ICECREAM);
  PatternMake(material[2], material[3], material[11], MANJU);

  
}


void CreateMonster::Update()
{
  mousePos = App::get().mousePosition();

    Select();
    CreateCommand();
    FinalDecide();
  
}

void CreateMonster::Draw()
{
  font.size(25);
  for (int i = 0; i < MATERIAL_NUM; i++)
    { 
      int x = int (i % 3);
      int y = int (i / 3);
      drawFillBox(x * 180 + MATERIAL_UI_POS_X, y * 100 + MATERIAL_UI_POS_Y, MATERIAL_UIBOX_SIZEX, MATERIAL_UIBOX_SIZEY, color[i]);
      drawBox(x * 180 + MATERIAL_UI_POS_X, y * 100 + MATERIAL_UI_POS_Y, MATERIAL_UIBOX_SIZEX, MATERIAL_UIBOX_SIZEY, 5, Color::red);
      font.draw(material[i].name, Vec2f(x * 200 - WINDOW_WIDTH / 2, y * 100 - WINDOW_HEIGHT / 2), Color::red);
      if (!material[i].active)
      {
        drawFillBox(x * 180 + MATERIAL_UI_POS_X, y * 100 + MATERIAL_UI_POS_Y, MATERIAL_UIBOX_SIZEX, MATERIAL_UIBOX_SIZEY, Color(0, 0, 0, 0.6f));
      }
    }

  font.size(50);
  drawFillBox(CREATE_COMMAND_UIBOX_POSX, CREATE_COMMAND_UIBOX_POSY,
              CREATE_COMMAND_UIBOX_SIZEX, CREATE_COMMAND_UIBOX_SIZEY,
              Color::yellow);
  font.draw("����", Vec2f(CREATE_COMMAND_UIBOX_POSX + 50, CREATE_COMMAND_UIBOX_POSY + 25), Color::red);

  font.size(35);
  if (nowDecide)
  {
    drawFillBox(FINAL_DECIDE_UIBOX_POSX, FINAL_DECIDE_UIBOX_POSY,
                FINAL_DECIDE_UIBOX_SIZEX, FINAL_DECIDE_UIBOX_SIZEY,
                Color::black);
    drawBox(FINAL_DECIDE_UIBOX_POSX, FINAL_DECIDE_UIBOX_POSY,
            FINAL_DECIDE_UIBOX_SIZEX, FINAL_DECIDE_UIBOX_SIZEY,
            5, Color::white);
    drawFillBox(YES_UIBOX_POSX, YES_UIBOX_POSY,
                YES_UIBOX_SIZEX, YES_UIBOX_SIZEY, Color::red);
    drawFillBox(NO_UIBOX_POSX, NO_UIBOX_POSY,
                NO_UIBOX_SIZEX, NO_UIBOX_SIZEY, Color::blue);
    font.draw("�{���ɍ������܂����H", Vec2f(-175, 100), Color::white);
    font.draw("�͂�", Vec2f(YES_UIBOX_POSX + 25, YES_UIBOX_POSY+25), Color::white);
    font.draw("������", Vec2f(NO_UIBOX_POSX + 25, NO_UIBOX_POSY+25), Color::white);
  }
  //DEBUGDRAW:
  font.draw("����: "+std::to_string(monster), Vec2f(-100, 250), Color::white);
}

//---------------------------------------------//
//              �I�ԏ����i�S�ʁj                 //
//---------------------------------------------//

void CreateMonster::Select()
{

  if (!nowDecide)
  {
    for (int i = 0; i < MATERIAL_NUM; i++)
    {
      int x = int(i % 3);
      int y = int(i / 3);

      if (Collision(Vec2f(x * 180 + MATERIAL_UI_POS_X, y * 100 + MATERIAL_UI_POS_Y), Vec2f(MATERIAL_UIBOX_SIZEX, MATERIAL_UIBOX_SIZEY), mousePos, Vec2f(1, 1)))
      {
        SelectMaterial(i);
      }
      ChangeColor(i);
    }
    ChoicedMaterialCount();
  }
}

//---------------------------------------------//
//              �f�ނ�I�ԏ���                  //
//---------------------------------------------//

// �V�[�N���b�g�������������߃l�X�g�͐[��
void CreateMonster::SelectMaterial(int i)
{
  if (App::get().isPushButton(Mouse::LEFT))
  {
    if (material[i].active)
    {
      if (!material[i].select)
      {
        if (selectMaterialNum < 3)
          material[i].select = true;
      }
      else
      {
        material[i].select = false;
      }
    }
  }
}


//---------------------------------------------//
//              �f�ނ��Z�b�g����                 //
//---------------------------------------------//
void CreateMonster::SetMaterual()
{
  int tmp = 0;
  for (int i = 0; i < MATERIAL_NUM; i++)
  {
    if (material[i].select)
    {
      choiceMaterial[tmp] = material[i];
      tmp++;
    }
  }

  //  �I������Ă���f�ނ��O�ȉ����
  //  ���Ǝc���NULL����������
  while (tmp<3)
  {
    choiceMaterial[tmp].name = "��";
    choiceMaterial[tmp].id = NULL;
    tmp++;
  }

}


//---------------------------------------------//
//                ��������                      //
//---------------------------------------------//
bool CreateMonster::Search(CreateCombination createcombination_)
{
    if (choiceMaterial[0].id == createcombination_.material[0].id
        &&choiceMaterial[1].id == createcombination_.material[1].id
        &&choiceMaterial[2].id == createcombination_.material[2].id)
    {
      monster = createcombination_.monster;
      return true;
    }
  
    return false;
}


//---------------------------------------------//
//              �F��ς��鏈��                  //
//---------------------------------------------//
void CreateMonster::ChangeColor(int i)
{
  if (material[i].select)
  {
    color[i] = Color::yellow;
  }
  else
  {
    color[i] = Color::white;
  }
}


//---------------------------------------------//
//             �I�񂾑f�ނ𐔂���               //
//---------------------------------------------//
void CreateMonster::ChoicedMaterialCount()
{
  selectMaterialNum = 0;
  for (int i = 0; i < MATERIAL_NUM; i++)
  {
    if (material[i].select)
      selectMaterialNum++;
  }
}

//---------------------------------------------//
//           �����J�n�̃{�^���̂����蔻��        //
//---------------------------------------------//
void CreateMonster::CreateCommand()
{
  if (Collision(Vec2f(CREATE_COMMAND_UIBOX_POSX, CREATE_COMMAND_UIBOX_POSY),
                Vec2f(CREATE_COMMAND_UIBOX_SIZEX, CREATE_COMMAND_UIBOX_SIZEY),
                mousePos, Vec2f(1, 1)))
  {
    if (App::get().isPushButton(Mouse::LEFT))
    {
      nowDecide = true;
    }
  }
}

//---------------------------------------------//
//           �@�@�����p�^�[����ǉ�              //
//---------------------------------------------//
void CreateMonster::PatternMake(Material material1_, Material material2_, Material material3_, int monster_)
{
  pattern.push_back(CreateCombination(material1_, material2_, material3_, monster_));
}

//---------------------------------------------//
//                   �ŏI�m�F                   //
//---------------------------------------------//
void CreateMonster::FinalDecide()
{
  if (nowDecide)
  {
    if (Collision(Vec2f(YES_UIBOX_POSX, YES_UIBOX_POSY),
      Vec2f(YES_UIBOX_SIZEX, YES_UIBOX_SIZEY),
      mousePos, Vec2f(1, 1)))
    {
      if (App::get().isPushButton(Mouse::LEFT))
      {
        Finish();
      }
    }
    if (Collision(Vec2f(NO_UIBOX_POSX, NO_UIBOX_POSY),
      Vec2f(NO_UIBOX_SIZEX, NO_UIBOX_SIZEY),
      mousePos, Vec2f(1, 1)))
    {
      if (App::get().isPushButton(Mouse::LEFT))
      {
        nowDecide = false;
      }
    }
  }
}



//---------------------------------------------//
//                   �ŏI����                   //
//---------------------------------------------//
void CreateMonster::Finish()
{
  SetMaterual();
  for (auto& iterator : pattern)
  {
    if (Search(iterator))
    {
      isEnd = true;
      break;
    }
    monster = 0;
  }

  nowDecide = false;
}