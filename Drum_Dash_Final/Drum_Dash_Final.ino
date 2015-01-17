#include <MeggyJrSimple.h> // Required code, line 1 of 2.
// Global variables go here
boolean gameOver = false;
int xplayer = 0;
int yplayer = 0;
int xenemies = 7;
int yenemies = random(8);// figure out code for not green
boolean enemyDead = false;
int mountains[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // Create initial array with all zeros.
int SLOPE = 3; // This determines how much the elevation changes between columns.
int MAXHEIGHT = 4; // This determines the maximum height of the mountains.
int movement = 0; //-1 down, 1 up

void setup() // run once, when the sketch starts
{
  MeggyJrSimpleSetup(); // Required code, line 2 of 2.
  Serial.begin(9600);
}




void loop() // run over and over again
{
  if (gameOver == false)
  {
    CheckButtonsPress();
    if (Button_A)
      movement = 1;
    jump();
    Serial.print(xplayer);
    Serial.print(" ");
    Serial.println(yplayer);
    drawmountain();
    UpdateMountains();
    if (ReadPx(xplayer+1,yplayer) == Green)
      gameOver = true;
    DrawPx(xplayer,yplayer,Blue); // Draws player
    DrawEnemy();
    UpdateEnemy();
  //  shift(); //Cole Damon helped with how shift code works
    DisplaySlate();
    delay(300);
    ClearSlate();
  }
  else
  {
    deathScreen();  
    DisplaySlate();
    delay(300);
    ClearSlate();
    CheckButtonsPress();
    if (Button_A)
    { 
      gameOver = false;
      xplayer = 0;
      yplayer = 0;
      for (int i = 0; i < 8; i++)
      {
        mountains[i] = 0;
      }
      spawn();
    }
  }
}


void spawn()
{
  while (ReadPx(xenemies,yenemies) != 0 && ReadPx(xenemies,yenemies) != Green)
  {
    xenemies = 7;
    yenemies = random(8);
  }
  enemyDead = false;
}

void drawmountain()//from Mr. Kiang
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < mountains[i]; j++)
    {
      DrawPx(i,j,Green);
    }
  }
}

void UpdateMountains()
{
  for (int i = 0; i < 7; i++) // copy everything to the right
  {
    mountains[i] = mountains[i+1];
  }
  // look at the last amount and create a new slope no more than two high.
  int lastHeight = mountains[7];
  int newHeight = random(SLOPE); // generate an elevation change
  if (random(10) > 4) // Half the time
    mountains[7] += newHeight; // add
  else
    mountains[7] -= newHeight; // or subtract
if (mountains[7] > MAXHEIGHT) // correct for out of bounds errors
mountains[7] = MAXHEIGHT;
if (mountains[7] < 0)
mountains[7] = 0;
}

void jump()
{
  if (movement > 0) //jumping and gravity from Mr. Kiang
  {
    if (movement < 3) {
      yplayer++;//unsure of code
      movement++;
    }
    else
      movement = -1;
  }

  if (movement < 0)//falling
  {
    if (ReadPx (xplayer, yplayer-1) != Green)
    {
      if (yplayer > 0)
        yplayer--;
    }
    else
    {
      gameOver = true;
      movement = 0;
    }
  }
}

void deathScreen()
{
  for (int i = 0; i < 8; i++)
  {
    DrawPx(i,i,Red);
  }
  
  for (int i = 0; i < 8; i++)
  {
    DrawPx(i, 7-i, Red); 
  }                                                                                       
}

void DrawEnemy()
{
      if (enemyDead == false)
      DrawPx(xenemies,yenemies,Red);
    else
      spawn();
}

void UpdateEnemy()
{
  if (xenemies > 0)
    xenemies--;
   else 
     enemyDead = true;
}

