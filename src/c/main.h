#pragma once
#include <pebble.h>

Window *main_window;
Layer *dots_layer, *analog_time_layer, *digital_time_layer;

typedef struct ClaySettings {
    GColor main_color;
    GColor accent_color;
    GColor bg_color;
    int num_hour_dots;
    int dot_size;
    int min_hand_size;
} ClaySettings;

void update_stuff();

ClaySettings settings;