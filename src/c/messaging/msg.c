#include <pebble.h>
#include "msg.h"
#include "../main.h"
#include "../config/cfg.h"

static void inbox_recieved_handler(DictionaryIterator *iter, void *ctx) {
    //set the tuples (idek what a tuple is i'ma be honest)
    //then sets the value of each tuple to a ClaySettings variable
    Tuple *MainColor_t = dict_find(iter, MESSAGE_KEY_MainColorKey);
    if(MainColor_t) {
        settings.main_color = GColorFromHEX(MainColor_t->value->int32);
    }

    Tuple *AccentColor_t = dict_find(iter, MESSAGE_KEY_AccentColorKey);
    if(AccentColor_t) {
        settings.accent_color = GColorFromHEX(AccentColor_t->value->int32);
    }

    Tuple *BackgroundColor_t = dict_find(iter, MESSAGE_KEY_BackgroundColorKey);
    if(BackgroundColor_t) {
        settings.bg_color = GColorFromHEX(BackgroundColor_t->value->int32);
    }

    //save and update things
    save_settings();
    update_stuff();
}

void init_msg() {
    app_message_register_inbox_received(inbox_recieved_handler);
    app_message_open(256, 256);
}