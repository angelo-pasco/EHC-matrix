#include <FastLED.h>
#include <LEDMatrix.h>

#define DATA_PIN 3 
#define COLOR_ORDER GRB
#define CHIPSET WS2812B

#define MATRIX_WIDTH 10
#define MATRIX_HEIGHT 10
#define MATRIX_TYPE HORIZONTAL_ZIGZAG_MATRIX

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

enum Direction { UP, DOWN, LEFT, RIGHT };
Direction dir = LEFT;
int snake[100] = {4,3,2,1,0}; //snake's initial location
int snake_length = 1;         //snake's initial length

const int leftButton = 4, rightButton = 5, upButton = 6, downButton = 7;
int left_state = 0, right_state = 0, up_state = 0, down_state = 0;
bool start = false;
int food = 69;
long randFoodNum;


void setup() {
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size());
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  Serial.begin(9600);
  randFoodNum = random(0,99);
}  

void loop() {
  //randFoodNum = random(0,99);
  
  leds(randFoodNum) = CRGB::Red;
  while (!start) {
    snake_length = 1;
    snake[0] = 4;
    snake[1] = 3;
    snake[2] = 2;
    snake[3] = 1;
    snake[4] = 0;
    left_state = digitalRead(leftButton);
    right_state = digitalRead(rightButton);
    up_state = digitalRead(upButton);
    down_state = digitalRead(downButton);
    if (left_state == LOW){
      dir = LEFT;
      start = true;
    }
    else if (right_state == LOW){
      dir = RIGHT;
      start = true;
    }
    else if (up_state == LOW){
      dir = UP;
      start = true;
    }
    else if (down_state == LOW){
      dir = DOWN;
      start = true;
    }
    
    leds(snake[0]) = CRGB::Blue;
    FastLED.show();
    delay(100);
    leds(snake[0]) = CRGB::Black;
    FastLED.show();
    delay(100);
    
  }
    if (snake[0] > 99){
      start = false;
    }
    else if (snake[0] < 0){
      start = false;
    }
    else if ((snake[0] % 10 == 0) && (dir == LEFT)){
      start = false;
    }
    else if ((snake[0] % 10 == 9) && (dir == RIGHT)){
      start = false;
    }
    left_state = digitalRead(leftButton);
    right_state = digitalRead(rightButton);
    up_state = digitalRead(upButton);
    down_state = digitalRead(downButton);
    
    for (int i = (sizeof(snake)/sizeof(int)) - 1; i > 0; i--){ 
      snake[i] = snake[i-1];
    }

    if ((left_state == LOW) && (dir != RIGHT)){
      dir = LEFT;
    }
    else if ((right_state == LOW) && (dir != LEFT)){
      dir = RIGHT;
    }
    else if ((up_state == LOW) && (dir != DOWN)){
      dir = UP;
    }
    else if ((down_state == LOW) && (dir != UP)){
      dir = DOWN;
    }
    if (snake[0] == randFoodNum){
      snake_length++;
      randFoodNum = random(0,99);
      for (int i = (sizeof(snake)/sizeof(int)) - 1; i > 0; i--){ 
      if (randFoodNum == snake[i]){
        randFoodNum = random(0,99);
      }
    }
    }
    switch(dir){
      case UP:
        snake[0] = snake[0] + 10;
        break;
      case DOWN:
        snake[0] = snake[0] - 10;
        break;
      case LEFT:
        snake[0] = snake[0] + 1;
        break;
      case RIGHT:
        snake[0] = snake[0] - 1;
        break;
    }
    Serial.print(snake[0], DEC);
    for (int i = 0; i < snake_length ; i++)
    {
      leds(snake[i]) = CRGB::Pink;
    }
    
    LEDS.show();
    delay(200);
    clear_leds();

 
}

void clear_leds()
{
  for (int i = 0; i < 100; i++)
  {
    leds(i) = CRGB::Black;
  }
}
