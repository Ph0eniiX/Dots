#include <pebble.h>
#include "drawing.h"
#include "../main.h"

static int hour, min;
static char center_time[] = "hh:mm";

int if_quickview_else(int if_no, int if_yes) {
  if(layer_get_unobstructed_bounds(window_get_root_layer(main_window)).size.h == layer_get_bounds(window_get_root_layer(main_window)).size.h) {
    return if_no;
  } else {
    return if_yes;
  }
}

void update_time() {
  //get a tm structure
  time_t temp = time(NULL);
  struct tm *t = localtime(&temp);

  strftime(center_time, sizeof(center_time), clock_is_24h_style() ? "%H:%M" : "%I:%M", t);

  hour = t->tm_hour % 12;
  min = t->tm_min;
}

static void draw_dots_bg(GContext *ctx, int radius) {
  GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));
  GPoint center = grect_center_point(&bounds);

  graphics_context_set_fill_color(ctx, settings.main_color);

  for(int i = 0; i < settings.num_hour_dots; i++) {
    int angle = TRIG_MAX_ANGLE * i / settings.num_hour_dots;

    GPoint dot = {
      .x = center.x + sin_lookup(angle) * radius / TRIG_MAX_RATIO,
      .y = center.y - cos_lookup(angle) * radius / TRIG_MAX_RATIO
    };

    graphics_fill_circle(ctx, dot, settings.dot_size);
  }
}

static void draw_hour_dot(GContext *ctx, int radius) {
  GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));
  GPoint center = grect_center_point(&bounds);

  graphics_context_set_fill_color(ctx, settings.accent_color);

  int angle = TRIG_MAX_ANGLE * hour / 12;

  GPoint dot = {
    .x = center.x + sin_lookup(angle) * radius / TRIG_MAX_RATIO,
    .y = center.y - cos_lookup(angle) * radius / TRIG_MAX_RATIO
  };

  graphics_fill_circle(ctx, dot, settings.dot_size);
}

static void draw_min_hand(GContext *ctx, int length) {
  GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));
  GPoint center = grect_center_point(&bounds);

  int angle = TRIG_MAX_ANGLE * min / 60;

  GPoint end_point = {
    .x = center.x + sin_lookup(angle) * length / TRIG_MAX_RATIO,
    .y = center.y - cos_lookup(angle) * length / TRIG_MAX_RATIO
  };

  graphics_context_set_stroke_color(ctx, settings.accent_color);
  graphics_context_set_stroke_width(ctx, settings.min_hand_size);
  graphics_draw_line(ctx, center, end_point);
}

void draw_dots_bg_update_proc(Layer *layer, GContext *ctx) {
  int dist_from_center = if_quickview_else(68, 50);

  draw_dots_bg(ctx, dist_from_center);
}

void draw_analog_time_update_proc(Layer *layer, GContext *ctx) {
  int dist_from_center = if_quickview_else(68, 50);

  draw_hour_dot(ctx, dist_from_center);
  draw_min_hand(ctx, dist_from_center);
}