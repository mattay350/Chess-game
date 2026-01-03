#include <iostream>
#include "chess.hpp"
#include <string>
#include <cctype>

using namespace std;

namespace Chess {
  //point
  bool Point::operator== (const Point &pt1) const
  {
    return x == pt1.x && y ==pt1.y;
  }

  // piece
  vector<Point> Piece::Get_PieceMovesList(Point pt, int piece) {
    //
    vector<Point> movelst;
    piece = piece & 7;
    
    // get movedlist
    switch (piece) {
    case NONE:
      break;
    case KING:
      movelst.assign({Point(pt.x + 1, pt.y), Point(pt.x + 1, pt.y + 1),
	  Point(pt.x + 1, pt.y - 1), Point(pt.x - 1, pt.y),
	  Point(pt.x - 1, pt.y + 1), Point(pt.x - 1, pt.y - 1),
	  Point(pt.x, pt.y + 1), Point(pt.x, pt.y - 1)});
      break;
    case QUEEN:
      for (int i = 0; i < BOARD_SIZE; i++) {
	movelst.push_back(Point(pt.x + i, pt.y));
	movelst.push_back(Point(pt.x - i, pt.y));
	movelst.push_back(Point(pt.x, pt.y + i));
	movelst.push_back(Point(pt.x, pt.y - i));
	movelst.push_back(Point(pt.x + i, pt.y + i));
	movelst.push_back(Point(pt.x + i, pt.y - i));
	movelst.push_back(Point(pt.x - i, pt.y + i));
	movelst.push_back(Point(pt.x - i, pt.y - i));
      }
      break;
    case ROOK:
      for (int i = 0; i < BOARD_SIZE; i++) {
	movelst.push_back(Point(pt.x + i, pt.y));
	movelst.push_back(Point(pt.x - i, pt.y));
	movelst.push_back(Point(pt.x, pt.y + i));
	movelst.push_back(Point(pt.x, pt.y - i));
      }
      break;
    case BISHOP:
      for (int i = 0; i < BOARD_SIZE; i++) {
	movelst.push_back(Point(pt.x + i, pt.y + i));
	movelst.push_back(Point(pt.x + i, pt.y - i));
	movelst.push_back(Point(pt.x - i, pt.y + i));
	movelst.push_back(Point(pt.x - i, pt.y - i));
      }
      break;
    case KNIGHT:
      movelst.assign({
	  Point(pt.x + 1, pt.y + 2),
	  Point(pt.x + 1, pt.y - 2),
	  Point(pt.x - 1, pt.y + 2),
	  Point(pt.x - 1, pt.y - 2),
	  Point(pt.x + 2, pt.y + 1),
	  Point(pt.x - 2, pt.y + 1),
	  Point(pt.x + 2, pt.y - 1),
	  Point(pt.x - 2, pt.y - 1),
	});

      break;
    case PAWN:
      movelst.assign({
	  Point(pt.x + 1, pt.y),
	  Point(pt.x + 2, pt.y + 1),
	});
      break;
    }

    //ありえない座標を排除する
    for (int i = 0; i < movelst.size(); i++) {
      if (movelst[i].x < 0 || movelst[i].x > BOARD_SIZE || movelst[i].y < 0 ||
	  movelst[i].y > BOARD_SIZE) {
	movelst.erase(movelst.begin() + i);
	i--;
      }
    }

    return movelst;       
  }

  
  bool Board::Get_plyaer_turn() const { return player_turn; }
  unsigned int Board::Get_size() const { return size; }
  Point Board::Find_Piece(Point pt,int piece) const
  {
    int x=0,y=0;
    int find_side = piece & 8 ;
    int find_piece = piece & 7; 
    int input_piece_side;
    int input_piece;
    
    for (int i=0;i<BOARD_SIZE;i++){
      for (int j = 0; j < BOARD_SIZE; j++) {

	input_piece_side = Get_Board_value(j,i) & 8;
	input_piece = Get_Board_value(j,i) & 7;
	if(input_piece_side == find_side){
	  if(input_piece ==find_piece)
            if (input_piece != Piece::PAWN) {
              x = j;
              y = i;
            } else if (pt.x == j) {
              x = j;
              y = i;
            }
        }
      }
    }
    return Point(x,y);
  }  
    int Board::Get_Board_value(int x, int y) const {return board[x][y];}
    char Board::Get_Board_char(int x, int y) const
    {
      char c;
      int i;
      i = Get_Board_value(x,y);
      if( i == Piece::NONE)
	c = ' ';
      if(i & 16){
	i = i & 7;
	switch (i) {
	case Piece::KING:
	  c = 'K';
	  break;
	case Piece::QUEEN:
	  c = 'Q';
	  break;
	case Piece::ROOK:
	  c = 'R';
	  break;
	case Piece::BISHOP:
	  c = 'B';
	  break;
	case Piece::KNIGHT:
	  c = 'N';
	  break;
	case Piece::PAWN:
	  c = 'P';
	  break;
	}
      }
      if(i & 8){
	i = i & 7;      
	switch (i) {
	case Piece::KING:
	  c = 'k';
	  break;
	case Piece::QUEEN:
	  c = 'q';
	  break;
	case Piece::ROOK:
	  c = 'r';
	  break;
	case Piece::BISHOP:
	  c = 'b';
	  break;
	case Piece::KNIGHT:
	  c = 'n';
	  break;
	case Piece::PAWN:
	  c = 'p';
	  break;

	}
      }
      return c;
    }

    void Board::Init()
    {
      for(int y =0;y<BOARD_SIZE;y++){
	for(int x =0;x<BOARD_SIZE;x++){
	  //BLACK Piece set
	  switch (y) {
	  case 0:
	    board[0][y] = Piece::ROOK | Piece::BLACK;
	    board[1][y] = Piece::KNIGHT | Piece::BLACK;
	    board[2][y] = Piece::BISHOP | Piece::BLACK;
	    board[3][y] = Piece::QUEEN | Piece::BLACK;
	    board[4][y] = Piece::KING | Piece::BLACK;
	    board[5][y] = Piece::BISHOP | Piece::BLACK;
	    board[6][y] = Piece::KNIGHT | Piece::BLACK;
	    board[7][y] = Piece::ROOK | Piece::BLACK;
	    break;

	  case 1:
	    board[x][y] = Piece::PAWN | Piece::BLACK;
	    continue;

	    // WHITE Piece set
	  case 6:
	    board[x][y] = Piece::PAWN | Piece::WHITE;
	    continue;

	  case 7:
	    board[0][y] = Piece::ROOK | Piece::WHITE;
	    board[1][y] = Piece::KNIGHT | Piece::WHITE;
	    board[2][y] = Piece::BISHOP | Piece::WHITE;
	    board[3][y] = Piece::QUEEN | Piece::WHITE;
	    board[4][y] = Piece::KING | Piece::WHITE;
	    board[5][y] = Piece::BISHOP | Piece::WHITE;
	    board[6][y] = Piece::KNIGHT | Piece::WHITE;
	    board[7][y] = Piece::ROOK | Piece::WHITE;
	    break;

	  default:
	    board[x][y] = Piece::NONE;
	    break;
	  }
	}
      }
    }
    bool Board::VEval_GoFirst()
    {
      return false;
    }
  
    bool Board::VEval_GoSecond()
    {
      return false;
    }

    bool Board::Move(string cmd,bool turn)
    {
      bool is_matched =true;
      bool is_moved =true;
      bool set_piece =false;
      //input parse
      int x = 9,y = 9;
      int piece = Piece::NONE ;
      int side = Piece::NONE ;    

      for (int i =0 ;i<cmd.length(); i++) {
	char c = cmd[i];
	if(turn) side = Piece::WHITE;
	else side = Piece::BLACK;
      
	switch(i){
	case 0://piece
	  if (c == 'K') {
	    piece = Piece::KING | side ;
	    break;
	  }
	  if (c == 'Q') {
	    piece = Piece::QUEEN | side ;
	    break;
	  }
	  if (c == 'R') {
	    piece = Piece::ROOK | side ;
	    break;
	  }
	  if (c == 'B') {
	    piece = Piece::BISHOP | side ;
	    break;         
	  }
	  if (c == 'N') {
	    piece = Piece::KNIGHT | side ;
	    break;         
	  }
	  //pawn moved
	  piece = Piece::PAWN | side ;
	  i++;
	case 1: // x
	  if (c == 'a')
	    x = 0; 
	  if (c == 'b')
	    x = 1;
	  if (c == 'c')
	    x = 2;
	  if (c == 'd')
	    x = 3;
	  if (c == 'e')
	    x = 4;
	  if (c == 'f')
	    x = 5;
	  if (c == 'g')
	    x = 6;
	  if (c == 'h')
	    x = 7;
	  if (x >= 8)
	    is_matched = false;
	  break;

	case 2: // y
	  if (isdigit(c)){
	    y = c - '0';
	    y = 8 - y;
	  }
	  else
	    is_matched = false;
	  break;
	default:
	  is_matched = false;
	}
	//コマンドとして成り立ってない
	if (!is_matched)
	  return false;
      }
      //移動できるか検証
      Point pt = Find_Piece(Point(x,y),piece);
      Point pt_moved(x,y);
      vector<Point> ptlst;
    
      ptlst = Piece::Get_PieceMovesList(pt,piece);

      for (Point p : ptlst) {
	if (p == Point(x,y)) {
	  pt_moved = p;
	  is_moved = true;
	}
      }

      //移動先が不正
      if (!is_moved)
	return false;
    
      //移動を実施する
      board[x][y] = Get_Board_value(pt.x,pt.y);
      board[pt.x][pt.y] = Piece::NONE;
      logs.push_back(cmd);
      player_turn = !player_turn;
      return true;
    }

    ///Render
    void Render::Console_Render(Render::Console_Cmd cmd)
    {
      switch (cmd) {
      case Render::CLEAN:
	cout << "\033[2J\033[H" << flush;
	break;
      case Render::LIGHT:
	cout << "\033[1;1H" << flush;
	break;
      }
    }

    void Render::Render_Board(const Board &board)
    {
      Render::Console_Render(Render::CLEAN);
    
      string footer =
	"////////////////////////////////\n\
Chess game \n\
This Turn : \n\
////////////////////////////////\n ";
   
      int board_size = board.Get_size();
      cout << " -------------------" << endl;    
      for(int y=0; y<board_size;y++){
	for (int x = 0; x < board_size; x++) {
	  if (x == 0)
	    cout << BOARD_SIZE-y << "|";
	  cout << " " << board.Get_Board_char(x, y);
	  if (x == BOARD_SIZE - 1)
	    cout <<" "<< "|" ;	
	}
	cout << "   " << "board.logs[y]" << endl;//logs
      }
      cout << " -------------------" << endl;
      cout << "   a b c d e f g h  " << endl;      
      
      cout << footer;    
    }

    void Render::Render_MyTurn()
    {
      cout << endl;
      cout << endl;
      cout << "input move cmd :";
    }

    void Render::Render_EnemyTurn()
    {
      cout << endl;
      cout << endl;
      cout << "input move cmd :" ;
    }

    void Render::Render_Win()
    {
      cout << endl;
      cout << endl;    
      cout << "YOU WIN" << endl;
    }
    void Render::Render_Lose()
    {
      cout << endl;
      cout << endl;    
      cout << "YOU LOSE" << endl;
    }

    void Render::Rendering (Render::RenderCmd cmd, const Chess::Board &game)
    {
      switch (cmd) {
      case Render::MY_TURN:
	Render::Render_Board(game);
	Render::Render_MyTurn();
	break;

      case Render::MY_TURN_NOMOVE:
	Render::Render_Board(game);
	Render::Render_MyTurn();
	cout << "not moved it." << endl;
	break;

      case Render::ENEMY_TURN:
	Render::Render_Board(game);
	Render::Render_EnemyTurn();
	break;

      case Render::ENEMY_TURN_NOMOVE:
	Render::Render_Board(game);
	Render::Render_EnemyTurn();
	cout << "not moved it." << endl;
	break;

      case Render::WIN:
	Render::Render_Win();
	break;

      case Render::LOSE:
	Render::Render_Lose();
	break;
      }
    }

  } // namespace Chess
