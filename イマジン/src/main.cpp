#include "CreateAction.h"
#include "CreateMonster.h"

int main() {

  App::get();

  //CreateAction mazeru;
  CreateMonster gousei;

  gousei.SetUp();

  while (App::get().isOpen()) {
    App::get().begin();

    gousei.Update();
    gousei.Draw();

    //mazeru.Update();
    //mazeru.Draw();

    App::get().end();
  }
}
