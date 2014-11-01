#include <SPI.h>
#include <Gamebuino.h>
#include <math.h>
#include <EEPROM.h>
Gamebuino gb;

// these two default fonts are already defined in the Gamebuino library
// the "extern" modifier is used to be able to use a variable declared in another file
extern const byte font3x5[]; //a small but efficient font (default)
extern const byte font5x7[]; //a large, comfy font

int line0[4] = {
  0,0,0,0};
int line1[4] = {
  0,0,0,0};
int line2[4] = {
  0,0,0,0};
int line3[4] = {
  0,0,0,0};
int* board[4] = {
  line0,line1,line2,line3};

int highScore=0;
int score=0;
int row[4];
boolean notBlocked;
int move;
boolean won;


///////////////////////////////////// SETUP
void setup() {
  int x1,x2,y1,y2;
  gb.begin(); //initialize the Gamebuino
  gb.display.setFont(font5x7);
  gb.titleScreen(F("Eleven")); //shows the main menu
  gb.pickRandomSeed();
  gb.display.setFont(font3x5);
  gb.battery.show = false;
  x1=random(0,3);
  x2=random(0,3);
  y1=random(0,3);
  y2=random(0,3);
  while (x1==x2 && y1==y2){
    x2=random(0,3);
    y2=random(0,3);
  }
  board[x1][y1]=1;
  board[x2][y2]=1;
}

///////////////////////////////////// LOOP
void loop() {
  if(gb.update()){
    notBlocked=false;
    move=0;
    if(gb.buttons.pressed(BTN_C)){
      gb.titleScreen(F("Eleven")); //shows the main menu
    }
    else if(gb.buttons.pressed(BTN_UP) && !won){
      move=1; // up
      for (int i=0; i<=3; i++){
        // read the column i into row
        for (int j=0; j<=3;j++){
          row[j]=board[j][i];
        }
        // collapse row and count points
        notBlocked=collapse(row,&score)||notBlocked;
        // store row back to board
        for (int j=0; j<=3;j++){
          board[j][i]=row[j];
        }
      }
    }
    else if(gb.buttons.pressed(BTN_DOWN) && !won){
      move=2; // down
      for (int i=0; i<=3; i++){
        // read the column i into row
        for (int j=0; j<=3;j++){
          row[j]=board[3-j][i];
        }
        // collapse row and count points
        notBlocked=collapse(row,&score)||notBlocked;
        // store row back to board
        for (int j=0; j<=3;j++){
          board[3-j][i]=row[j];
        }
      }
    }
    else if(gb.buttons.pressed(BTN_LEFT) && !won){
      move=3; // left
      for (int i=0; i<=3; i++){
        // read the line i into row
        for (int j=0; j<=3;j++){
          row[j]=board[i][j];
        }
        // collapse row and count points
        notBlocked=collapse(row,&score)||notBlocked;
        // store row back to board
        for (int j=0; j<=3;j++){
          board[i][j]=row[j];
        }
      }
    }
    else if(gb.buttons.pressed(BTN_RIGHT) && !won){
      move=4; // right
      for (int i=0; i<=3; i++){
        // read the line i into row
        for (int j=0; j<=3;j++){
          row[j]=board[i][3-j];
        }
        // collapse row and count points
        notBlocked=collapse(row,&score)||notBlocked;
        // store row back to board
        for (int j=0; j<=3;j++){
          board[i][3-j]=row[j];
        }
      }     
    }
    else if(gb.buttons.pressed(BTN_B)){
      reset();
    }
    if (move!=0 && notBlocked && !won){
      newone(move);
    }
    if (score>highScore){
      highScore=score;
    }
    boardPrint();
  }
}



















