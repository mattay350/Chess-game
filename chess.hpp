#pragma once

#include <iostream>
#include <vector>

#define BOARD_SIZE 8
using namespace std;

namespace Chess {
  class Point{
  public:
    int x =0;
    int y =0;
    Point(int _x, int _y) {
      x = _x;
      y = _y;
    }
    bool operator== (const Point& pt1) const;

  };
  class Piece{
  public:
    enum Piece_num {
      //piece name
      NONE,
      KING,
      QUEEN,
      ROOK,
      BISHOP,
      KNIGHT,
      PAWN,
      //jinei
      WHITE = 8,
      BLACK = 16,
    };
    static vector<Point> Get_PieceMovesList(Point pt,int piece);
    
  };
  class Board {

    bool player_turn = true;
    unsigned int size = BOARD_SIZE;    
    int board[BOARD_SIZE][BOARD_SIZE];
    char teamArea[BOARD_SIZE][BOARD_SIZE];  
    vector<string> logs;

    struct Settings {
      //True：先行

    };

    vector<string> GetPossibleMovesList(int x,int y);

  public:
    bool Get_plyaer_turn() const;
    unsigned int Get_size() const ;
    Point Find_Piece(Point pt,int piece)const;
    int Get_Board_value(int x,int y) const;
    char Get_Board_char(int x, int y) const;


    void Init();
    void SSelect();  
    bool VEval_GoFirst();
    bool VEval_GoSecond();    
    bool Move(std::string cmd,bool turn);
  };

  class Render
  {

  private:
    //console
    
    //render method
    static void Render_Board(const Board &board);
    static void Render_MyTurn();
    static void Render_EnemyTurn();
    static void Render_Win();    
    static void Render_Lose();
    
    
  public:
    enum Console_Cmd {
      CLEAN,
      LIGHT
    };
    
    enum RenderCmd{
      MY_TURN,
      MY_TURN_NOMOVE,
      ENEMY_TURN,
      ENEMY_TURN_NOMOVE,      
      WIN,
      LOSE
    };

    static void Console_Render(Console_Cmd cmd);
    static void Rendering(RenderCmd cmd , const Chess::Board &game);
  };
} // namespace chess
