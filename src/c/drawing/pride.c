#include <pebble.h>

// definitions of each flag's hex code variables
const int clear[] = {0x000000};
const int pride[] = {0xFF0000, 0xFFAA00, 0xFFFF00, 0x00FF00, 0x0000FF, 0xAA00AA};
const int trans[] = {0x00AAFF, 0xFF55FF, 0xFFFFFF, 0xFF55FF, 0x00AAFF};
const int bisexual[] = {0xAA0055, 0xAA0055, 0xAA55AA, 0x0000FF, 0x0000FF};
const int lesbian[] = {0xFF0000, 0xFF5500, 0xFFAA00, 0xFFFFFF, 0xAA55AA, 0xAA00AA, 0xAA0055};
const int pansexual[] = {0xFF00FF, 0xFFFF00, 0x00AAFF};
const int asexual[] = {0x000000, 0xAAAAAA, 0xFFFFFF, 0xAA00AA};
const int nonbinary[] = {0xFFFF55, 0xFFFFFF, 0xAA55AA, 0x000000};

int *flag_colors[] = {clear, pride, trans, bisexual, lesbian, pansexual, asexual, nonbinary};
int num_stripes[] = {0, 6, 5, 5, 7, 3, 4, 4};

// DRAW FLAG FUNCTION
static void draw_flag(int segments, int colors[], GContext *ctx) {
    // setting bounds for main window's layer to draw flag for ENTIRE SCREEN
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    // height and width of each bar in pixels
    int bar_height, bar_width;

    switch (settings.rot_flag) {
        default:
            bar_height = bounds.size.h / segments + (bounds.size.h % segments != 0);
            bar_width = bounds.size.w;
            break;
        case 1:
            bar_height = bounds.size.h;
            bar_width = -1 * bounds.size.w / segments - (bounds.size.w % segments != 0);
            break;
        case 2:
            bar_height = -1 * bounds.size.h / segments - (-1 * bounds.size.h % segments != 0);
            bar_width = bounds.size.w;
            break;
        case 3:
            bar_height = bounds.size.h;
            bar_width = bounds.size.w / segments + (bounds.size.w % segments != 0);
    }

    for (int i = 0; i < segments; i++) {
        GRect flag_stripe;

        switch (settings.rot_flag) {
            default:
                flag_stripe = GRect(0, h * i, w, h);
                break;
            case 1:
                flag_stripe = GRect(bounds.size.w + (w * i), 0, w, h);
                break;
            case 2:
                flag_stripe = GRect(0, bounds.size.h + (h * i), w, h);
                break;
            case 3:
                flag_stripe = GRect(w * i, 0, w, h);
                break;
        }

        graphics_context_set_fill_color(ctx, GColorFromHEX(colors[i]));
        graphics_fill_rect(ctx, flag_stripe, 0, GCornerNone);
    }
}