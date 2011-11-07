/* 
 code for "colordetect" pd class.  
*/

#include "m_pd.h"

/* the data structure for each copy of "colordetect".  In this case we
on;y need pd's obligatory header (of type t_object). */
typedef struct colordetect
{
  t_object x_ob;
} t_colordetect;

/* this is a pointer to the class for "colordetect", which is created in the
"setup" routine below and used to create new ones in the "new" routine. */
static t_class *colordetect_class;

/*----------------------------------------------------------------------*/

static void 
colordetect_list(t_colordetect *this, t_symbol *s, int argc, t_atom *argv)
{
  if (argc >= 3) {
    t_float r = atom_getfloat(&argv[0]);
    t_float g = atom_getfloat(&argv[1]);
    t_float b = atom_getfloat(&argv[2]);
    post("got rgb: %g%g%g", r, g, b);
  }
}

/* this is called when a new "colordetect" object is created. */
static void *
colordetect_new(void)
{
    t_colordetect *x = (t_colordetect *)pd_new(colordetect_class);
    // xx TODO new outlet 
    post("colordetect_new");
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
