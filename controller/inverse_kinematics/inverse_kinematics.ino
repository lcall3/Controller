// This sketch takes vertices of desired locations,
// then convert it into angles and ultimately pulses of the encoders

#include "hline.h"

void setup() {
    Serial.begin(115200);
    for (int i = 0; i < N_VERTICES; i++) {
        Serial.print(vertices_x[i]);
        Serial.print("\t");
        Serial.print(vertices_y[i]);
        Serial.print("\t");
        Serial.println(time_vector[i]);
    }
}

void loop() {

}