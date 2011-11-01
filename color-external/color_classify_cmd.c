#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float MAX (float a, float b, float c);
float MIN (float a, float b, float c);
void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );


int main (int argc, const char * argv[])
{
    float red = atof (argv[1]);
    float green = atof (argv[2]);
    float blue = atof (argv[3]);
    float hue;
    float sat;
    float val;
    char label[20] = "none";
    char secondary_label[20] = "none";
    char certainty_level[20] = "certain";
    
    RGBtoHSV(red, green, blue, &hue, &sat, &val);
    
    if (val < 0.3) {
        if (sat > 0.3 && val > 0.2) {
            strcpy(secondary_label, "black");
            if (sat > 0.6 && (hue >= 65 && hue <= 170)) {
                strcpy(label, "green");
                printf("%s %s %s\n", label, secondary_label, certainty_level);
                return 0;
            } 
            else if (sat > 0.8) {
                strcpy(certainty_level, "unreliable");
            } 
            else {
                strcpy(certainty_level, "good guess");
            }
            // will proceed below to guessing colors
        }
        else {
            strcpy(label, "black");
        }
    }
    else if ((val > 0.8 && sat < 0.2) || (val > 0.7 && sat < 0.1) || (val > 0.6 && sat < 0.05)) {
        strcpy (label, "white");
        if (sat > 0.1) {
            // light baby colors; could be white with offset colorbalance.
            strcpy(certainty_level, "unreliable"); 
            // will proceed below to guessing colors
            strcpy(label, "none");
            strcpy(secondary_label, "white");
        }
        else {
            if (val < 0.7) {
            strcpy(secondary_label, "gray");
            strcpy(certainty_level, "good guess");
            }
            printf("%s %s %s\n", label, secondary_label, certainty_level);
            return 0;
        }
    }
    else if ((val < 0.65 && sat < 0.15) || (val < 0.7 && sat < 0.1) || (val < 0.5 && sat < 0.3 && (hue < 40 && hue > 10))) { // heuristica ~ marrons
        if (val < 0.50) {
            strcpy(label, "black");
            strcpy(certainty_level, "good guess");
            if (val > 0.40) {
                strcpy(secondary_label, "gray");
            }
            printf("%s %s %s\n", label, secondary_label, certainty_level);
            return 0;
        }
        else {
            if (sat < 0.08) {
                strcpy(certainty_level, "good guess");
                strcpy(label, "white");
                strcpy(secondary_label, "gray");
                printf("%s %s %s\n", label, secondary_label, certainty_level);
                return 0;
            }
            else {
                strcpy(certainty_level, "unreliable");
                strcpy(secondary_label, "gray");
            }
        }
    }
    
    //RED
    if (hue < 30 || hue > 330) {
        if (hue > 10 && hue <= 30 && sat < 0.4) {
            if (hue > 20) { 
                strcpy(label, "yellow");
                strcpy(certainty_level, "good guess");
                if (val < 0.7) {
                    strcpy(secondary_label, "gray");
                }
            }
            else { 
                strcpy(label, "red");
                strcpy(certainty_level, "unreliable");
                if (val < 0.7) {
                    strcpy(secondary_label, "gray");
                }
            }
        }
        else {
            strcpy(label, "red");
            if ((sat < 0.3 && val < 0.6) | (sat < 0.4 & val < 0.35)) {
                if (strcmp(certainty_level, "certain") == 0) {
                    strcpy(certainty_level,  "good guess");
                }
            }
        }
    }
    // GREEN
    else if (hue > 80 && hue < 170) {
        strcpy(label, "green");
        if (sat < 0.2) {
            if (strcmp(certainty_level, "certain") == 0) {
                strcpy(certainty_level, "good guess");
            }
        }
        if (hue > 160 && (sat < 0.6 || val > 0.6)) {
            strcpy(certainty_level, "unreliable");
            strcpy(secondary_label, "blue");
        }
    }
    // BLUE
    else if (hue > 185 && hue < 270) {
        if (sat < 0.3) { 
            if (strcmp(certainty_level, "certain") == 0) {
                strcpy(certainty_level, "good guess");
            }
            if (val > 0.75) {
                strcpy(label, "white");
                strcpy(secondary_label, "blue");
                if (strcmp(certainty_level, "certain") == 0) {
                    strcpy(certainty_level, "good guess");
                }
            }
            else {
                strcpy(label, "blue");
                if (val < 0.6) {
                    strcpy(secondary_label, "gray");
                }
                else {
                    strcpy(secondary_label, "white");
                }
            }
        }
        else {
            strcpy(label, "blue");
        }
    }
    // remaining YELLOW + OTHER cases
    else {
        if (sat < 0.5) {
            strcpy(certainty_level, "unreliable");
        }
        // in the real system you just discard this estimate and use the previous
        // estimate (e.g. previous frame) at this point
        if (hue >= 30 && hue <= 80) {
            if (hue >= 70 && val <= 70) {
                strcpy(label, "green");
            }
            else {
                strcpy(label, "yellow");
            }
        }
        else {
            if (strcmp(certainty_level, "certain") == 0) {
                    strcpy(certainty_level, "good guess");
            }
            if (hue >= 150 && hue <= 185) {
                // hard test near cyan and put a secondary label.
                if (hue >= 180) {
                    strcpy(label, "blue");
                }
                else if (hue < 170) {
                    strcpy(label, "green");
                    strcpy(secondary_label, "blue");
                }
                else {
                    strcpy(label, "blue");
                    strcpy(secondary_label, "green");
                }
            }
            else if (hue >= 270 && hue <= 330) {
                // hard test near magenta and put a secondary label.
                if (hue < 280) {
                    strcpy(label, "blue");
                    if (strcmp(secondary_label, "none") == 0) {
                        strcpy(secondary_label, "purple-pink-lavender");
                    }
                }
                else {
                    strcpy(label, "red");
                    if (strcmp(secondary_label, "none") == 0) {
                        strcpy(secondary_label, "purple-pink-magenta");
                    }
                }
            }
        }
    }
    printf("%s %s %s\n", label, secondary_label, certainty_level);
    return 0;
}

float MAX (float a, float b, float c)
{
    if (a > b) {
        if (a > c) {
            return a;
        } else {
            return c;
        }
    } else if (b > c) {
        return b;
    } else {
        return c;
    }
}

float MIN (float a, float b, float c)
{
    if (a < b) {
        if (a < c) {
            return a;
        } else {
            return c;
        }
    } else if (b < c) {
        return b;
    } else {
        return c;
    }
}

// 0 <= r, g, b, s, v <= 1
// 0 < h < 360
void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v ) 
{
    float min, max, delta;
    min = MIN( r, g, b );
    max = MAX( r, g, b );
    *v = max;
    delta = max - min;
    if( max != 0 )
        *s = delta / max;
    else {
        // r = g = b = 0
        *s = 0;
        *h = -1;
        return;
    }
    if( r == max )
        *h = ( g - b ) / delta;
    else if( g == max )
        *h=2+(b-r)/delta;
    else 
        *h=4+(r-g)/delta; 
    *h *= 60;
    if( *h < 0 )
        *h += 360;
}
