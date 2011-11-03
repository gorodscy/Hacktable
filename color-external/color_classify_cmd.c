#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color_classify.h"


int main (int argc, const char * argv[])
{
    float red = atof (argv[1]);
    float green = atof (argv[2]);
    float blue = atof (argv[3]);
    color result;
    color second_guess;
    certainty certainty_level;
    
    color_classify(red, green, blue, &result, &second_guess, &certainty_level);
    
    print_color(result, second_guess, certainty_level);
    
    
    return 0;
}

void print_color (color result, color second, certainty certainty_level) {
    
    switch (result) {
        case BLACK:
            printf("black ");
            break;
            
        case WHITE:
            printf("white ");
            break;
            
        case RED:
            printf("red ");
            break;
            
        case GREEN:
            printf("green ");
            break;
            
        case BLUE:
            printf("blue ");
            break;
            
        case YELLOW:
            printf("yellow ");
            break;
            
        default:
            printf("none ");
            break;
    }
    
    switch (second) {
        case BLACK:
            printf("black ");
            break;
            
        case WHITE:
            printf("white ");
            break;
            
        case RED:
            printf("red ");
            break;
            
        case GREEN:
            printf("green ");
            break;
            
        case BLUE:
            printf("blue ");
            break;
            
        case YELLOW:
            printf("yellow ");
            break;

        case BLUE_GREEN:
            printf("blue-green ");
            break;
            
        case PURPLE_PINK_LAVENDER:
            printf("purple-pink-lavender ");
            break;
            
        case PURPLE_PINK_MAGENTA:
            printf("purple-pink-magenta ");
            break;
            
        case GRAY:
            printf("gray ");
            break;
            
        default:
            printf("none ");
            break;
    }
    
    switch (certainty_level) {
        case CERTAIN:
            printf("certain\n");
            break;
            
        case GOOD_GUESS:
            printf("good-guess\n");
            break;
            
        case UNRELIABLE:
            printf("unreliable\n");
            break;
            
        default:
            printf("error\n");
            break;
    }
    
    
    
}
