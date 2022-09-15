#include <pebble.h>
#include "../main.h"

// bluetooth callback function, basically buzzes when BT disconnects
    // just make sure this function is declared in a header somewhere
void bluetooth_callback(bool connected) {
    if(settings.do_bt_buzz == true && !connected) {
        vibes_short_pulse();
    }
}