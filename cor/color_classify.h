//
//  color_classify.h
//  color_classify_cmd
//
//  Created by Fernando Gorodscy on 11-11-03 based on code from Ricardo Fabbri
//

#ifndef color_classify_cmd_color_classify_h
#define color_classify_cmd_color_classify_h


typedef enum {
 BLACK = 0,
 WHITE = 1,
 RED   = 2,
 GREEN = 3,
 BLUE  = 4,
 YELLOW = 5,
 BLUE_GREEN = 6,
 PURPLE_PINK_LAVENDER = 7,
 PURPLE_PINK_MAGENTA = 8,
 GRAY = 9,
 NONE = 10} color;
typedef enum {UNRELIABLE = 0,
 GOOD_GUESS = 1,
 CERTAIN = 2} certainty;

void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );
void color_classify (float red, float green, float blue, color *result, color *second_guess, certainty *sure);
void print_color (color result, color second, certainty certainty_level);


#endif
