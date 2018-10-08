#pragma once

#include <API.h>

#define RED true //Should be used if the robot is on the red alliance.
#define BLUE false //Should be used if the robot is on the blue alliance.
#define TOP true //Indicates the robot is on the "top" starting tile which is arbitrarly chosen.
#define BOTTOM false //Indicates the robot is on the "bottom" starting tile which is arbitrarly chosen.

void initGameState(bool colour, bool end); //If you use the macros with this method it makes sense with natural language.

bool isStartRed(); //If the starting side is red, this is true. Otherwise it's false.
bool isStartBlue(); //If the starting side is blue, this is true. Otherwise it's false.

bool isStartTop(); //If we are starting at the top, this is true. Otherwise it's false.
bool isStartBottom(); //If we are starting at the bottom, this is true. Otherwise, it's false.
