#include "CreateAction.h"


// 全体的に仕組みはごまかしている

void CreateAction::Update()
{
  //  マウスの位置を更新
  mousePos = App::get().mousePosition();
  
  // 押した瞬間defAngleを初期化
  if (App::get().isPushButton(Mouse::LEFT))
  {
    SetDefAngle();
  }

  if (App::get().isPressButton(Mouse::LEFT))
  {
    // 10フレームに一回defAngleを初期化し
    // 動かしているか確認する
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
    // マウスを押していなかったら
    // 減速
    SlowDown();
  }


  // スピードの制限
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


//TODO:関数化
//*中心点をそれぞれ入れる
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