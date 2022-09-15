#include <pebble.h>
#include "drawing.h"
#include "../main.h"

// int and char declarations for time values and format
static int hour, min;
static char center_time[] = "hh:mm";

// integer function that returns an int if true or false
    // detects if the actual screen height is the same as the unobstructed screen height
static int if_quickview_else(int if_no, int if_yes) {
    if (layer_get_unobstructed_bounds(window_get_root_layer(main_window)).size.h == layer_get_bounds(window_get_root_layer(main_window)).size.h) {
        return if_no;
    } else {
        return if_yes;
    }
}

// updates the time and gets values from localtime
void update_time() {
    // get a tm structure
    time_t temp = time(NULL);
    struct tm *t = localtime(&temp);

    // string from time
    strftime(center_time, sizeof(center_time), clock_is_24h_style() ? "%H:%M" : "%I:%M", t);

    // hour and min variables being set to the values of the "t" struct for each unit
    hour = t->tm_hour % 12;
    min = t->tm_min;
}

// draws the background circle and the dots
static void draw_dots_bg(GContext *ctx, int radius) {
    // set bounds rectangle and center dot point
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));
    GPoint center = grect_center_point(&bounds);

    // fill background2 circle (circle behind dots)
    graphics_context_set_fill_color(ctx, settings.bg_color2);
    graphics_fill_circle(ctx, center, radius + if_quickview_else(10, 6));

    // set fill color for dots
    graphics_context_set_fill_color(ctx, settings.main_color);

    // actually draw the dots
    for (int i = 0; i < settings.num_hour_dots; i++) {
        int angle = TRIG_MAX_ANGLE * i / settings.num_hour_dots;

        GPoint dot = {
            .x = center.x + sin_lookup(angle) * radius / TRIG_MAX_RATIO,
            .y = center.y - cos_lookup(angle) * radius / TRIG_MAX_RATIO
        };

        graphics_fill_circle(ctx, dot, settings.dot_size);
    }
}

// drawing the hour dot
static void draw_hour_dot(GContext *ctx, int radius) {
    // set bounds rectangle and center dot point
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));
    GPoint center = grect_center_point(&bounds);

    // set an "angle" integer to the correct value for the current hour
    int angle = TRIG_MAX_ANGLE * hour / 12;

    // set coords of the dot according to the angle
    GPoint dot = {
        .x = center.x + sin_lookup(angle) * radius / TRIG_MAX_RATIO,
        .y = center.y - cos_lookup(angle) * radius / TRIG_MAX_RATIO
    };

    // fill in the actual dot
    graphics_context_set_fill_color(ctx, settings.accent_color);
    graphics_fill_circle(ctx, dot, settings.dot_size);
}

// drawing the minute hand
static void draw_min_hand(GContext *ctx, int length) {
    // set bounds rectangle and center dot point
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));
    GPoint center = grect_center_point(&bounds);

    // set an "angle" integer to the correct value for the current minute
    int angle = TRIG_MAX_ANGLE * min / 60;

    // set coords of the end point dot according to the angle
    GPoint end_point = {
        .x = center.x + sin_lookup(angle) * length / TRIG_MAX_RATIO,
        .y = center.y - cos_lookup(angle) * length / TRIG_MAX_RATIO};

    // draw the line with point one being the center and point two being the end point according to the minute
    graphics_context_set_stroke_color(ctx, settings.accent_color);
    graphics_context_set_stroke_width(ctx, settings.min_hand_size);
    graphics_draw_line(ctx, center, end_point);

    // draw a smaller circle to cut off the center and make room for the digital time
    graphics_context_set_fill_color(ctx, settings.bg_color2);
    graphics_fill_circle(ctx, center, 30);
}

// drawing the digital time onscreen
static void draw_digital_time(GContext *ctx) {
    // set bounds rectangle and center dot point
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    // height of the box
    int height = if_quickview_else(28, 24);

    // set a GRect box that is the bounds of the time
    GRect box = GRect(0, bounds.size.h / 2 - (height / 2 + 4), bounds.size.w, height);

    // set text color
    graphics_context_set_text_color(ctx, settings.accent_color);

    // draw text
        // smaller if there's quickview showing
        // larger if the watchface is fullscreen
    if (bounds.size.h == layer_get_bounds(window_get_root_layer(main_window)).size.h) {
        graphics_draw_text(ctx, center_time, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), box, GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, 0);
    } else {
        graphics_draw_text(ctx, center_time, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), box, GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, 0);
    }
}

// drawing background
void draw_dots_bg_update_proc(Layer *layer, GContext *ctx) {
    int dist_from_center = PBL_IF_ROUND_ELSE(60, if_quickview_else(58, 46));

    draw_dots_bg(ctx, dist_from_center);
}

// drawing hour dot and minute hand
void draw_analog_time_update_proc(Layer *layer, GContext *ctx) {
    int dist_from_center = PBL_IF_ROUND_ELSE(60, if_quickview_else(58, 46));

    draw_hour_dot(ctx, dist_from_center);
    draw_min_hand(ctx, dist_from_center);
}

// drawing digital time 
void draw_digital_time_update_proc(Layer *layer, GContext *ctx) {
    draw_digital_time(ctx);
}