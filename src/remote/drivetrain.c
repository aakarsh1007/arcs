#include "common.h"
#include "drivetrain.h"
#include <wiringPi.h>
#include <math.h>

bool closed;

inline float clamp(float f) {
	if(f > 1.0) return 1.0;
	if(f < -1.0) return -1.0;
	return f;
}

inline int motor_val(float speed) {
	return (int) (1024.0 * speed);
}

void drive_init() {
	pinMode(RIGHT_MOTOR, PWM_OUTPUT);
	pwmWrite(RIGHT_MOTOR, 0);
	pinMode(LEFT_MOTOR, PWM_OUTPUT);
	pwmWrite(LEFT_MOTOR, 0);
	pinMode(RIGHT_DIR, OUTPUT);
	digitalWrite(RIGHT_DIR, LOW);
	pinMode(LEFT_DIR, OUTPUT);
	digitalWrite(LEFT_DIR, LOW);

	closed = false;
}

void drive_update(float left, float right) {
	if(closed)
		return;

	left = clamp(left);
	right = clamp(right);

	bool ri = right < 0, li = left < 0;

	if(RIGHT_INVERT)
		ri = !ri;
	
	if(LEFT_INVERT)
		li = !li;

	digitalWrite(RIGHT_DIR, ri ? HIGH : LOW);
	digitalWrite(LEFT_DIR, li ? HIGH : LOW);
	pwmWrite(RIGHT_MOTOR, motor_val(fabs(right)));
	pwmWrite(LEFT_MOTOR, motor_val(fabs(left)));
}

void drive_close() {
	pwmWrite(RIGHT_MOTOR, 0);
	pwmWrite(LEFT_MOTOR, 0);
	digitalWrite(RIGHT_DIR, LOW);
	digitalWrite(LEFT_DIR, LOW);
	closed = true;
}
