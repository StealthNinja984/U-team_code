#include "screenSelector.h"

class button
{
private:
  int count;
  bool hidden;
  bool selected;

public:
  int x, y;
  int height;
  int width;
  const char* text;
  int length;
  int howTall;
  bool isPressed;
  button(int X, int Y, int Width, int Height, const char* Text, bool Hidden)
  {
    x = X;
    y = Y;
    height = Height;
    width = Width;
    count = 0;
    text = Text;
    hidden = Hidden;
    selected = false;
  }

  int getCount () { return count; }
  void setCount (int newCount) { count = newCount; }
  
  bool getHidden () { return hidden; }
  void setHidden (bool newValue) { hidden = newValue; }

  bool getSelected () { return selected; }
  void setSelected (bool newValue) { selected = newValue; }

  void textSize ()
  {
    length = Brain.Screen.getStringWidth(text);
    howTall = Brain.Screen.getStringHeight(text);
  }
  
  void draw ()
  {
    if (!selected)
    {
      Brain.Screen.drawRectangle(x, y, width, height, blue);
    }
    else if (selected)
    {
      Brain.Screen.drawRectangle(x, y, width, height, red);
    }
    //Brain.Screen.drawRectangle(x, y, width, height);
    Brain.Screen.printAt(((width / 2) + x) - (length / 2), ((height / 2) + y) + (howTall / 2), text);
  }

  void update() 
  {
    int pressX = Brain.Screen.xPosition();
    int pressY = Brain.Screen.yPosition();

    if (pressX > x && pressX < (x + width) && pressY > y && pressY < (y + height))
    {
      setCount (getCount() + 1);
      isPressed = true;
      setSelected (true);
    }
    else 
    {
      isPressed = false;
      setSelected (false);
    }
    if (!getHidden())
    {
      draw();
    }
    
  }
};

bool auton1 = false;
bool auton2 = false;
bool auton3 = false;
bool auton4 = false;



button button1(0, 0, 240, 120, "auton1", false);
button button2(240, 0, 240, 120, "auton2", false);
button button3(0, 120, 240, 120, "auton3", false);
button button4(240, 120, 240, 120, "auton4", false);

void getTextSize()
{
  button1.textSize();
  button2.textSize();
  button3.textSize();
  button4.textSize();
}

void drawAll()
{
  button1.draw();
  button2.draw();
  button3.draw();
  button4.draw();
  Brain.Screen.printAt(215, 17, "2121U");
}

void updateAll()
{
  Brain.Screen.clearScreen();
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  Brain.Screen.printAt(215, 17, "2131U");
  
    if (button1.getSelected())
    {
      auton1 = true;
      auton2 = false;
      auton3 = false;
      auton4 = false;
    } else if (button2.getSelected())
    {
      auton1 = false;
      auton2 = true;
      auton3 = false;
      auton4 = false;
    } else if (button3.getSelected())
    {
      auton1 = false;
      auton2 = false;
      auton3 = true;
      auton4 = false;
    } else if (button4.getSelected())
    {
      auton1 = false;
      auton2 = false;
      auton3 = false;
      auton4 = true;
    }
}
