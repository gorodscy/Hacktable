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
  t_outlet *result_outlet;
  t_outlet *certainty_outlet;
  t_outlet *second_guess_outlet;
} t_colordetect;

/* this is a pointer to the class for "colordetect", which is created in the
"setup" routine below and used to create new ones in the "new" routine. */
static t_class *colordetect_class;

/*----------------------------------------------------------------------*/

void 
print_color_pd (color result, color second, certainty certainty_level) 
{
  extern char *color_name[], *certainty_name[];
  assert(result < num_colors);
  post("%s ", color_name[result]);

  assert(second < num_colors);
  post("%s ", color_name[second]);
    
  assert(certainty_level < 3);
  post("%s\n", certainty_name[certainty_level]);
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

    color_classify(r, g, b, &result, &second_guess, &c);
    outlet_float(this->result_outlet, (t_float)result);
    outlet_float(this->second_guess_outlet, (t_float)second_guess);
    outlet_float(this->certainty_outlet, (t_float)c);
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

    x->result_outlet = outlet_new(&x->x_obj, &s_float);
    x->second_guess_outlet = outlet_new(&x->x_obj, &s_float);
    x->certainty_outlet = outlet_new(&x->x_obj, &s_float);

    // Note: uncertain = (!certain && !good-guess)
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
