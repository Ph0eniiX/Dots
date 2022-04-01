#pragma once
#include <pebble.h>

Window *main_window;
Layer *flag_layer, *dots_layer, *analog_time_layer, *digital_time_layer;

typedef struct ClaySettings {
    //customizable
    GColor main_color;
    GColor accent_color;
    GColor bg_color;
    GColor bg_color2;
    int num_hour_dots;
    int num_flag;
    int rot_flag;

    //not customizable    
    int dot_size;
    int min_hand_size;
} ClaySettings;

void update_stuff();

ClaySettings settings;