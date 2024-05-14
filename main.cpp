#include "mbed.h"
#include "LSM6DSLSensor.h"

#define PI 3.141592654   // Define the value of PI

// Define an I2C interface for the accelerometer
static DevI2C devI2c(PB_11,PB_10);
static LSM6DSLSensor acc_gyro(&devI2c,0xD4,D4,D5); // high address

// Function to compute the pitch angle based on acceleration values
float computeAngle(int x, int y, int z) {

   // Calculate the pitch angle using the x, y, and z acceleration values
    // Pitch angle = arctan(y / sqrt(x^2 + z^2))
    float pitch_rad = atan2(y, sqrt(x * x + z * z));

    // Convert the pitch angle from radians to degrees
    float pitch_deg = pitch_rad * 180.0 / PI;

    return pitch_deg;
}

/* Simple main function */
int main() {
    uint8_t id;
    int32_t axes[3];
    float res=0;
    acc_gyro.init(NULL);
    // Initialize the accelerometer
    acc_gyro.enable_x();
    acc_gyro.enable_g();

    // Print the Mbed OS version and the accelerometer & gyroscope ID
    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while(1) {

        acc_gyro.get_x_axes(axes);
        res = computeAngle(axes[0], axes[1], axes[2]);
        // Print the accelerometer readings and the computed pitch angle
        printf("LSM6DSL: %6d, %6d, %6d, %3.2f\r\n", axes[0], axes[1], axes[2], res);

        // Wait for 2 seconds before the next iteration
        thread_sleep_for(2000);

    }
}

