void reset(){
  int x1,x2,y1,y2;
  for (int i=0;i<=3;i++){
    for (int j=0;j<=3;j++){
      board[i][j]=0;
    }
  }
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
  score=0;
}

boolean collapse(int row[4],int *score){
  int points;
  boolean hasmoved=false;
  // move tiles together
  hasmoved=removeBlanks(row);
  // add tiles
  points=add(row);
  *score+=points;
  return hasmoved || points!=0;
}

boolean removeBlanks(int row[4]){
  int destination=0;
  boolean move=false;
  for (int i=0; i<=3;i++){
    if (row[i]!=0){
      if (destination!=i){
        row[destination]=row[i];
        row[i]=0;
        move=true;
      }
      destination++;
    }
  }
  return move;
}

int add(int row[4]){
  int points=0;
  if (row[0]==row[1] && row[0]!=0){
    row[0]+=1;
    points+=pow(2,row[0])+1;
    if (row[2]==row[3] && row[2]!=0){
      row[2]+=1;
      points+=pow(2,row[2])+1;
      row[1]=row[2];
      row[2]=0;
      row[3]=0;
      return points;
    }
    row[1]=row[2];
    row[2]=row[3];
    row[3]=0;
    return points;
  }
  if (row[1]==row[2] && row[1]!=0){
    row[1]+=1;
    points+=pow(2,row[1])+1;
    row[2]=row[3];
    row[3]=0;
    return points; 
  }
  if (row[2]==row[3] && row[2]!=0){
    row[2]+=1;
    points+=pow(2,row[2])+1;
    row[3]=0;
  }
  return points; 
}


void newone(int dir){
  int i,j,k,r,newTile;
  int n=0;
  r=random(0,100);
  if (r>=90) {
    newTile=2;
  } 
  else {
    newTile=1;
  }
  for (i=0;i<=3;i++){
    for (j=0;j<=3;j++){
      if (board[i][j]==0){
        n+=1;
      }
    }
  }
  if (n!=0){
    k=random(1,n+1);
    n=0;
    for (i=0;i<=3;i++){
      for (j=0;j<=3;j++){
        if (board[i][j]==0){
          n+=1;
          if (n==k){
            board[i][j]=newTile;
            return;
          }
        }
      }
    }
  }
}

boolean gameNotOver(){
  int score=0;
  boolean notGameOver=false;
  // up
  for (int i=0; i<=3; i++){
    // read the column i into row
    for (int j=0; j<=3;j++){
      row[j]=board[j][i];
    }
    // collapse row and count points
    notGameOver=collapse(row,&score)||notGameOver;
  }
  // down
  for (int i=0; i<=3; i++){
    // read the column i into row
    for (int j=0; j<=3;j++){
      row[j]=board[3-j][i];
    }
    // collapse row and count points
    notGameOver=collapse(row,&score)||notGameOver;
  }
  // left
  for (int i=0; i<=3; i++){
    // read the line i into row
    for (int j=0; j<=3;j++){
      row[j]=board[i][j];
    }
    // collapse row and count points
    notGameOver=collapse(row,&score)||notGameOver;
  }
  // right
  for (int i=0; i<=3; i++){
    // read the line i into row
    for (int j=0; j<=3;j++){
      row[j]=board[i][3-j];
    }
    // collapse row and count points
    notGameOver=collapse(row,&score)||notGameOver;
  }
  return notGameOver;
}

void boardPrint(){
  gb.display.cursorX=47;
  gb.display.cursorY=1;
  gb.display.setFont(font5x7);
  gb.display.print("Eleven");
  gb.display.setFont(font3x5);
  gb.display.cursorX=50;
  gb.display.cursorY=10;
  gb.display.print("Score :");
  gb.display.cursorX=55;
  gb.display.cursorY=17;
  gb.display.print(score);
  gb.display.cursorX=50;
  gb.display.cursorY=24;
  gb.display.print("Highest :");
  gb.display.cursorX=55;
  gb.display.cursorY=31;
  gb.display.print(highScore);
  if (!gameNotOver()){
    gb.display.cursorX=47;
    gb.display.cursorY=38;
    gb.display.print("Game over");
  }
  for (int i=0;i<=3;i++){
    for (int j=0;j<=3;j++){
      gb.display.drawRect(j*11,i*11,12,12);
      if (board[i][j]<=9){
        gb.display.cursorX=4+j*11;
        gb.display.cursorY=4+i*11;
      }
      else{
        gb.display.cursorX=2+j*11;
        gb.display.cursorY=4+i*11;
      }
      if (board[i][j]==11){
        won=true;
      }
      if (board[i][j]!=0){
        gb.display.print(board[i][j]);
      }
    }
  }
  if (won){
    gb.display.setFont(font5x7);
    gb.display.cursorX=47;
    gb.display.cursorY=38;
    gb.display.print("Won !");
  }
}


































