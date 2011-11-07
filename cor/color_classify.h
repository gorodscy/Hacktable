//
//  color_classify.h
//  color_classify_cmd
//
//  Created by Fernando Gorodscy on 11-11-03 based on code from Ricardo Fabbri
//

#ifndef color_classify_cmd_color_classify_h
#define color_classify_cmd_color_classify_h

typedef enum {BLACK, WHITE, RED, GREEN, BLUE, YELLOW, BLUE_GREEN, PURPLE_PINK_LAVENDER, PURPLE_PINK_MAGENTA, GRAY, NONE} color;
typedef enum {UNRELIABLE, GOOD_GUESS, CERTAIN} certainty;

void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );
void color_classify (float red, float green, float blue, color *result, color *second_guess, certainty *sure);
void print_color (color result, color second, certainty certainty_level);

#endif
