#include <Arduino.h>
#include "AsyncServoLib.h"
#include "Config.h"

AsyncServo leftServo;
enum movementDirection {FORWARD, REVERSE};

void inertiaAfterAccelerate(movementDirection direction);
void inertiaAfterStop(movementDirection direction);
void returnServoToIdle();

void setup()
{
    Serial.begin(115200);
    Serial.println("Restart");

    leftServo.Attach(LEFT_SERVO_PIN);
    leftServo.WriteDegree(90);
    delay(2000);

    inertiaAfterAccelerate(FORWARD);
}

void inertiaAfterAccelerate(movementDirection direction)
{
    if (direction == FORWARD) {
        leftServo.MoveDegrees(STEP_DEGREES, INIT_STEP_MS, returnServoToIdle);
    }
    else {
        leftServo.MoveDegrees((IDLE_DEGREES - STEP_DEGREES) * 2, INIT_STEP_MS, returnServoToIdle);
    }
}

void inertiaAfterStop(movementDirection direction)
{
    if (direction == FORWARD) {
        leftServo.MoveDegrees((IDLE_DEGREES - STEP_DEGREES) * 2, INIT_STEP_MS, returnServoToIdle);
    }
    else {
        leftServo.MoveDegrees(STEP_DEGREES, INIT_STEP_MS, returnServoToIdle);
    }
}

void returnServoToIdle()
{
    leftServo.MoveDegrees(IDLE_DEGREES, RETURN_STEP_MS);
}

void loop()
{
    leftServo.Update();
}
