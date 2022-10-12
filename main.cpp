/*
  Programmer:           Mohammad Seeam
  Topic:                Making connect 4 game.
*/

#include<iostream>
#include <fstream> 
#include <iomanip>
#include <string>
#include <cmath> 
#include <iostream>
#include <string>
#include<time.h>
using namespace std; 

class Board{

  private:

    char** arr;
    int numCol;
    int numRow;
    int winSum;
    int totalMoves;

  public:
    Board(int r, int c, int w){   //custom constructor

      //init row and column values
      numRow = r;
      numCol = c;
      winSum = w;
      totalMoves = 0;

      //create the first dimention of 2d array
      arr = new char* [numRow];

      //create a second dimention of 2d array
      for(int i=0; i< numRow; i++){
        arr[i] = new char[numCol];
      }

      clearBoard();
    }

    void clearBoard(){
      //populate the char array with *
      for(int i=0; i< numRow; i++){
        for(int j=0; j< numCol;j++){
          arr[i][j] = '*';
        }
      }
      totalMoves=0;
    }

    void displayBoard(){
      for (int i=1; i<=numCol;i++){
        cout<<i<<" ";
      }

      cout<<endl;
      for(int i=0; i< numRow; i++){
         for(int j=0; j< numCol; j++){
            cout << arr[i][j] << " ";
         }
         cout << endl;
      }
    }
    
    bool check_left_right(int targetRowIndex, int targetColIndex, char playerNum){

      //total count that should be equal to winSum, in that case game over.
      int Count=0;

      //add the candidate items value to count
      Count = Count + 1;

      //check left
      for(int i=1; i< winSum; i++){
        if(targetColIndex-i>-1){
          if(arr[targetRowIndex][targetColIndex-i]==playerNum){
            Count = Count + 1;
          }else{
            break;
          }      
        }else{
          break;
        }
      }

      //check right
      for(int i=1; i< winSum; i++){
        if(targetColIndex+i<numCol){
          if(arr[targetRowIndex][targetColIndex+i]==playerNum){
              Count = Count + 1;
          }else{
            break;
          }
        }else{
          break;
        }
      }

      //now check if Count is equal to winSum
      if(Count==winSum){
        return true;
      }else{
        return false;
      }
    }

    bool check_up_down(int targetRowIndex, int targetColIndex, char playerNum){

      //total count that should be equal to winSum, in that case game over.
      int Count=0;

      //add the candidate items value to count
      Count = Count + 1;

      //check up
      for(int i=1; i< winSum; i++){
        if(targetRowIndex-i>-1){
          if(arr[targetRowIndex-i][targetColIndex]==playerNum){
            Count = Count + 1;
          }else{
            break;
          }      
        }else{
          break;
        }
      }

      //check down
      for(int i=1; i< winSum; i++){
        if(targetRowIndex+i<numRow){
          if(arr[targetRowIndex+i][targetColIndex]==playerNum){
            Count = Count + 1;
          }else{
            break;
          }      
        }else{
          break;
        }
      }
      
      //cout << "count" << Count << endl;
      //now check if Count is equal to winSum
      if(Count==winSum){
        return true;
      }else{
        return false;
      }
    }

    bool check_up_left_to_down_right_diagonal(int targetRowIndex, int targetColIndex, char playerNum){

      //total count that should be equal to winSum, in that case game over.
      int Count=0;

      //add the candidate items value to count
      Count = Count + 1;

       //check up_left 
      for(int i=1; i< winSum; i++){
        if(targetRowIndex-i>-1 && targetColIndex-i>-1){
          if(arr[targetRowIndex-i][targetColIndex-i]==playerNum){
            Count = Count + 1;
          }else{
            break;
          }      
        }else{
          break;
        }
      }

      //check down_right 
      for(int i=1; i< winSum; i++){
        if(targetRowIndex+i<numRow && targetColIndex+i<numCol){
          if(arr[targetRowIndex+i][targetColIndex+i]==playerNum){
            Count = Count + 1;
          }else{
            break;
          }      
        }else{
          break;
        }
      }
    
      if(Count==winSum){
        return true;
      }else{
        return false;
      }
      return false;
    }
    
    bool check_down_left_to_up_right_diagonal(int targetRowIndex, int targetColIndex, char playerNum){

      //total count that should be equal to winSum, in that case game over.
      int Count=0;

      //add the candidate items value to count
      Count = Count + 1;

        //check down left
      for(int i=1; i< winSum; i++){
        if(targetRowIndex+i<numRow && targetColIndex-i>-1){
          if(arr[targetRowIndex+i][targetColIndex-i]==playerNum){
            Count = Count + 1;
          }else{
            break;
          }      
        }else{
          break;
        }
      }

       //check up right 
      for(int i=1; i< winSum; i++){
        if(targetRowIndex-i>-1 && targetColIndex+i<numCol){
          if(arr[targetRowIndex-i][targetColIndex+i]==playerNum){
            Count = Count + 1;
          }else{
            break;
          }      
        }else{
          break;
        }
      }
      
      if(Count==winSum){
         return true;
      }else{
        return false;
      }
      return false;
  };

  string makeAmove(int targetCol, char playerNum){

      //check if any move available
      if(totalMoves>=(numRow*numCol)){ 
        return "no_more_moves";
      }
      int targetColIndex = targetCol - 1;
      for(int i=numRow-1; i>=0; i--){
        if (arr[i][targetColIndex]=='*'){
            arr[i][targetColIndex]=playerNum;
            
            //targetRowIndex => i
            //targetColIndex => targetColIndex
            //now check if the move we just made made a score
            totalMoves++;
            if(check_left_right(i, targetColIndex, playerNum)==true || check_up_down(i, targetColIndex, playerNum)==true || check_up_left_to_down_right_diagonal(i, targetColIndex, playerNum)==true || check_down_left_to_up_right_diagonal(i, targetColIndex, playerNum)==true){
              return "valid_move_and_game";
            }else{
              return "valid_move_no_game";
            }
        }
      }
      return "invalid_move_column_full";
    }
};

int main(){
  
  string play_1, play_2;
  string oppositionPlayerName = "S";

  char check_computer_or_man;
  cout<<"Do you want to play with Computer or Man Versus Man? Press C/c for Computer or M/m for Man Versus Man: ";

  //is other guy computer or a real player
  while (true){
    cin >> check_computer_or_man;
    if (check_computer_or_man == 'C' || check_computer_or_man=='c' || check_computer_or_man == 'M' || check_computer_or_man=='m'){
      if(check_computer_or_man == 'C' || check_computer_or_man=='c'){
        oppositionPlayerName = "Computer";
      }else{
        oppositionPlayerName = "S";
      }
      break;
    }else {
      cout<<"Invalid input ! Please press C/c for Computer or M/m for Man Versus Man: ";
      continue;
    }
  }
  
  int count_of_number_of_game_for_player_1=0;
  int count_of_number_of_game_for_player_2=0;
  int total_game_number=0;
  
  int board_row;
  int board_col;
  int board_game_num;
  cout<<"Please enter the row number of the board: ";
  cin >> board_row;
  cout<<"Please enter the column number of the board: ";
  cin >> board_col;
  cout<<"Please enter the length of the line which is required to win the game: ";
  cin >> board_game_num;
  Board b(board_row,board_col,board_game_num);

  //make a move
  int move_1;
  int move_2;

  bool newGame=true;
  char nowPlaying = 'M';
  while(true){ 

    if(newGame==true){
      total_game_number++;
      newGame = false;
    }

    if(nowPlaying=='M'){
      b.displayBoard();
      cout<<"Please make a move for player M between column 1 to "<<board_col<<" or 0 to Quit: ";
      cout<<"";
      cin>>move_1;

      if(move_1>board_col){
        cout<<"Invalid column number"<<endl;
      }else if(move_1==0){
        count_of_number_of_game_for_player_2++;
        cout<<"Player M won: "<<count_of_number_of_game_for_player_1<<" games. "<<"Player M played: "<< total_game_number<<" games. "<<"Player M has: " <<((count_of_number_of_game_for_player_1*100)/total_game_number)<<" % of score. "<<endl;
        cout<<"Player "<<oppositionPlayerName<<" won: "<<count_of_number_of_game_for_player_2<<" games. "<<"Player " << oppositionPlayerName << " played: "<< total_game_number<<" games. "<<" Player "<<oppositionPlayerName<< " has: " <<((count_of_number_of_game_for_player_2*100)/total_game_number)<<" % of score. "<<endl;
        cout<<"Good Bye !"<<endl;
        exit(0);
      }else{
        play_1 = b.makeAmove(move_1, 'M');
        cout<<""<<endl;
        //int move_2;
        //cout << oppositionPlayerName << " moved on column " << move_2 <<" ."<<endl;
        cout<<""<<endl;
        cout<<endl;
        //when the current game will continue
        if(play_1=="valid_move_no_game"){
          nowPlaying='S';
          continue;
        }else if(play_1=="invalid_move_column_full"){
          cout<<"Column Full"<<endl;
          continue;
        }
        //when current game is over
        if(play_1=="no_more_moves"){
          cout << "Game over ! No one won because the board is full and there is no valid move left. " << endl;
        }else if(play_1=="valid_move_and_game"){
          b.displayBoard();
          cout<<endl;
          cout<<"Player M won the game !"<<endl;
          count_of_number_of_game_for_player_1++;
        }
        //ask user if they want to play again
        while(true){
          cout << "Do you want to play again? Press Y/y for Yes or press N/n for No: ";
          char c;
          cin>>c;
          if(c=='Y' || c=='y'){
            newGame=true;
            //clear the board
            b.clearBoard();
            break;
          }else if(c=='N' || c=='n'){
            cout<<"Player M won: "<<count_of_number_of_game_for_player_1<<" games. "<<"Player M played: "<< total_game_number<<" games. "<<"Player M has: " <<((count_of_number_of_game_for_player_1*100)/total_game_number)<<" % of score. "<<endl;
            cout<<"Player "<<oppositionPlayerName<<" won: "<<count_of_number_of_game_for_player_2<<" games. "<<"Player " << oppositionPlayerName << " played: "<< total_game_number<<" games. "<<" Player "<<oppositionPlayerName<< " has: " <<((count_of_number_of_game_for_player_2*100)/total_game_number)<<" % of score. "<<endl;
            cout<<"Good Bye !"<<endl;
            exit(0);
          }else {
            cout<<"Invalid character. Press Y/y for Yes or press N/n for No: "<<endl; 
            continue;
          }
        }
      }
    }else if(nowPlaying=='S'){
      b.displayBoard();
      int move_2=0;
      if(check_computer_or_man=='C' || check_computer_or_man=='c'){
        move_2=((rand()%board_col)+1);
      }else{
        cout<<"Please make a move for player S between column 1 to "<<board_col<<" or 0 to Quit: ";
        cin>>move_2;
      }
      if(move_2>board_col){
        cout<<"Invalid column number"<<endl;
      }else if(move_2==0){
        count_of_number_of_game_for_player_1++;
        cout<<"Player M won: "<<count_of_number_of_game_for_player_1<<" games. "<<"Player M played: "<< total_game_number<<" games. "<<"Player M has: " <<((count_of_number_of_game_for_player_1*100)/total_game_number)<<" % of score. "<<endl;
        cout<<"Player "<<oppositionPlayerName<<" won: "<<count_of_number_of_game_for_player_2<<" games. "<<"Player " << oppositionPlayerName << " played: "<< total_game_number<<" games. "<<" Player "<<oppositionPlayerName<< " has: " <<((count_of_number_of_game_for_player_2*100)/total_game_number)<<" % of score. "<<endl;
        cout<<"Good Bye !"<<endl;
        exit(0);
      }else{
        play_2 = b.makeAmove(move_2, 'S');
     
        cout << oppositionPlayerName << " moved on column " << move_2 <<" ."<<endl;
        cout<<""<<endl;;
       
        //when the current game will continue
        if(play_2=="valid_move_no_game"){
          nowPlaying='M';
          continue;
        }else if(play_2=="invalid_move_column_full"){
          cout<<"Column Full"<<endl;
          continue;
        }
        //when current game is over
        if(play_2=="no_more_moves"){
          cout << "Game over ! No one won because the board is full and there is no valid move left. " << endl;
        }else if(play_2=="valid_move_and_game"){
          b.displayBoard();
          cout<<endl;
          cout<<"Player S won the game !"<<endl;
          count_of_number_of_game_for_player_2++;
        }
        //ask user if they want to play again
        while(true){
          cout << "Do you want to play again? Press Y/y for Yes or press N/n for No: ";
          char c;
          cin>>c;
          if(c=='Y' || c=='y'){
            //clear the board
            newGame=true;
            b.clearBoard();
            break;
          }else if (c=='N' || c=='n'){
            cout<<"Player M won: "<<count_of_number_of_game_for_player_1<<" games. "<<"Player M played: "<< total_game_number<<" games. "<<"Player M has: " <<((count_of_number_of_game_for_player_1*100)/total_game_number)<<" % of score. "<<endl;
            cout<<"Player "<<oppositionPlayerName<<" won: "<<count_of_number_of_game_for_player_2<<" games. "<<"Player " << oppositionPlayerName << " played: "<< total_game_number<<" games. "<<" Player "<<oppositionPlayerName<< " has: " <<((count_of_number_of_game_for_player_2*100)/total_game_number)<<" % of score. "<<endl;
            cout<<"Good Bye !"<<endl;
            exit(0);
          }else{
            cout<<"Invalid character. Press Y/y for Yes or press N/n for No: "<<endl; 
            continue;
          }
        }
      }
    }   
  }
}

/*
Do you want to play with Computer or Man Versus Man? Press C/c for Computer or M/m for Man Versus Man: a
Invalid input ! Please press C/c for Computer or M/m for Man Versus Man: c
Please enter the row number of the board: 8
Please enter the column number of the board: 7
Please enter the length of the line which is required to win the game: 3
1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 1



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
Computer moved on column 1 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S * * * * * * 
M * * * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 3



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S * * * * * * 
M * M * * * * 
Computer moved on column 1 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S * * * * * * 
S * * * * * * 
M * M * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 1



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
S * * * * * * 
S * * * * * * 
M * M * * * * 
Computer moved on column 3 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
S * * * * * * 
S * S * * * * 
M * M * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 3



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
S * M * * * * 
S * S * * * * 
M * M * * * * 
Computer moved on column 7 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
S * M * * * * 
S * S * * * * 
M * M * * * S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 2



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
S * M * * * * 
S * S * * * * 
M M M * * * S 

Player M won the game !
Do you want to play again? Press Y/y for Yes or press N/n for No: y
1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 1



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
Computer moved on column 7 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 2



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M M * * * * S 
Computer moved on column 7 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * S 
M M * * * * S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 2



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* M * * * * S 
M M * * * * S 
Computer moved on column 3 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* M * * * * S 
M M S * * * S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 3



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* M M * * * S 
M M S * * * S 
Computer moved on column 2 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* S * * * * * 
* M M * * * S 
M M S * * * S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 5



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* S * * * * * 
* M M * * * S 
M M S * M * S 
Computer moved on column 2 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* S * * * * * 
* S * * * * * 
* M M * * * S 
M M S * M * S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 2



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* M * * * * * 
* S * * * * * 
* S * * * * * 
* M M * * * S 
M M S * M * S 
Computer moved on column 2 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* S * * * * * 
* M * * * * * 
* S * * * * * 
* S * * * * * 
* M M * * * S 
M M S * M * S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 3



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* S * * * * * 
* M * * * * * 
* S * * * * * 
* S M * * * * 
* M M * * * S 
M M S * M * S 

Player M won the game !
Do you want to play again? Press Y/y for Yes or press N/n for No: y
1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 5



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * M * * 
Computer moved on column 7 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * M * S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 4



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * M M * S 
Computer moved on column 3 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * S M M * S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 6



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * S M M M S 

Player M won the game !
Do you want to play again? Press Y/y for Yes or press N/n for No: y
1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 1



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
Computer moved on column 1 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S * * * * * * 
M * * * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 5



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S * * * * * * 
M * * * M * * 
Computer moved on column 7 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S * * * * * * 
M * * * M * S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 3



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S * * * * * * 
M * M * M * S 
Computer moved on column 1 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S * * * * * * 
S * * * * * * 
M * M * M * S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 1



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
S * * * * * * 
S * * * * * * 
M * M * M * S 
Computer moved on column 6 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
S * * * * * * 
S * * * * * * 
M * M * M S S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 3



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
S * * * * * * 
S * M * * * * 
M * M * M S S 
Computer moved on column 3 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
S * S * * * * 
S * M * * * * 
M * M * M S S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 5



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
S * S * * * * 
S * M * M * * 
M * M * M S S 
Computer moved on column 5 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
S * S * S * * 
S * M * M * * 
M * M * M S S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 5



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * M * * 
S * S * S * * 
S * M * M * * 
M * M * M S S 
Computer moved on column 5 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * S * * 
M * * * M * * 
S * S * S * * 
S * M * M * * 
M * M * M S S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 6



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * S * * 
M * * * M * * 
S * S * S * * 
S * M * M M * 
M * M * M S S 
Computer moved on column 4 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * S * * 
M * * * M * * 
S * S * S * * 
S * M * M M * 
M * M S M S S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 6



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * S * * 
M * * * M * * 
S * S * S M * 
S * M * M M * 
M * M S M S S 
Computer moved on column 5 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * S * * 
* * * * S * * 
M * * * M * * 
S * S * S M * 
S * M * M M * 
M * M S M S S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 6



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * S * * 
* * * * S * * 
M * * * M M * 
S * S * S M * 
S * M * M M * 
M * M S M S S 

Player M won the game !
Do you want to play again? Press Y/y for Yes or press N/n for No: y
1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 3



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * M * * * * 
Computer moved on column 6 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * M * * S * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 2



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* M M * * S * 
Computer moved on column 2 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* S * * * * * 
* M M * * S * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 4



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* S * * * * * 
* M M M * S * 

Player M won the game !
Do you want to play again? Press Y/y for Yes or press N/n for No: y
1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 1



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
M * * * * * * 
Computer moved on column 1 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S * * * * * * 
M * * * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 19
Invalid column number
1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S * * * * * * 
M * * * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 2



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S * * * * * * 
M M * * * * * 
Computer moved on column 2 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S S * * * * * 
M M * * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 9
Invalid column number
1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S S * * * * * 
M M * * * * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 5



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S S * * * * * 
M M * * M * * 
Computer moved on column 4 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S S * * * * * 
M M * S M * * 
Please make a move for player M between column 1 to 7 or 0 to Quit: 6



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S S * * * * * 
M M * S M M * 
Computer moved on column 7 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S S * * * * * 
M M * S M M S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 7



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S S * * * * M 
M M * S M M S 
Computer moved on column 3 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S S * * * * M 
M M S S M M S 
Please make a move for player M between column 1 to 7 or 0 to Quit: 4



1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S S * M * * M 
M M S S M M S 
Computer moved on column 1 .

1 2 3 4 5 6 7 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
* * * * * * * 
S * * * * * * 
S S * M * * M 
M M S S M M S 

Player S won the game !
Do you want to play again? Press Y/y for Yes or press N/n for No: n
Player M won: 5 games. Player M played: 6 games. Player M has: 83 % of score. 
Player Computer won: 1 games. Player Computer played: 6 games.  Player Computer has: 16 % of score. 
Good Bye !
*/

//********************************************************************************************************//

/*
Do you want to play with Computer or Man Versus Man? Press C/c for Computer or M/m for Man Versus Man: m
Please enter the row number of the board: 5
Please enter the column number of the board: 5
Please enter the length of the line which is required to win the game: 3
1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
Please make a move for player M between column 1 to 5 or 0 to Quit: 1



1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
M * * * * 
Please make a move for player S between column 1 to 5 or 0 to Quit: 2
S moved on column 2 .

1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
M S * * * 
Please make a move for player M between column 1 to 5 or 0 to Quit: 1



1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
M * * * * 
M S * * * 
Please make a move for player S between column 1 to 5 or 0 to Quit: 3
S moved on column 3 .

1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
M * * * * 
M S S * * 
Please make a move for player M between column 1 to 5 or 0 to Quit: 1



1 2 3 4 5 
* * * * * 
* * * * * 
M * * * * 
M * * * * 
M S S * * 

Player M won the game !
Do you want to play again? Press Y/y for Yes or press N/n for No: u
Invalid character. Press Y/y for Yes or press N/n for No: 
Do you want to play again? Press Y/y for Yes or press N/n for No: y
1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
Please make a move for player M between column 1 to 5 or 0 to Quit: 1



1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
M * * * * 
Please make a move for player S between column 1 to 5 or 0 to Quit: 4
S moved on column 4 .

1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
M * * S * 
Please make a move for player M between column 1 to 5 or 0 to Quit: 2



1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
M M * S * 
Please make a move for player S between column 1 to 5 or 0 to Quit: 4
S moved on column 4 .

1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * S * 
M M * S * 
Please make a move for player M between column 1 to 5 or 0 to Quit: 1



1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
M * * S * 
M M * S * 
Please make a move for player S between column 1 to 5 or 0 to Quit: 4
S moved on column 4 .

1 2 3 4 5 
* * * * * 
* * * * * 
* * * S * 
M * * S * 
M M * S * 

Player S won the game !
Do you want to play again? Press Y/y for Yes or press N/n for No: y
1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
Please make a move for player S between column 1 to 5 or 0 to Quit: 5
S moved on column 5 .

1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
* * * * S 
Please make a move for player M between column 1 to 5 or 0 to Quit: 4



1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
* * * M S 
Please make a move for player S between column 1 to 5 or 0 to Quit: 5
S moved on column 5 .

1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * S 
* * * M S 
Please make a move for player M between column 1 to 5 or 0 to Quit: 3



1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * S 
* * M M S 
Please make a move for player S between column 1 to 5 or 0 to Quit: 5
S moved on column 5 .

1 2 3 4 5 
* * * * * 
* * * * * 
* * * * S 
* * * * S 
* * M M S 

Player S won the game !
Do you want to play again? Press Y/y for Yes or press N/n for No: y
1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
Please make a move for player S between column 1 to 5 or 0 to Quit: 2
S moved on column 2 .

1 2 3 4 5 
* * * * * 
* * * * * 
* * * * * 
* * * * * 
* S * * * 
Please make a move for player M between column 1 to 5 or 0 to Quit: 0
Player M won: 1 games. Player M played: 4 games. Player M has: 25 % of score. 
Player S won: 3 games. Player S played: 4 games.  Player S has: 75 % of score. 
Good Bye !
*/

//********************************************************************************************************//

/*
Do you want to play with Computer or Man Versus Man? Press C/c for Computer or M/m for Man Versus Man: m
Please enter the row number of the board: 3
Please enter the column number of the board: 3
Please enter the length of the line which is required to win the game: 3
1 2 3 
* * * 
* * * 
* * * 
Please make a move for player M between column 1 to 3 or 0 to Quit: 1



1 2 3 
* * * 
* * * 
M * * 
Please make a move for player S between column 1 to 3 or 0 to Quit: 2
S moved on column 2 .

1 2 3 
* * * 
* * * 
M S * 
Please make a move for player M between column 1 to 3 or 0 to Quit: 5
Invalid column number
1 2 3 
* * * 
* * * 
M S * 
Please make a move for player M between column 1 to 3 or 0 to Quit: 1



1 2 3 
* * * 
M * * 
M S * 
Please make a move for player S between column 1 to 3 or 0 to Quit: 1
S moved on column 1 .

1 2 3 
S * * 
M * * 
M S * 
Please make a move for player M between column 1 to 3 or 0 to Quit: 1



Column Full
1 2 3 
S * * 
M * * 
M S * 
Please make a move for player M between column 1 to 3 or 0 to Quit: 2



1 2 3 
S * * 
M M * 
M S * 
Please make a move for player S between column 1 to 3 or 0 to Quit: 2
S moved on column 2 .

1 2 3 
S S * 
M M * 
M S * 
Please make a move for player M between column 1 to 3 or 0 to Quit: 2



Column Full
1 2 3 
S S * 
M M * 
M S * 
Please make a move for player M between column 1 to 3 or 0 to Quit: 3



1 2 3 
S S * 
M M * 
M S M 
Please make a move for player S between column 1 to 3 or 0 to Quit: 3
S moved on column 3 .

1 2 3 
S S * 
M M S 
M S M 
Please make a move for player M between column 1 to 3 or 0 to Quit: 3



1 2 3 
S S M 
M M S 
M S M 

Player M won the game !
Do you want to play again? Press Y/y for Yes or press N/n for No: n
Player M won: 1 games. Player M played: 1 games. Player M has: 100 % of score. 
Player S won: 0 games. Player S played: 1 games.  Player S has: 0 % of score. 
Good Bye !
*/

