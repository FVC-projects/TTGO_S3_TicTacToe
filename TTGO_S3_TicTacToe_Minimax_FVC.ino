#include "TFT_eSPI.h"
#include "TicTacTOeS3.h" //Imagem inicial

TFT_eSPI lcd = TFT_eSPI();

 int fromTop=80;
 int fromLeft=10;
 int space=7;
 int boxSize=45 ;
 int playGround=3*boxSize+2*space;

 int a=0;
 int b=0;
 int option; //1- Pro 2- Hard, 3- Medium, 4-Easy, 5- 2 players
 String op[]={"Pro","Hard","Medium","Easy","2 players"};
 int jogarEm=9;
 bool winplayer=false;
 bool player1;

 #define c1 0xEEAC //brown yellow

struct TicTacToe {
 char player, computer;
 int grid[3][3];};

struct move {
  int r, c, score;};

TicTacToe jogo;


void setup() {
  Serial.begin(115200);
  
  pinMode(15,OUTPUT); // necessário para funcionar com a bateria
  digitalWrite(15,1);
  
  pinMode(0,INPUT_PULLUP);
  pinMode(14,INPUT_PULLUP);

  randomSeed(analogRead(17));
  lcd.init();

//Incial Screen
  lcd.setRotation(0);
  lcd.setSwapBytes(true);
  lcd.fillScreen(c1);
  lcd.setTextColor(TFT_BLACK);
  lcd.drawString("TicTacToe",24,17,4);
  lcd.pushImage(2, 80, animation_width  , animation_height, TicTacToeS3);
  lcd.setTextColor(TFT_RED,c1);
  lcd.drawString("FVC - 2023",50,300,2);
  delay(1500);

 //Menu Jogo
 menuini();

}

void playini() {
  a=0;
  b=0;
 // Inicialização grelha
 for (int i = 0; i < 3; i++) {
   for (int j = 0; j < 3; j++) {
     jogo.grid[i][j]= ' ';
   }
 }
 
// Grelha inicial
  lcd.fillScreen(TFT_BLACK);
  lcd.setTextColor(TFT_WHITE);
  lcd.drawString("TicTacToe",24,17,4);
//  lcd.drawFastHLine(fromLeft-space,50,164,TFT_WHITE);
  lcd.drawWedgeLine(fromLeft-space,50,161,50,3,3,TFT_WHITE,TFT_BLACK);
  lcd.drawString(op[option-1],24,30+(6*boxSize),4);
  
  lcd.drawFastVLine(fromLeft+boxSize+space/2,fromTop,playGround,TFT_WHITE);
  lcd.drawFastVLine(1+fromLeft+boxSize+space/2,fromTop,playGround,TFT_WHITE);
  lcd.drawFastVLine(fromLeft+boxSize*2+space+space/2,fromTop,playGround,TFT_WHITE);
  lcd.drawFastVLine(1+fromLeft+boxSize*2+space+space/2,fromTop,playGround,TFT_WHITE);
  lcd.drawFastHLine(fromLeft,fromTop+boxSize+space/2,playGround,TFT_WHITE);
  lcd.drawFastHLine(fromLeft,1+fromTop+boxSize+space/2,playGround,TFT_WHITE);
  lcd.drawFastHLine(fromLeft,fromTop+boxSize*2+space+space/2,playGround,TFT_WHITE);
  lcd.drawFastHLine(fromLeft,1+fromTop+boxSize*2+space+space/2,playGround,TFT_WHITE);
  
//  lcd.drawRect((fromLeft+(a*boxSize)+(a*space)),(fromTop+(b*boxSize)+(b*space)),boxSize,boxSize,TFT_RED);
  lcd.drawSmoothRoundRect((fromLeft+(a*boxSize)+(a*space)),(fromTop+(b*boxSize)+(b*space)),3,3,boxSize,boxSize,TFT_RED,TFT_BLACK);
  if (jogo.player == 'O' && option!=5) computer_move(); 
}

void menuini() 
{
  //Menu jogo
  lcd.fillScreen(TFT_BLACK);
  lcd.setTextColor(TFT_YELLOW);
  lcd.drawString("Menu Jogo",22,17,4);
//  lcd.drawFastHLine(fromLeft-space,50,164,TFT_YELLOW);
  lcd.drawWedgeLine(fromLeft-space,50,161,50,3,3,c1,TFT_BLACK);
  lcd.setTextColor(TFT_WHITE);
  for (int i = 0; i<5; i++)
  {
  lcd.drawString(op[i],fromLeft,fromTop + (35*i),4);
  }
  
 a=0;
// lcd.drawRect(fromLeft-space,fromTop-space,164,32,TFT_RED);
 lcd.drawSmoothRoundRect(fromLeft-space,fromTop-space,5,5,161,32,TFT_RED,TFT_BLACK);
 while (true) {
  
  if(digitalRead(0)==0)
  {
//    lcd.drawRect(fromLeft-space,fromTop-space+(35*a),164,32,TFT_BLACK);
    lcd.drawSmoothRoundRect(fromLeft-space,fromTop-space+(35*a),5,5,161,32,TFT_BLACK,TFT_BLACK);
    a=a+1;
    if(a>4) a=0;
//    lcd.drawRect(fromLeft-space,fromTop-space+(35*a),164,32,TFT_RED);
    lcd.drawSmoothRoundRect(fromLeft-space,fromTop-space+(35*a),5,5,161,32,TFT_RED,TFT_BLACK);
    delay(300);
  }
  if(digitalRead(14)==0)
  {
    lcd.setTextColor(TFT_RED);
    lcd.drawString(op[a],fromLeft,fromTop + (35*a),4);
    option=a+1;
    delay(300);
    break;
  }
 }
 
 // Menu jogador
 lcd.fillScreen(TFT_BLACK);
 lcd.setTextColor(TFT_YELLOW);
 lcd.drawString("Jogador",28,17,4);
// lcd.drawFastHLine(fromLeft-space,50,164,TFT_YELLOW);
 lcd.drawWedgeLine(fromLeft-space,50,161,50,3,3,c1,TFT_BLACK);
 lcd.setTextColor(TFT_WHITE);
 lcd.drawString("X",fromLeft,fromTop,4);
 lcd.drawString("O",fromLeft,fromTop+35,4);
 a=0;
// lcd.drawRect(fromLeft-space,fromTop-space,164,32,TFT_RED);
 lcd.drawSmoothRoundRect(fromLeft-space,fromTop-space,5,5,161,32,TFT_RED,TFT_BLACK);
 while (true) {
  
  if(digitalRead(0)==0)
  {
//    lcd.drawRect(fromLeft-space,fromTop-space+(35*a),164,32,TFT_BLACK);
    lcd.drawSmoothRoundRect(fromLeft-space,fromTop-space+(35*a),5,5,161,32,TFT_BLACK,TFT_BLACK);
    a=a+1;
    if(a>1) a=0;
//    lcd.drawRect(fromLeft-space,fromTop-space+(35*a),164,32,TFT_RED);
    lcd.drawSmoothRoundRect(fromLeft-space,fromTop-space+(35*a),5,5,161,32,TFT_RED,TFT_BLACK);
    delay(300);
  }
  if(digitalRead(14)==0)
  {
    lcd.setTextColor(TFT_RED);
    if (a==0) {
      lcd.drawString("X",fromLeft,fromTop + (35*a),4);
      jogo.player='X';      
      jogo.computer='O';
    } else {
      lcd.drawString("O",fromLeft,fromTop + (35*a),4);
      jogo.player='O';
      jogo.computer='X';
    }
    delay(300);
    break;
  }
 }
  player1=true; //modo 2 jogadores
 
 //Incicialização da grelha jogo
 playini();
}

bool win() {
  int win_states[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
        for (int i = 0; i < 8; i++) {
            bool win = true;
            int first_r = win_states[i][0]/3, first_c = win_states[i][0] % 3;
            for (int j = 0; j < 3; j++) {
                int r = win_states[i][j]/3, c = win_states[i][j] % 3;
                if (jogo.grid[first_r][first_c] == ' ' || jogo.grid[first_r][first_c] != jogo.grid[r][c]) {
                    win = false;
                }
            }
            if (win) 
           return true;
        }
        return false;
}

bool tie() {
        if (win())
            return false;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (jogo.grid[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
}

move minimax(bool maximizing_player = true) {
  move best_move;
  if (win()) {
     if (maximizing_player) {
       best_move.score = -1;
     } else {
       best_move.score = 1;
     }
     return best_move;
     } else if (tie()) {
       best_move.score = 0;
       return best_move;
     }
     best_move.score = maximizing_player ? -2 : 2;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (jogo.grid[i][j] == ' ') {
                    jogo.grid[i][j] = maximizing_player ? jogo.computer : jogo.player;
                    move board_state = minimax(!maximizing_player);
                    if (maximizing_player) {
                        if (board_state.score > best_move.score) {
                            best_move.score = board_state.score;
                            best_move.r = i;
                            best_move.c = j;
                        }
                    } else {
                        if (board_state.score < best_move.score) {
                            best_move.score = board_state.score;
                            best_move.r = i;
                            best_move.c = j;
                        }
                    }
                    jogo.grid[i][j] = ' ';
                }
            }
        }
        return best_move;
}

void ganhaJogo ()
{
 Serial.println("ganhaJogo");
 verificaDupla(0,1,2,jogo.computer);
 verificaDupla(3,4,5,jogo.computer);
 verificaDupla(6,7,8,jogo.computer);
 verificaDupla(0,3,6,jogo.computer);
 verificaDupla(1,4,7,jogo.computer);
 verificaDupla(2,5,8,jogo.computer);
 verificaDupla(0,4,8,jogo.computer);
 verificaDupla(2,4,6,jogo.computer);
 if (jogarEm !=9) {
 Serial.print("posicao ataque: ");
 Serial.println(jogarEm);
 }
}

void bloqueiaJogador()
{
 Serial.println("Bloqueia Jogador");
 verificaDupla(0,1,2,jogo.player);
 verificaDupla(3,4,5,jogo.player);
 verificaDupla(6,7,8,jogo.player);
 verificaDupla(0,3,6,jogo.player);
 verificaDupla(1,4,7,jogo.player);
 verificaDupla(2,5,8,jogo.player);
 verificaDupla(0,4,8,jogo.player);
 verificaDupla(2,4,6,jogo.player);
 if (jogarEm !=9) {
 Serial.print("posicao defesa: ");
 Serial.println(jogarEm);
 }
}

void verificaposicao2()
{
 verifDupla2(0,1,2);
 verifDupla2(3,4,5);
 verifDupla2(6,7,8);
 verifDupla2(0,3,6);
 verifDupla2(1,4,7);
 verifDupla2(2,5,8);
 verifDupla2(0,4,8);
 verifDupla2(2,4,6); 
}

void verificaDupla(int posA, int posB, int posC, char value)
{
  if(jogo.grid[int(posA/3)][posA%3]==' ' && jogo.grid[int(posB/3)][posB%3]==value && jogo.grid[int(posC/3)][posC%3]==value) {
    jogarEm=posA;
  }else if(jogo.grid[int(posA/3)][posA%3]==value && jogo.grid[int(posB/3)][posB%3]==' ' && jogo.grid[int(posC/3)][posC%3]==value) {
    jogarEm=posB;
  }else if(jogo.grid[int(posA/3)][posA%3]==value && jogo.grid[int(posB/3)][posB%3]==value && jogo.grid[int(posC/3)][posC%3]==' ') {
    jogarEm=posC;
  }
}

void verifDupla2(int posA, int posB, int posC)
{
  if(jogo.grid[int(posA/3)][posA%3]==jogo.computer && jogo.grid[int(posB/3)][posB%3]==' ' && jogo.grid[int(posC/3)][posC%3]==' ') {
    jogarEm=posB;
  }else if(jogo.grid[int(posB/3)][posB%3]==jogo.computer && jogo.grid[int(posA/3)][posA%3]==' ' && jogo.grid[int(posC/3)][posC%3]==' ') {
    jogarEm=posA;
  }else if(jogo.grid[int(posC/3)][posC%3]==jogo.computer && jogo.grid[int(posB/3)][posB%3]==' ' && jogo.grid[int(posA/3)][posA%3]==' ') {
    jogarEm=posB;
  }
}

void computer_move() {
  if (option==1) {
  move best_move = minimax();
  jogo.grid[best_move.r][best_move.c] = jogo.computer;
  lcd.drawString(String(jogo.computer),14+fromLeft+(best_move.c*boxSize)+(space*best_move.c),12+fromTop+(best_move.r*boxSize)+best_move.r*space,4);
  return;
 } else {
  jogarEm=9;
//  bool cornerplay = false;
  if (option==2) ganhaJogo();
  if ((option!=4)&&(jogarEm==9)) bloqueiaJogador();
  if ((option==2)&&(jogarEm==9)) verificaposicao2();
  if (jogarEm==9) // determina posição aleatória
  {
    int posAlx=int(random(0,9));
    while (jogo.grid[int(posAlx/3)][posAlx%3]!=' '){
    posAlx=int(random(0,9));
    }
    jogo.grid[int(posAlx/3)][posAlx%3]=jogo.computer;
    lcd.drawString(String(jogo.computer),14+fromLeft+((posAlx%3)*boxSize)+(space*(posAlx%3)),12+fromTop+((int(posAlx/3))*boxSize)+(int(posAlx/3))*space,4);
  }
   else {
    jogo.grid[int(jogarEm/3)][jogarEm%3]=jogo.computer;
    lcd.drawString(String(jogo.computer),14+fromLeft+((jogarEm%3)*boxSize)+(space*(jogarEm%3)),12+fromTop+((int(jogarEm/3))*boxSize)+(int(jogarEm/3))*space,4);
   }
  }
}

void tracewinner () {
 for (int i = 0; i < 3; i++) {
   if (jogo.grid[i][0] !=' ' && jogo.grid[i][0] == jogo.grid[i][1] && jogo.grid[i][1] == jogo.grid[i][2]) {
       lcd.drawFastHLine(fromLeft,fromTop+(i*space)+(boxSize*i)+boxSize/2,playGround,TFT_RED);
       lcd.drawFastHLine(fromLeft,fromTop+1+(i*space)+(boxSize*i)+boxSize/2,playGround,TFT_RED);
   }
 }

 for (int j = 0; j < 3; j++) {
   if (jogo.grid[0][j] !=' ' && jogo.grid[0][j] == jogo.grid[1][j] && jogo.grid[1][j] == jogo.grid[2][j]) {
      lcd.drawFastVLine(fromLeft+(j*space)+(boxSize*j)+boxSize/2,fromTop,playGround,TFT_RED);
      lcd.drawFastVLine(fromLeft+1+(j*space)+(boxSize*j)+boxSize/2,fromTop,playGround,TFT_RED);
   }
 }
 
 if (jogo.grid[0][0] !=' ' && jogo.grid[0][0] == jogo.grid[1][1] && jogo.grid[1][1] == jogo.grid[2][2]) {
    lcd.drawLine(fromLeft,fromTop,fromLeft+playGround, fromTop+playGround,TFT_RED);
}
if (jogo.grid[0][2] !=' ' && jogo.grid[0][2] == jogo.grid[1][1] && jogo.grid[1][1] == jogo.grid[2][0]) {
   lcd.drawLine(fromLeft+playGround,fromTop,fromLeft, fromTop+playGround,TFT_RED);
}
}

 void iniGame(char winner)
 {
  Serial.println("iniGame");
  delay(1000);
  lcd.fillScreen(TFT_BLACK);
  lcd.setTextColor(TFT_RED);
  lcd.drawString("GAME OVER",10,17,4);
  lcd.drawWedgeLine(fromLeft-space,50,161,50,3,3,c1,TFT_BLACK);
//lcd.fillRect(fromLeft-5,fromTop-5,playGround+10,playGround+10,TFT_BLACK);

if (winner==jogo.player) {
  lcd.setTextColor(TFT_YELLOW);
  if (option==5 && !player1) lcd.drawString("Play 1 win",15,100,4);
  else lcd.drawString("YOU WIN :(",20,160,4);
  delay(2000);
  lcd.fillRect(fromLeft-5,fromTop-5,playGround+10,playGround+10,TFT_BLACK);
} else if (winner==jogo.computer) {
  lcd.setTextColor(TFT_YELLOW);
  if (option==5 && player1) lcd.drawString("Play 2 win",15,100,4);
  else lcd.drawString("I WIN !!! :)",20,160,4);
  delay(2000);
  lcd.fillRect(fromLeft-5,fromTop-5,playGround+10,playGround+10,TFT_BLACK);
} else {
  lcd.setTextColor(TFT_YELLOW);
  lcd.drawString("Tie...",20,160,4);
  delay(2000);
  lcd.fillRect(fromLeft-5,fromTop-5,playGround+10,playGround+10,TFT_BLACK);
}

menuini();
}
 
void loop() {

if(digitalRead(0)==0)
  {
//  lcd.drawRect((fromLeft+(a*boxSize)+(a*space)),(fromTop+(b*boxSize)+(b*space)),boxSize,boxSize,TFT_BLACK);  
  lcd.drawSmoothRoundRect((fromLeft+(a*boxSize)+(a*space)),(fromTop+(b*boxSize)+(b*space)),3,3,boxSize,boxSize,TFT_BLACK,TFT_BLACK);
  a=a+1;
  if(a>2)
      {
      a=0;
      b++;
      }
  if(b>2)
  b=0;
 // lcd.drawRect((fromLeft+(a*boxSize)+(a*space)),(fromTop+(b*boxSize)+(b*space)),boxSize,boxSize,TFT_RED);  
  lcd.drawSmoothRoundRect((fromLeft+(a*boxSize)+(a*space)),(fromTop+(b*boxSize)+(b*space)),3,3,boxSize,boxSize,TFT_RED,TFT_BLACK);
 
  delay(300);
  }

  if(digitalRead(14)==0)
  {
    if(jogo.grid[b][a]==' ')
    {
      if (player1) {
    lcd.drawString(String(jogo.player),14+fromLeft+(a*boxSize)+(space*a),12+fromTop+(b*boxSize)+b*space,4);
    jogo.grid[b][a]=jogo.player;
    if (option==5) player1=false;
      } else {
        lcd.drawString(String(jogo.computer),14+fromLeft+(a*boxSize)+(space*a),12+fromTop+(b*boxSize)+b*space,4); 
        jogo.grid[b][a]=jogo.computer;
        player1=true;
      }
    if (win()) {
      tracewinner();
      Serial.println("Player wins!");
      winplayer = true;
        if (option==5 && !player1) iniGame(jogo.player);
        else if (option==5 && player1) iniGame(jogo.computer);
        else iniGame(jogo.player);
    } else if (tie()) {
      winplayer = true;
      Serial.println("Empate...");
      iniGame(' ');
    }
    
    if (option!=5 && !winplayer)
    {
      Serial.println("O computador está a jogar...");
      computer_move();
      if (win()) {
        tracewinner();
        Serial.println("Computer wins!");
        iniGame(jogo.computer);
      } else if (tie()) {
        Serial.println("Empate...");
        iniGame(' ');
      }
    }
    delay(300);
    winplayer = false;
   }
    
 }
}
