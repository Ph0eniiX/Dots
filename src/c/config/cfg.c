#include <pebble.h>
#include "cfg.h"
#include "../main.h"

static void default_settings() {
    //part of the config page
    settings.main_color = GColorBlack;
    settings.accent_color = GColorRed;
    settings.bg_color = GColorOxfordBlue;
    settings.bg_color2 = GColorWhite;
    settings.num_hour_dots = 12;
    settings.num_flag = 0;
    settings.rot_flag = 0;

    //not in the config page,
    //i just used this to easily change them in one file
    settings.dot_size = 3;
    settings.min_hand_size = 4;
}

void load_settings() {
    default_settings();
    persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

void save_settings() {
    persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}