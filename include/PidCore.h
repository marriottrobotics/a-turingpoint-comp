#pragma once

#include <API.h>
#include "Sensors.h"

#define LIMIT(x, min, max) (((x) <= (max)) ? (((x) >= (min)) ? (x) : (min)) : (max))
#define ABS(x) (((x) >= 0) ? (x) : (-(x)))
#define LOWPASS(x, n) (((ABS((x))) >= (n) || (x) <= (-(n))) ? (true) : (false))
#define SIGN(x) (((x) >= 0) ? (1) : (-1))

#define P_COMPONENT
#define I_COMPONENT
#define D_COMPONENT

//The task for the loop running
extern TaskHandle pid_loop;

struct pid {
  struct Sensor *sensor;
	int mport;
	long mtarget;
	float pgain;

	float isum;
	float igain;
	long ilimit;

    long lastpos;
    float dgain;

	short corrcap;
	bool enable;

	long min, max;
};

bool pid_ontarget(struct pid *p);

void pid_update(struct pid *p);

//The array of pid loops to be used in the update task.
extern struct pid *pid_arr[10];
//The amount of currently registered pid loops.
extern int pid_count;

void pid_init_all();

void pid_run_loops();

short lowpassS(short input, short minimum);

void wait_ontarget(struct pid *p);
