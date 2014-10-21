/*
 SNAKE by Vinu Ilangovan
 */


const int LEFT = 0;
const int RIGHT = 18;
const int UP = 1;
const int DOWN = 19;

//initial values
int length = 3; //length of snake
int storage[8][8]; // playing grid
int snake[64][2]; //snake locations
int appleX = 6;
int appleY = 6;
int headX = 3;
int headY = 3;
int snakeDirection = 2;
//0 = left
//1 = right
//2 = up
//3 = down

boolean left = false;
boolean right = false;
boolean up = false;
boolean down = false;

boolean gameover=false;
boolean startNew = true;

int ledX = 30;
int ledY = 30;

int counter;
int level;


//**********************************************************************
//Setup Ports
void setup(){
  //output pins
  for(int indexPin = 2; indexPin <= 13; indexPin++){
    pinMode(indexPin, OUTPUT);
  }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  //input pins
  pinMode(0,INPUT); //left button
  pinMode(1,INPUT); //right button
  pinMode(A4,INPUT); //up button
  pinMode(A5,INPUT); //down button

  gameover=false;
  startNew = true;
}

//**********************************************************************
//Main Game Loop
void loop(){
  //Serial.print("Begin Main Loop");
  //**********************************************************************
  //Initialize Game
  if(startNew) {
    //initialize Snake and Apple
    //clear matrix
    for(int storageY = 0; storageY < 8; storageY++) {
      for(int storageX = 0; storageX < 8; storageX++) {
        storage[storageY][storageX] = 0;
      }
    }

    for(int snakeY = 0; snakeY < 64; snakeY++) {
      for(int snakeX = 0; snakeX < 2; snakeX++) {
        snake[snakeY][snakeX] = 0;
      }
    }

    length = 3; //length of snake
    appleX = 6; //apple position
    appleY = 1;
    storage[appleY][appleX] = 3;

    snake[0][0] = 4; //headY of snake
    snake[0][1] = 2; //headX of snake
    storage[snake[0][0]][snake[0][1]] = 2;

    snake[1][0] = 5; //Y of snake
    snake[1][1] = 2; //X of snake
    storage[snake[1][0]][snake[1][1]] = 1;

    snake[2][0] = 6; //Y of snake
    snake[2][1] = 2; //X of snake
    storage[snake[2][0]][snake[2][1]] = 1;

    snakeDirection = 2;
    level = 50;
    left = false;
    right = false;
    up = false;
    down = false;


    gameover = false;
    startNew = false;
  }



  if(!gameover) {
    //Main Game

    //**********************************************************************
    //Movement of Snake
    int tempY = snake[length - 1][0];
    int tempX = snake[length - 1][1];
    for (int count = length - 1; count > 0; count--) {
      snake[count][0] = snake[count - 1][0]; //Y of snake
      snake[count][1] = snake[count - 1][1]; //X of snake
      storage[snake[count][0]][snake[count][1]] = 1;
    }
    storage[snake[0][0]][snake[0][1]] = 1;

    if(left || snakeDirection == 0) {
      //go left
      if ((snake[0][1] - 1) >= 0) {
        snake[0][1] = snake[0][1] - 1;
      }
      else {
        snake[0][1] = 7;
      }
      snakeDirection = 0;
      left = false;
    }
    else if(right || snakeDirection == 1) {
      //go right
      if ((snake[0][1] + 1) <= 7) {
        snake[0][1] = snake[0][1] + 1;
      }
      else {
        snake[0][1] = 0;
      }
      snakeDirection = 1;
      right = false;
    }
    else if(up || snakeDirection == 2) {
      //go up
      if ((snake[0][0] - 1) >= 0) {
        snake[0][0] = snake[0][0] - 1;
      }
      else {
        snake[0][0] = 7;
      }
      snakeDirection = 2;
      up = false;
    }
    else if(down || snakeDirection == 4) {
      //go down
      if ((snake[0][0] + 1) <= 7) {
        snake[0][0] = snake[0][0] + 1;
      }
      else {
        snake[0][0] = 0;
      }
      snakeDirection = 4;
      down = false;
    }
    storage[snake[0][0]][snake[0][1]] = 2;
    storage[tempY][tempX] = 0;

    //**********************************************************************
    //Collision Detection with Apple
    if(snake[0][0] == appleY && snake[0][1] == appleX) {
      //snake head eat apple
      snake[length][0] = snake[length - 1][0];
      snake[length][1] = snake[length - 1][1];
      storage[snake[length][0]][snake[length][1]] = 1;
      length++;
      
      boolean pass =false;
      while(!pass){
        pass=true;
        
        appleY = random(8);
        appleX = random(8);
       
        for (int count = (length - 1); count > 0; count--) {
          if (appleY == snake[count][0] && appleX == snake[count][1]) {
            pass=false;
          }
        }
        
      }
      level--;
      
      storage[appleY][appleX] = 3;
    }

    //**********************************************************************
    //Collision Detection with Self
    for (int count = (length - 1); count > 0; count--) {
      if (snake[0][0] == snake[count][0] && snake[0][1] == snake[count][1]) {
        gameover = true;
      }
    }

    //**********************************************************************
  }

  //**********************************************************************
  //If Collision is detected with self Then Game Over
  if(gameover) {
    for(int storageY = 0; storageY < 8; storageY++) {
      for(int storageX = 0; storageX < 8; storageX++) {
        storage[storageY][storageX] = 1;
      }
    }

    startNew = true;
  }

  //**********************************************************************
  //**********************************************************************
  //Print Matrix
  while (counter >= 0) {
    for (int indexY = 0; indexY < 8; indexY++) {
      for (int indexX = 0; indexX < 8; indexX++) {


        //**********************************************************************
        //Button Input Read

        if(digitalRead(LEFT) == HIGH && snakeDirection != 0 && snakeDirection != 1) {
          left = true;
          snakeDirection=0;
        }
        else if(digitalRead(RIGHT) == HIGH && snakeDirection != 0 && snakeDirection != 1) {
          right = true;
          snakeDirection=1;
        }
        else if(digitalRead(UP) == HIGH && snakeDirection != 2 && snakeDirection != 3) {
          up = true;
          snakeDirection=2;
        }
        else if(digitalRead(DOWN) == HIGH && snakeDirection != 2 && snakeDirection != 3) {
          down = true;
          snakeDirection=3;
        }

        //**********************************************************************

        if(storage[indexY][indexX] != 0) {
          //Turn on LED

          if(indexY == 0) {
            digitalWrite(17, LOW);
          }
          if(indexY == 1) {
            digitalWrite(16, LOW);
          }
          if(indexY == 2) {
            digitalWrite(15, LOW);
          }
          if(indexY == 3) {
            digitalWrite(14, LOW);
          }
          if(indexY == 4) {
            digitalWrite(13, LOW);
          }
          if(indexY == 5) {
            digitalWrite(12, LOW);
          }
          if(indexY == 6) {
            digitalWrite(11, LOW);
          }
          if(indexY == 7) {
            digitalWrite(10, LOW);
          }
          digitalWrite(indexX + 2, HIGH);

        }
        //Turn off LED
        for(int indexPin = 2; indexPin <= 9; indexPin++){  
          digitalWrite(indexPin, LOW); 
        }
        for(int indexPin=10;indexPin<=17;indexPin++){
          digitalWrite(indexPin,HIGH);
        }
      }
    }
    counter--;
  }
  counter = level;
}

