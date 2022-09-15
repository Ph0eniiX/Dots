#include <pebble.h>
#include "msg.h"
#include "../main.h"
#include "../config/cfg.h"

// the handler that handles the recieving of messages from the phone's config page
static void inbox_recieved_handler(DictionaryIterator *iter, void *ctx) {
    // set the tuple to the value of a key (recieved from phone)
        // then set the value of a settings variable to what the tuple was

    // main color
    Tuple *MainColor_t = dict_find(iter, MESSAGE_KEY_MainColorKey);
    if(MainColor_t) {
        settings.main_color = GColorFromHEX(MainColor_t->value->int32);
    }

    // accent color
    Tuple *AccentColor_t = dict_find(iter, MESSAGE_KEY_AccentColorKey);
    if(AccentColor_t) {
        settings.accent_color = GColorFromHEX(AccentColor_t->value->int32);
    }

    // background color
    Tuple *BackgroundColor_t = dict_find(iter, MESSAGE_KEY_BackgroundColorKey);
    if(BackgroundColor_t) {
        settings.bg_color = GColorFromHEX(BackgroundColor_t->value->int32);
    }

    // circle/second background color
    Tuple *BackgroundColor2_t = dict_find(iter, MESSAGE_KEY_BackgroundColor2Key);
    if(BackgroundColor2_t) {
        settings.bg_color2 = GColorFromHEX(BackgroundColor2_t->value->int32);
    }

    Tuple *DoBTBuzz_t = dict_find(iter, MESSAGE_KEY_DoBTBuzzKey);
    if(DoBTBuzz_t) {
        settings.do_bt_buzz = DoBTBuzz_t->value->int32 == 1;
    }

    // number of hour dots
    Tuple *NumHourDot_t = dict_find(iter, MESSAGE_KEY_NumHourDotsKey);
    if(NumHourDot_t) {
        settings.num_hour_dots = atoi(NumHourDot_t->value->cstring);
    }

    // number value of pride flag background
    Tuple *NumFlag_t = dict_find(iter, MESSAGE_KEY_NumFlagKey);
    if(NumFlag_t) {
        settings.num_flag = atoi(NumFlag_t->value->cstring);
    }

    // number value of pride flag rotations
    Tuple *RotFlag_t = dict_find(iter, MESSAGE_KEY_RotFlagKey);
    if(RotFlag_t) {
        settings.rot_flag = atoi(RotFlag_t->value->cstring);
    }

    // save and update all of the settings variables
    save_settings();
    update_stuff();
}

// initializes the messaging connection of phone to watch
void init_msg() {
    app_message_register_inbox_received(inbox_recieved_handler);
    app_message_open(256, 256);
}