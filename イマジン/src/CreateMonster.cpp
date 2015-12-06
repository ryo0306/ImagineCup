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
    choiceMaterial[i].name = "空";
    choiceMaterial[i].id = NULL;
  }

  material[0].name = "牛乳";
  material[1].name = "砂糖";
  material[2].name = "卵";
  material[3].name = "小麦粉";
  material[4].name = "バター";
  material[5].name = "スポンジ";
  material[6].name = "生クリーム";
  material[7].name = "果物";
  material[8].name = "ゼラチン";
  material[9].name = "カカオ";
  material[10].name = "水飴";
  material[11].name = "あんこ";


  
  //PatternMakeする際にはmaterialは小さい順になるようにしてください
  PatternMake(material[0], material[1], material[2], CUSTARD_PUDDING);
  PatternMake(material[2], material[3], material[4], CREAM_PUFF);
  PatternMake(material[5], material[6], material[7], STRAWBERRY＿SPONGE_CAKE);
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
  font.draw("合成", Vec2f(CREATE_COMMAND_UIBOX_POSX + 50, CREATE_COMMAND_UIBOX_POSY + 25), Color::red);

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
    font.draw("本当に合成しますか？", Vec2f(-175, 100), Color::white);
    font.draw("はい", Vec2f(YES_UIBOX_POSX + 25, YES_UIBOX_POSY+25), Color::white);
    font.draw("いいえ", Vec2f(NO_UIBOX_POSX + 25, NO_UIBOX_POSY+25), Color::white);
  }
  //DEBUGDRAW:
  font.draw("結果: "+std::to_string(monster), Vec2f(-100, 250), Color::white);
}

//---------------------------------------------//
//              選ぶ処理（全般）                 //
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
//              素材を選ぶ処理                  //
//---------------------------------------------//

// シークレットを実装したためネストは深め
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
//              素材をセットする                 //
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

  //  選択されている素材が三つ以下状態
  //  だと残りはNULLが代入される
  while (tmp<3)
  {
    choiceMaterial[tmp].name = "空";
    choiceMaterial[tmp].id = NULL;
    tmp++;
  }

}


//---------------------------------------------//
//                検索処理                      //
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
//              色を変える処理                  //
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
//             選んだ素材を数える               //
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
//           合成開始のボタンのあたり判定        //
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
//           　　合成パターンを追加              //
//---------------------------------------------//
void CreateMonster::PatternMake(Material material1_, Material material2_, Material material3_, int monster_)
{
  pattern.push_back(CreateCombination(material1_, material2_, material3_, monster_));
}

//---------------------------------------------//
//                   最終確認                   //
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
//                   最終処理                   //
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