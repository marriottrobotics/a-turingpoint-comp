/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */
#include <API.h>
#include "main.h"
#include "PidCore.h"
#include "GameState.h"
#include "Movement.h"
#include "Sensors.h"

/*
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {
}

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize() {
  imeCount = imeInitializeAll();
  /**Ports are wrong*/
  leftDriveF.mport = 1;
  leftDriveF.sensor = ime(0);
  pid_arr[pid_count++] = &leftDriveF;
  leftDriveB.mport = 2;
  leftDriveB.sensor = ime(1);
  pid_arr[pid_count++] = &leftDriveB;
  rightDriveF.mport = 3;
  rightDriveF.sensor = ime(2);
  pid_arr[pid_count++] = &rightDriveF;
  rightDriveB.mport = 4;
  rightDriveB.sensor = ime(3);
  pid_arr[pid_count++] = &rightDriveB;

  catipult.mport = 5;
  catipult.sensor = ime(4);
  pid_arr[pid_count++] = &catipult;
  loader.mport = 6;
  catipult.sensor = ime(5);
  pid_arr[pid_count++] = &forks;

  tower.mport = 7;
  tower.sensor = ime(6);
  pid_arr[pid_count++] = &tower;
  forks.mport = 8;
  forks.sensor = ime(7);
  pid_arr[pid_count++] = &forks;

  pid_init_all(); //Sets up some default variables. You should then set any specific details.

  loader.min = LOADER_UP;
  loader.max = LOADER_DOWN;

  tower.min = TOWER_DOWN;
  tower.max = TOWER_UP;

  forks.min = FORKS_UP;
  forks.max = FORKS_DROP;

  /*The last thing that should happen, the repeating task starts.*/
  pid_loop = taskRunLoop(pid_run_loops, 10);

  bool colour = false;
  bool side = false;

  if(digitalRead(1)){
    colour = RED;
  }else{
    colour = BLUE;
  }
  if(digitalRead(2)){
    side = TOP;
  }else{
    side = BOTTOM;
  }
  initGameState(colour, side);

  setupMovements(&leftDriveF, &leftDriveB, &rightDriveF, &rightDriveB, IME_TORQUE, 2.5f, 2.5f);
}
