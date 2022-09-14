#pragma once

// updating and redrawing time specific things
void update_time();

// update procs for various layers
void draw_flag_update_proc(Layer *layer, GContext *ctx);
void draw_dots_bg_update_proc(Layer *layer, GContext *ctx);
void draw_analog_time_update_proc(Layer *layer, GContext *ctx);
void draw_digital_time_update_proc(Layer *layer, GContext *ctx);