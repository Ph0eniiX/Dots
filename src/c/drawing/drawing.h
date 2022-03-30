#pragma once

void update_time();

void draw_dots_bg_update_proc(Layer *layer, GContext *ctx);
void draw_analog_time_update_proc(Layer *layer, GContext *ctx);
void draw_digital_time_update_proc(Layer *layer, GContext *ctx);