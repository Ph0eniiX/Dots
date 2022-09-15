#include <pebble.h>
#include "cfg.h"
#include "../main.h"

// loads these settings when nothing is configured
static void default_settings() {
    // part of the config page
    settings.main_color = GColorBlack;
    settings.accent_color = GColorRed;
    settings.bg_color = GColorOxfordBlue;
    settings.bg_color2 = GColorWhite;
    settings.num_hour_dots = 12;
    settings.do_bt_buzz = true;
    settings.num_flag = 0;
    settings.rot_flag = 0;

    // i just used this to easily change them in one file
    settings.dot_size = 3;
    settings.min_hand_size = 4;
}

// load settings from persistent storage
void load_settings() {
    default_settings();
    persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

// writes settings to persistent storage
void save_settings() {
    persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}