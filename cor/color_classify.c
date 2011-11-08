#include <stdio.h>
#include "color_classify.h"

static void rgb2hsv(float r, float g, float b, float *h, float *s, float *v);

char *color_name[num_colors]  = {
  "black",
  "white",
  "red",
  "green",
  "blue",
  "yellow",
  "blue-green",
  "purple-pink-lavender",
  "purple-pink-magenta",
  "gray",
  "none"
};


char *certainty_name[3] =  {
  "unreliable",
  "good-guess",
  "certain"
};

void 
color_classify (
  float red,
  float green,
  float blue,
  color *result,
  color *second_guess,
  certainty *certainty_level)
{
    float hue;
    float sat;
    float val;
    
    *certainty_level = CERTAIN;
    *result = NONE;
    *second_guess = NONE;
    
    rgb2hsv(red, green, blue, &hue, &sat, &val);
    hue *= 360;

    //fprintf(stderr, "%g, %g, %g\n", hue, sat, val);
    
    if (val < 0.3) {
        if (sat > 0.3 && val > 0.2) {
            *second_guess = BLACK;
            if (sat > 0.6 && (hue >= 65 && hue <= 170)) {
                *result = GREEN;
                return;
            } else if (sat > 0.8) {
                *certainty_level = UNRELIABLE;
            } else {
                *certainty_level = GOOD_GUESS;
            }
            // will proceed below to guessing colors
        } else {
            *result = BLACK;
            return;
        }
    } else if ((val > 0.8 && sat < 0.2) || (val > 0.7 && sat < 0.1) || (val > 0.6 && sat < 0.05)) {
        *result = WHITE;
        if (sat > 0.1) {
            // light baby colors; could be white with offset colorbalance.
            *certainty_level = UNRELIABLE;
            // will proceed below to guessing colors
            *result = NONE;
            *second_guess = WHITE;
        }
        else {
            if (val < 0.7) {
                *second_guess = GRAY;
                *certainty_level = GOOD_GUESS;
            }
            return;
        }
    }
    else if ((val < 0.65 && sat < 0.15) || 
        (val < 0.7 && sat < 0.1) || 
        (val < 0.5 && sat < 0.3 && (hue < 40 && hue > 10))) { // heuristica ~ marrons
        if (val < 0.50) {
            *result = BLACK;
            *certainty_level = GOOD_GUESS;
            if (val > 0.40)
                *second_guess = GRAY;
            return;
        }
        else {
            if (sat < 0.08) {
                *certainty_level = GOOD_GUESS;
                *result = WHITE;
                *second_guess = GRAY;
                return;
            }
            else {
                *certainty_level = UNRELIABLE;
                *second_guess = GRAY;
            }
        }
    }
    
    //RED
    if (hue < 30 || hue > 330) {
        if (hue > 10 && hue <= 30 && sat < 0.4) {
            if (hue > 20) { 
                *result = YELLOW;
                *certainty_level = GOOD_GUESS;
                if (val < 0.7) {
                    *second_guess = GRAY;
                }
            }
            else { 
                *result = RED;
                *certainty_level = UNRELIABLE;
                if (val < 0.7) {
                    *second_guess = GRAY;
                }
            }
        }
        else {
            *result = RED;
            if ((sat < 0.3 && val < 0.6) || (sat < 0.4 && val < 0.35)) {
                if (*certainty_level == CERTAIN) {
                    *certainty_level = GOOD_GUESS;
                }
            }
        }
    }
    // GREEN
    else if (hue > 80 && hue < 170) {
        *result = GREEN;
        if (sat < 0.2) {
            if (*certainty_level == CERTAIN) {
                *certainty_level = GOOD_GUESS;
            }
        }
        if (hue > 160 && (sat < 0.6 || val > 0.6)) {
            *certainty_level = UNRELIABLE;
            *second_guess = BLUE;
        }
    }
    // BLUE
    else if (hue > 185 && hue < 270) {
        if (sat < 0.3) { 
            if (*certainty_level == CERTAIN) {
                *certainty_level = GOOD_GUESS;
            }
            if (val > 0.75) {
                *result = WHITE;
                *second_guess= BLUE;
                if (*certainty_level == CERTAIN) {
                    *certainty_level = GOOD_GUESS;
                }
            }
            else {
                *result = BLUE;
                if (val < 0.6) {
                    *second_guess = GRAY;
                }
                else {
                    *second_guess = WHITE;
                }
            }
        }
        else {
            *result = BLUE;
        }
    }
    // remaining YELLOW + OTHER cases
    else {
        if (sat < 0.5) {
            *certainty_level = UNRELIABLE;
        }
        // in the real system you just discard this estimate and use the previous
        // estimate (e.g. previous frame) at this point
        if (hue >= 30 && hue <= 80) {
            if (hue >= 70 && val <= 70) {
                *result = GREEN;
            }
            else {
                *result = YELLOW;
            }
        }
        else {
            if (*certainty_level == CERTAIN) {
                *certainty_level = GOOD_GUESS;
            }
            if (hue >= 150 && hue <= 185) {
                // hard test near cyan and put a secondary label.
                if (hue >= 180) {
                    *result = BLUE;
                }
                else if (hue < 170) {
                    *result = GREEN;
                    *second_guess = BLUE;
                }
                else {
                    *result = BLUE;
                    *second_guess = GREEN;
                }
            }
            else if (hue >= 270 && hue <= 330) {
                // hard test near magenta and put a secondary label.
                if (hue < 280) {
                    *result = BLUE;
                    if (*second_guess == NONE) {
                        *second_guess = PURPLE_PINK_LAVENDER;
                    }
                }
                else {
                    *result = RED;
                    if (*second_guess == NONE) {
                        *second_guess = PURPLE_PINK_MAGENTA;
                    }
                }
            }
        }
    }
    return;
}

// Code from AnImaL animal.sf.net
// 0 <= r, g, b, h, s, v <= 1
void 
rgb2hsv(float r, float g, float b, float *h, float *s, float *v)
{
   float max, min, delta;

   if (r > g) {
      max = r;
      min = g;
   } else  {
      max = g;
      min = r;
   }

   if (max < b) 
      max = b;
   else if (min > b)
      min = b;
    
   delta = max - min;

   *v = max;
   if (max != 0.0)
     *s = delta / max;
   else
     *s = 0.0;

   if (*s == 0.0) *h = -1;
   else {
     if (r == max)
       *h = (g - b) / delta;
     else if (g == max)
       *h = 2 + (b - r) / delta;
     else if (b == max)
       *h = 4 + (r - g) / delta;
     *h *= 60.0;
     if (*h < 0) *h += 360.0;
     *h /= 360.0;
   }
}



void 
print_color (color result, color second, certainty certainty_level) 
{
  assert(result < num_colors);
  printf("%s ", color_name[result]);

  assert(second < num_colors);
  printf("%s ", color_name[second]);
    
  assert(certainty_level < 3);
  printf("%s\n", certainty_name[certainty_level]);
}
