#include <pebble.h>
#include "cfg.h"
#include "../main.h"

static void default_settings() {
    settings.main_color = GColorWhite;
    settings.accent_color = GColorVividCerulean;
    settings.bg_color = GColorBlack;
    settings.num_hour_dots = 12;
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