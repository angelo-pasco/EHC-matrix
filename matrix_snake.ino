#include <FastLED.h>
#include <LEDMatrix.h>

#define DATA_PIN 3 
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define MATRIX_WIDTH 10
#define MATRIX_HEIGHT 10
#define MATRIX_TYPE HORIZONTAL_ZIGZAG_MATRIX

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

enum Direction {UP, DOWN, LEFT, RIGHT};
Direction dir = LEFT;
int snake[100] = {4,3,2,1,0}; //snake's initial location
int snake_length = 5;         //snake's initial length

const int leftButton = 4, rightButton = 5, upButton = 6, downButton = 7;
int left_state = 0, right_state = 0, up_state = 0, down_state = 0;
bool start = false;

void setup(){
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size());
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
}

void loop(){
  while (!start){
    left_state = digitalRead(leftButton);
    right_state = digitalRead(rightButton);
    up_state = digitalRead(upButton);
    down_state = digitalRead(downButton);
    if (left_state == HIGH){
      dir = LEFT;
      start = true;
    }
    else if (right_state = HIGH){
      dir = RIGHT;
      start = true;
    }
    else if (up_state = HIGH){
      dir = UP;
      start = true;
    }
    else if (down_state = HIGH){
      dir = DOWN;
      start = true;
    }
    
    leds(snake[0]) = CRGB::Blue;
    FastLED.show();
    delay(30);
    leds(snake[0]) = CRGB::Black;
    FastLED.show();
    delay(30);
    
  }
  
  for (int frameNo = 0; frameNo < 1000; frameNo++){
    left_state = digitalRead(leftButton);
    right_state = digitalRead(rightButton);
    up_state = digitalRead(upButton);
    down_state = digitalRead(downButton);
    
    for (int i = (sizeof(snake)/sizeof(int)) - 1; i > 0; i--){ 
      snake[i] = snake[i-1];
    }

    if ((left_state == HIGH) && (dir != RIGHT)){
      dir = LEFT;
    }
    else if ((right_state == HIGH) && (dir != LEFT)){
      dir = RIGHT;
    }
    else if ((up_state == HIGH) && (dir != DOWN)){
      dir = UP;
    }
    else if ((down_state == HIGH) && (dir != UP)){
      dir = DOWN;
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
    
    for (int i = 0; i < snake_length ; i++)
    {
      leds(snake[i]) = CRGB::Blue;
    }
    
    LEDS.show();
    delay(200);
    clear_leds();

  }
}

void clear_leds()
{
  for (int i = 0; i < 100; i++)
  {
    leds(i) = CRGB::Black;
  }
}
