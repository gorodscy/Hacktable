/* 
 code for "colordetect" pd class.  
*/

#include "m_pd.h"
#include "color_classify.h"

/* the data structure for each copy of "colordetect".  In this case we
on;y need pd's obligatory header (of type t_object). */
typedef struct colordetect
{
  t_object x_obj;
} t_colordetect;

/* this is a pointer to the class for "colordetect", which is created in the
"setup" routine below and used to create new ones in the "new" routine. */
static t_class *colordetect_class;

/*----------------------------------------------------------------------*/

void 
print_color_pd (color result, color second, certainty certainty_level) 
{
    switch (result) {
        case BLACK:
            post("black ");
            break;
            
        case WHITE:
            post("white ");
            break;
            
        case RED:
            post("red ");
            break;
            
        case GREEN:
            post("green ");
            break;
            
        case BLUE:
            post("blue ");
            break;
            
        case YELLOW:
            post("yellow ");
            break;
            
        default:
            post("none ");
            break;
    }
    
    switch (second) {
        case BLACK:
            post("black ");
            break;
            
        case WHITE:
            post("white ");
            break;
            
        case RED:
            post("red ");
            break;
            
        case GREEN:
            post("green ");
            break;
            
        case BLUE:
            post("blue ");
            break;
            
        case YELLOW:
            post("yellow ");
            break;

        case BLUE_GREEN:
            post("blue-green ");
            break;
            
        case PURPLE_PINK_LAVENDER:
            post("purple-pink-lavender ");
            break;
            
        case PURPLE_PINK_MAGENTA:
            post("purple-pink-magenta ");
            break;
            
        case GRAY:
            post("gray ");
            break;
            
        default:
            post("none ");
            break;
    }
    
    switch (certainty_level) {
        case CERTAIN:
            post("certain\n");
            break;
            
        case GOOD_GUESS:
            post("good-guess\n");
            break;
            
        case UNRELIABLE:
            post("unreliable\n");
            break;
            
        default:
            post("error\n");
            break;
    }
}

/*----------------------------------------------------------------------*/

static void 
colordetect_list(t_colordetect *this, t_symbol *s, int argc, t_atom *argv)
{
  if (argc >= 3) {
    t_float r = atom_getfloat(&argv[0]);
    t_float g = atom_getfloat(&argv[1]);
    t_float b = atom_getfloat(&argv[2]);

    color result, second_guess;
    certainty c;

    color_classify (r, g, b, &result, &second_guess, &c);
    // do a switch like in _cmd to output the right message/symbol.
    // if good guess, bang the second outlet
    // if uncertain, bang the third outlet
    outlet_float(this->x_obj.ob_outlet, (t_float)result);
    print_color_pd(result, second_guess, c);
  }
}

/* this is called when a new "colordetect" object is created. */
static void *
colordetect_new(void)
{
    // xx TODO new outlet 
    post("colordetect_new");
    t_colordetect *x = (t_colordetect *)pd_new(colordetect_class);

    outlet_new(&x->x_obj, &s_float);

    return (void *)x;
}

/* this is called once at setup time, when this code is loaded into Pd. */
void 
colordetect_setup(void)
{
    post("colordetect_setup");
    colordetect_class = class_new(gensym("colordetect"), (t_newmethod)colordetect_new, 0,
    	sizeof(t_colordetect), 0, 0);

    class_addlist(colordetect_class, (t_method)colordetect_list);
}
