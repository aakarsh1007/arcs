/*
 * Drive train subsystem controler.
 */

#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

/*
 * Setup GPIO for drivetrain.
 */
void drive_init();

/*
 * Sets the motor values.
 * Inputs should be between 1 and -1.
 */
void drive_update(float left, float right);

/*
 * Sets GPIO outputs to 0 to stop motors.
 */
void drive_close();

#endif
