#include <pebble.h>
#include "main.h"
#include "config/cfg.h"
#include "drawing/drawing.h"
#include "messaging/msg.h"

// updates everything universally across program
void update_stuff() {
    window_set_background_color(main_window, settings.bg_color);

    // layer_mark_dirty updates the layer and draws it again
    layer_mark_dirty(dots_layer);
    layer_mark_dirty(analog_time_layer);
    layer_mark_dirty(digital_time_layer);
    layer_mark_dirty(flag_layer);
}

// tick handler, calculates and updates time
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    update_time();
    layer_mark_dirty(analog_time_layer);
}

// loads main window and initializes various layers
static void main_window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    window_set_background_color(main_window, settings.bg_color);

    // update time at beginning of window loading
    update_time();

    // creates and sets things for each layer
    // layer_set_update_proc allows layer_mark_dirty to work
    // layer_add_child actually allows the layer to be shown on the main layer (it makes a hierarchy)
    flag_layer = layer_create(bounds);
    layer_set_update_proc(flag_layer, draw_flag_update_proc);
    layer_add_child(window_layer, flag_layer);

    dots_layer = layer_create(bounds);
    layer_set_update_proc(dots_layer, draw_dots_bg_update_proc);
    layer_add_child(window_layer, dots_layer);

    analog_time_layer = layer_create(bounds);
    layer_set_update_proc(analog_time_layer, draw_analog_time_update_proc);
    layer_add_child(window_layer, analog_time_layer);

    digital_time_layer = layer_create(bounds);
    layer_set_update_proc(digital_time_layer, draw_digital_time_update_proc);
    layer_add_child(window_layer, digital_time_layer);
}

static void main_window_unload(Window *window) {
    // destroy all the layers i made before :(
    layer_destroy(dots_layer);
    layer_destroy(analog_time_layer);
    layer_destroy(digital_time_layer);
}

// start everything up
static void init() {
    // create window
    main_window = window_create();

    // subscribe to tick timer service, MINUTE_UNIT is the primary unit
    // set to SECOND_UNIT to use more battery but also be able to use seconds
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

    // initialize mesasging and load settings saved in persistent storage
    init_msg();
    load_settings();

    // set the load and unload functions for the main window
    window_set_window_handlers(main_window, (WindowHandlers){
        .load = main_window_load,
        .unload = main_window_unload
    });

    // ESSENTIAL: actually push the layer/window stack to the device upon loading
    window_stack_push(main_window, true);

    // update everything after pushing stack to screen
    update_stuff();
}

// shut everything down
static void deinit() {
    tick_timer_service_unsubscribe();
    window_destroy(main_window);
}

// MAIN PROGRAM METHOD
// initializes, does the entire app event loop, then deinitializes
int main(void) {
    init();
    app_event_loop();
    deinit();
}
