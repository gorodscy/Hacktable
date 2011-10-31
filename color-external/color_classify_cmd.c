#include <stdio.h>
#include <stdlib.h>

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
    
    RGBtoHSV(red, green, blue, &hue, &sat, &val);
    
    if (val < 0.2 && sat < 0.8) {
        printf("Black\n");
        return 0;
    } else if (val > 0.8 && sat < 0.1) {
        printf("White\n");
        return 0;
    }
    
    // At this point we have
    // val > 0.2 | (val < 0.8 | sat > 0.1)
    
    if (hue < 30 || hue > 330) {
        printf("Red\n");
    } else if (hue > 90 && hue < 150) {
        printf("Green\n");
    } else if (hue > 185 && hue < 270) {
        printf("Blue\n");
    } else { // disp 'unreliable color...';
        printf("Warning: Unreliable!    -----> ");
        // in the real system you just discard this estimate and use the previous
        // estimate (e.g. previous frame) at this point
        if (hue >= 30 && hue <= 90) {
            printf("Guessing yellow\n");
        } else if (hue >= 150 && hue <= 185) {
            if (hue >= 180) {
                printf("Guessing blue\n");
            } else {
                printf("Guessing blue-green\n");
            }
        } else if (hue >= 270 && hue <= 330) {
            printf("Guessing purple-pink\n");
        }
    }
    
    
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
