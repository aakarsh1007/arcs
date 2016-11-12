#include "common.h"
#include "leds.h"
#include "map.h"
#include "timing.h"
#include <wiringPi.h>
#include "comms.h"
#include <unistd.h>

void init_leds() {
	pinMode(STATUS_LED_PIN, OUTPUT);
	pinMode(COMMS_LED_PIN, OUTPUT);

	digitalWrite(STATUS_LED_PIN, HIGH);
	digitalWrite(COMMS_LED_PIN, HIGH);
	usleep(1000 * 1000);
	digitalWrite(STATUS_LED_PIN, LOW);
	digitalWrite(COMMS_LED_PIN, LOW);
}

void status_led_disabled() {
	digitalWrite(STATUS_LED_PIN,
				 (((microtime() / 1000) % 1000) < 100) ? HIGH : LOW);
}

void status_led_teleop() {
	digitalWrite(STATUS_LED_PIN,
				 (((microtime() / 1000) % 1000) < 500) ? HIGH : LOW);
}

void status_led_auto() {
	int64_t t = ((microtime() / 1000) % 1000);
	digitalWrite(STATUS_LED_PIN,
				 ((t < 200) || (t > 300 && t < 500)) ? HIGH : LOW);
}

void update_comms_led() {
	digitalWrite(COMMS_LED_PIN,
				 (microtime() - last_pack_time()) / 1000 < 100 ? HIGH : LOW);
}

void close_leds() {
	digitalWrite(STATUS_LED_PIN, LOW);
	digitalWrite(COMMS_LED_PIN, LOW);
}
