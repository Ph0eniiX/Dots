#include <pebble.h>
#include "main.h"
#include "drawing/drawing.h"
#include "config/cfg.h"
#include "messaging/msg.h"

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
  layer_mark_dirty(analog_time_layer);
}

void update_stuff() {
  window_set_background_color(main_window, settings.bg_color);

  layer_mark_dirty(dots_layer);
  layer_mark_dirty(analog_time_layer);
  layer_mark_dirty(digital_time_layer);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  //self explanatory
  window_set_background_color(main_window, settings.bg_color);

  update_time();

  //creates and sets things for each layer
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
  //destroy all the layers i made before :(
  layer_destroy(dots_layer);
  layer_destroy(analog_time_layer);
  layer_destroy(digital_time_layer);
}

static void init() {
  main_window = window_create();
  
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  init_msg();
  load_settings();

  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_stack_push(main_window, true);

  update_stuff();
}

static void deinit() {
  tick_timer_service_unsubscribe();
  window_destroy(main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
