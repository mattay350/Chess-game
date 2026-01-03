#include <iostream>
#include "chess.hpp"

using namespace std;
using namespace Chess;


int main(){
  Board game;
  Render rnd;
  bool is_moved = false;
  string input_cmd;
  //ゲーム板の初期化
  game.Init();

  ///ゲーム設定選択
  //  game.SSelect();
  
  //ゲームスタート
  for(;;)
    {
      if(game.Get_plyaer_turn()){
	//Go Player Turn
	rnd.Rendering(Render::RenderCmd::MY_TURN,game);
        for (;;) {
          cin >> input_cmd;
          if (game.Move(input_cmd, game.Get_plyaer_turn())) break;
	  else cout << "<入力が不正です" << endl;	 
	}
	if (game.VEval_GoFirst()) {
	  rnd.Rendering(Render::RenderCmd::WIN, game);
	  break;
	}

      }else{
	//Go ENEMY Turn
	is_moved =false;
	rnd.Rendering(Render::RenderCmd::ENEMY_TURN,game);
	for(;;) {
	  cin >> input_cmd;
          if (game.Move(input_cmd, game.Get_plyaer_turn())) break;
	  else cout << "<入力が不正です" << endl;	  
	}
	if (game.VEval_GoSecond()) {
	  rnd.Rendering(Render::RenderCmd::LOSE, game);
	  break;
	}
      }
    }
  
  cin.get();  
  return 0;
}

