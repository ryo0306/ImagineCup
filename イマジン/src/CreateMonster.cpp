#include "CreateMonster.h"


void CreateMonster::SetUp()
{
  str[0] = "�J�J�I";
  str[1] = "�X�|���W";
  str[2] = "�o�j��";
  str[3] = "����";
  str[4] = "�C�`�S";
  str[5] = "�A�C�X";
  str[6] = "�`�[�Y";
  str[7] = "������";
  str[8] = "������";
  str[9] = "������";
  str[10] = "������";
  str[11] = "������";
  for (int i = 0; i < SELECT_MATERIAL_NUM; i++)
  {
    material[i] = "��";
  }
  PatternMake("�J�J�I", "�X�|���W", "�`���R�P�[�L");
  PatternMake("�C�`�S", "�X�|���W", "�C�`�S�P�[�L");
  
}


void CreateMonster::Draw()
{
  font.size(30);

  // �I�������f��
  for (int i = 0; i < SELECT_MATERIAL_NUM; i++)
  {
    drawFillBox(i * 200-180, 100, UIBOX_WIDTH, UIBOX_HEIGHT, Color::white);
    drawBox(i * 200 - 180, 100, UIBOX_WIDTH, UIBOX_HEIGHT, 5, frameColor[i]);
    font.draw(material[i], Vec2f(i * 200 - 180, 100), Color::red);
  }

  // ����
  drawFillBox(-75, 300, UIBOX_WIDTH, UIBOX_HEIGHT, Color::yellow);
  font.draw(monster, Vec2f(-75, 300), Color::red);

  // �����ł���f��
  for (int i = 0; i < 12; i++)
  { 
    int x = int (i % 3);
    int y = int (i / 3);
    drawFillBox(x * 180 - WINDOW_WIDTH / 2, y * 100 - WINDOW_HEIGHT / 2, UIBOX_WIDTH, UIBOX_HEIGHT, color[i]);
    font.draw(str[i], Vec2f(x * 200 - WINDOW_WIDTH / 2, y * 100 - WINDOW_HEIGHT / 2), Color::red);
  }

}


void CreateMonster::Update()
{
  // �}�E�X�̈ʒu
  mousePos = App::get().mousePosition();

  // 
  Select();
  SetMaterial();
  for (auto& p : pattern)
  {
    if (Search(p.material1, p.material2, p.monster))
      break;
  }
}

//TODO:�l�X�g���[���̂ŉ��ǂ̗]�n����
void CreateMonster::Select()
{
  for (int i = 0; i < SELECT_MATERIAL_NUM; i++)
  {
    if (Collision(Vec2f(i * 200 - 180, 100), Vec2f(UIBOX_WIDTH, UIBOX_HEIGHT), mousePos, Vec2f(1, 1)))
    {
      if (App::get().isPushButton(Mouse::LEFT))
      {
        if (i == 0)
        {
          frameColor[0] = Color::yellow;
          frameColor[1] = Color::white;
          selectedFrame = 0;
        }
        if (i == 1)
        {
          frameColor[0] = Color::white;
          frameColor[1] = Color::yellow;
          selectedFrame = 1;
        }
      }
    }
  }
}

// �I�������g�ɑf�ނ��Z�b�g
void CreateMonster::SetMaterial()
{
  for (int i = 0; i < 12; i++)
  {
    color[i] = Color::white;
    int x = int(i % 3);
    int y = int(i / 3);

    if (Collision(Vec2f(x * 180 - WINDOW_WIDTH / 2, y * 100 - WINDOW_HEIGHT / 2), Vec2f(UIBOX_WIDTH, UIBOX_HEIGHT),
      mousePos, Vec2f(1, 1)))
    {
      color[i] = Color::yellow;
      if (App::get().isPressButton(Mouse::LEFT))
      {
        material[selectedFrame] = str[i];
      }
    }
  }
}


// SetUp�Œǉ����ꂽ�p�^�[��������
bool CreateMonster::Search(char* material1_, char* material2_, char* monster_)
{
  if (material[0] == material1_ && material[1] == material2_)
  {
    monster = monster_;
    return true;
  }
  monster = "���s";
  return false;
}


// �������Search()�̈������t�ɂ��Ă�����������������H
//LINE_65:if(Search(p.material2.,p.material2, p.monster))
//           break;
//�Ƃ������ɒǉ����ׂ��H
void CreateMonster::PatternMake(char* material1_, char* material2_, char* monster_)
{
  pattern.push_back(CreateCombination(material1_, material2_, monster_));
  pattern.push_back(CreateCombination(material2_, material1_, monster_));
}