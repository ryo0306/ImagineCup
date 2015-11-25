#include "Collision.h"


//Ÿè‚É’†S“_‚ğ‹‚ß‚éŠÖ”
//Collision‚Í‘¼‚Ìl‚ª‚Ç‚¤‚·‚é‚©‚É‚æ‚Á‚Ä•Ï‚¦‚é
bool Collision(Vec2f pos1_, Vec2f size1_, Vec2f pos2_, Vec2f size2_)
{
  return abs(pos1_.x() + size1_.x() / 2 - pos2_.x() + size2_.x() / 2) < size1_.x() / 2 + size2_.x() / 2 &&
    abs(pos1_.y() + size1_.y() / 2 - pos2_.y() + size2_.y() / 2) < size1_.y() / 2 + size2_.y() / 2;
}