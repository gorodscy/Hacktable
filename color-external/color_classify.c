#include <stdio.h>

typedef enum {BLACK, WHITE, RED, GREEN, BLUE, YELLOW, BLUEGREEN, PURPLEPINK} color;

float MAX (float a, float b, float c);
float MIN (float a, float b, float c);
void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );
void color_classify (float red, float green, float blue, color *result, int *sure);


int main (int argc, const char * argv[])
{

    
    
    
    
    return 0;
}




void color_classify (float red, float green, float blue, color *result, int *sure)
{
    float hue;
    float sat;
    float val;
    
    *sure = 1;
    
    RGBtoHSV(red, green, blue, &hue, &sat, &val);
    
    if (val < 0.2 && sat < 0.8) {
        *result = BLACK;
        return;
    } else if (val > 0.8 && sat < 0.1) {
        *result = WHITE;
        return;
    }
    
    // At this point we have
    // val > 0.2 | (val < 0.8 | sat > 0.1)
    
    if (hue < 30 || hue > 330) {
        *result = RED;
    } else if (hue > 90 && hue < 150) {
        *result = GREEN;
    } else if (hue > 185 && hue < 270) {
        *result = BLUE;
    } else { // disp 'unreliable color...';
        *sure = 0;
        // in the real system you just discard this estimate and use the previous
        // estimate (e.g. previous frame) at this point
        if (hue >= 30 && hue <= 90) {
            *result = YELLOW;
        } else if (hue >= 150 && hue <= 185) {
            if (hue >= 180) {
                *result = BLUE;
            } else {
                *result = BLUEGREEN;
            }
        } else if (hue >= 270 && hue <= 330) {
            *result = PURPLEPINK;
        }
    }
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
