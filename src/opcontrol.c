/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "PidCore.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {
	printf("driver? \n");
	//Disables the driving pid code because we don't use it here.
	leftDriveB.enable = false;
	leftDriveF.enable = false;
	rightDriveB.enable = false;
	rightDriveF.enable = false;
	
	/*forks.enable = true;
	tower.enable = false;
	loader.enable = false;
	catipult.enable = false;*/

	while (1) {
	int sensor = 0;
	imeGet(7, &sensor);
	printf("Forks = %d, Target = %ld \n", sensor, forks.mtarget);
	
		//Perimitive driving:
		short leftDrive = joystickGetAnalog(1, 3);
		leftDrive = LOWPASS(leftDrive, 8);
		leftDrive *= -1;
		short rightDrive = joystickGetAnalog(1, 2);
		rightDrive = LOWPASS(rightDrive, 8);

		motorSet(leftDriveF.mport, leftDrive);
		motorSet(leftDriveB.mport, leftDrive);
		motorSet(rightDriveF.mport, rightDrive);
		motorSet(rightDriveF.mport, rightDrive);
		//End fundemental driving.

		//Tower
		if(joystickGetDigital(1, 6, JOY_UP)){
			tower.mtarget += 10;
		}else if(joystickGetDigital(1, 6, JOY_DOWN)){
			tower.mtarget -= 10;
		}
		//Tower Macro
		if(joystickGetDigital(1, 7, JOY_UP)){
			tower.mtarget = TOWER_UP;
		}else if(joystickGetDigital(1, 7, JOY_DOWN)){
			tower.mtarget = TOWER_DOWN;
		}

		//Forks
		if(joystickGetDigital(1, 8, JOY_UP)){
			forks.mtarget = FORKS_UP;
		}else if(joystickGetDigital(1, 8, JOY_LEFT)){
			forks.mtarget = FORKS_FLAT;
		}else if(joystickGetDigital(1, 8, JOY_DOWN)){
			forks.mtarget = FORKS_DROP;
		}

		//Loader
		if(joystickGetDigital(1, 5, JOY_UP)){
			loader.mtarget += 10;
		}else if(joystickGetDigital(1, 5, JOY_DOWN)){
			loader.mtarget -= 10;
		}
		//Loader Macro
		if(joystickGetDigital(1, 7, JOY_LEFT)){
			loader.mtarget = LOADER_UP;
		}else if(joystickGetDigital(1, 7, JOY_RIGHT)){
			loader.mtarget = LOADER_DOWN;
		}

		//Catipult
		//TODO This is going to be a trick.

		delay(30);
	}
}
