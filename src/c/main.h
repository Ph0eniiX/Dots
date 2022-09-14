#pragma once
#include <pebble.h>

// window and layer declarations for the entire program
Window *main_window;
Layer *flag_layer, *dots_layer, *analog_time_layer, *digital_time_layer;

// defining all settings variables in a struct for the entire program
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

// updating everything
void update_stuff();

// initalizing a ClaySettings named "settings"
ClaySettings settings;