#pragma once

#include <API.h>

#define IME 0
#define IME_TORQUE 627.2
#define IME_SPEED 392
#define IME_TURBO 261.333
#define QENC 1
#define QENC_ALL 360
#define POT 2

struct Sensor{
    int sensorType;
    int port; //If a quadrature encoder is used this will be the Encoder[] slot
};

extern int sensor_count;
extern struct Sensor sensors[10];

extern int encoder_count;
extern Encoder qencoders[5];

int readValue(struct Sensor *input);

struct Sensor *pot(int port);
struct Sensor *ime(int addr);
struct Sensor *qenc(unsigned char portTop, unsigned char portBottom);
