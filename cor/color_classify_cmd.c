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

