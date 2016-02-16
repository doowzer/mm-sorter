#include <Servo.h>

#define SLOT_1  0
#define SLOT_2  30
#define SLOT_3  60
#define SLOT_4  120
#define SLOT_5  150
#define SLOT_6  180

#define COLORS 7
#define RED 1
#define BLUE 2
#define GREEN 3
#define BROWN 4
#define YELLOW 5
#define ORANGE 6

boolean data_available = false;
String command, colors[COLORS];
Servo srv;
int color;


/**
 *
 */
void setup()
{
        command.reserve(8);
        command = "";

        colors[RED] = "RED";
        colors[BLUE] = "BLUE";
        colors[GREEN] = "GREEN";
        colors[BROWN] = "BROWN";
        colors[YELLOW] = "YELLOW";
        colors[ORANGE] = "ORANGE";

        srv.attach(9);

        Serial.begin(9600);
        Serial.println("MMSTARTED");
}

/**
 *
 */
int get_colors()
{
        for (int i = 1; i <= COLORS; i++) {
                if (command.equals(colors[i])) {
                        return i;
                }
        }

        return -1;
}

/**
 *
 */
void serial_event()
{
        while (Serial.available()) {
                char r = (char) Serial.read();
                command += r;

                if (r == '\n') {
                        command.trim();
                        command.toUpperCase();
                        data_available = true;
                }
        }
}

/**
 *
 */
void loop()
{
        serial_event();
        if (data_available) {
                color = get_colors();

                switch (color) {
                case RED:
                        Serial.println("*** RED ***");
                        srv.write(SLOT_1);
                        break;

                case BLUE:
                        Serial.println("*** BLUE ***");
                        srv.write(SLOT_2);
                        break;

                case GREEN:
                        Serial.println("*** GREEN ***");
                        srv.write(SLOT_3);
                        break;

                case BROWN:
                        Serial.println("*** BROWN ***");
                        srv.write(SLOT_4);
                        break;

                case YELLOW:
                        Serial.println("*** YELLOW ***");
                        srv.write(SLOT_5);
                        break;

                case ORANGE:
                        Serial.println("*** ORANGE ***");
                        srv.write(SLOT_6);
                        break;

                default:
                        break;
                }

                command = "";
                data_available = false;

                delay(1000);
                srv.write(90);
        }
}
