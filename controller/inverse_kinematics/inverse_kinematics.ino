// This sketch takes vertices of desired locations,
// then convert it into angles and ultimately pulses of the encoders

#include "hline.h"

void setup() {
    Serial.begin(115200);
    for (int i = 0; i < N_VERTICES; i++) {
        print(vertices_x[i]);
        print("\t");
        print(vertices_y[i]);
        print("\t");
        println(time_vector[i]);
    }
}

void loop() {

}