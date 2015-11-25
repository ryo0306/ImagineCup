#include "CreateAction.h"


// �S�̓I�Ɏd�g�݂͂��܂����Ă���

void CreateAction::Update()
{
  //  �}�E�X�̈ʒu���X�V
  mousePos = App::get().mousePosition();
  
  // �������u��defAngle��������
  if (App::get().isPushButton(Mouse::LEFT))
  {
    SetDefAngle();
  }

  if (App::get().isPressButton(Mouse::LEFT))
  {
    // 10�t���[���Ɉ��defAngle����������
    // �������Ă��邩�m�F����
    if (updateCount % 10 == 0)
    {
      SetDefAngle();
      updateCount = 0;
    }
    SetAngle();
    Acceleration();
    updateCount++;
  }
  else
  {
    // �}�E�X�������Ă��Ȃ�������
    // ����
    SlowDown();
  }


  // �X�s�[�h�̐���
  if (speed > MAX_SPEED)
  {
    speed = MAX_SPEED;
  }
  else if (speed < -MAX_SPEED)
  {
    speed = -MAX_SPEED;
  }

  textureAbgle += speed;
}



void CreateAction::Draw()
{
  drawFillBox(pos.x(), pos.y(), size.x(), size.y(), Color::yellow,textureAbgle,Vec2f(1,1),Vec2f(pos.x()+size.x()/2,pos.y()+size.y()/2));
}


//TODO:�֐���
//*���S�_�����ꂼ������
void CreateAction::SetAngle()
{
  angle = -atan2(pos.x() - mousePos.x(),
                 pos.y() - mousePos.y());
}


void CreateAction::SetDefAngle()
{
  defAngle = -atan2(pos.x() - mousePos.x(),
                 pos.y() - mousePos.y());
}

void CreateAction::Acceleration()
{
  if (defAngle < angle)
    speed += ACCELERATION;
  else if (defAngle > angle)
    speed -= ACCELERATION;
}

void CreateAction::SlowDown()
{
  if (speed > 0)
    speed -= SLOWDOWN;
  else if (speed < 0)
    speed += SLOWDOWN;

  if (abs(speed) < SLOWDOWN)
    speed = 0;
}