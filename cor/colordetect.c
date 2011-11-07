/* code for "colordetect" pd class.  This takes two messages: floating-point
numbers, and "rats", and just prints something out for each message. */

#include "m_pd.h"

/* the data structure for each copy of "colordetect".  In this case we
on;y need pd's obligatory header (of type t_object). */
typedef struct colordetect
{
  t_object x_ob;
} t_colordetect;

/* this is called back when colordetect gets a "float" message (i.e., a
number.) */
void colordetect_float(t_colordetect *x, t_floatarg f)
{
    post("colordetect: %f", f);
    x=NULL; /* don't warn about unused variables */
}

/* this is called when colordetect gets the message, "rats". */
void colordetect_rats(t_colordetect *x)
{
    post("colordetect: rats");
    x=NULL; /* don't warn about unused variables */
}

    /* this is a pointer to the class for "colordetect", which is created in the
    "setup" routine below and used to create new ones in the "new" routine. */
static t_class *colordetect_class;

    /* this is called when a new "colordetect" object is created. */
void *colordetect_new(void)
{
    t_colordetect *x = (t_colordetect *)pd_new(colordetect_class);
    post("colordetect_new");
    return (void *)x;
}

    /* this is called once at setup time, when this code is loaded into Pd. */
void colordetect_setup(void)
{
    post("colordetect_setup");
    colordetect_class = class_new(gensym("colordetect"), (t_newmethod)colordetect_new, 0,
    	sizeof(t_colordetect), 0, 0);

    class_addmethod(colordetect_class, (t_method)colordetect_rats, gensym("rats"), 0);
    class_addfloat(colordetect_class, colordetect_float);
}

