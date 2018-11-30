#include <FastLED.h>
#include <LEDMatrix.h>

#define DATA_PIN 3 
#define COLOR_ORDER GRB
#define CHIPSET WS2812B

#define MATRIX_WIDTH 10
#define MATRIX_HEIGHT 10
#define MATRIX_TYPE HORIZONTAL_ZIGZAG_MATRIX

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

enum Direction { up, down, left, right };
Direction dir = left;
int snake[100] = {4,3,2,1,0};
int snake_length = 5;

const int leftButton = 4;
const int rightButton = 5;
const int upButton = 6;
const int downButton = 7;
int left_state = 0;
int right_state = 0;
int up_state = 0;
int down_state = 0;

void setup() {
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size());
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
}

void loop() {
  for (int frameNo = 0; frameNo < 1000; frameNo++)
  {
    left_state = digitalRead(leftButton);
    right_state = digitalRead(rightButton);
    up_state = digitalRead(upButton);
    down_state = digitalRead(downButton);
    
    for (int i = (sizeof(snake)/sizeof(int)) - 1; i > 0; i--)
    {
      snake[i] = snake[i-1];
    }


    if ((left_state == HIGH) && (dir != right)){
      dir = left;
    }
    else if ((right_state == HIGH) && (dir != left)){
      dir = right;
    }
    else if ((up_state == HIGH) && (dir != down)){
      dir = up;
    }
    else if ((down_state == HIGH) && (dir != up)){
      dir = down;
    }
    /*
    if (snake[0] == 9)
    {
      dir = up;
    }

    if (snake[0] == 99)
    {
      dir = right;
    }

    if (snake[0] == 90)
    {
      dir = down;
    }

    if (snake[0] == 0)
    {
      dir = left;
    }

    */
    move_snake();
    
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

void move_snake()
{
  switch(dir) {
    case up:
      snake[0] = snake[0] + 10;
      break;
    case down:
      snake[0] = snake[0] - 10;
      break;
    case left:
      snake[0] = snake[0] + 1;
      break;
    case right:
      snake[0] = snake[0] - 1;
      break;
  }
}
