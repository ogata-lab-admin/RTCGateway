//
//  doubleIn.cpp
//  RTMPort-x86_64
//
//  Created by 菅 佑樹 on 2013/08/21.
//
//

#ifdef nil
#undef nil
#endif 

#include "RTCGateway.h"
#include "MAX_MSP_RTC.h"

#include "ext.h" // MAXプラグイン用ヘッダ
#include "ext_obex.h" // MAXプラグイン用ヘッダ
#include "DoubleIn.h"



// 関数のプロトタイプ宣言
void *DoubleIn_new(t_symbol *s, long argc, t_atom *argv);
void DoubleIn_free(t_DoubleIn *x);
void DoubleIn_assist(t_DoubleIn *x, void *b, double m, double a, char *s);


t_class *DoubleIn_class;



void DoubleIn_init()
{
    DoubleIn_class = class_new("DoubleIn", (method)DoubleIn_new, (method)DoubleIn_free, (double)sizeof(t_DoubleIn),
                                0L, A_GIMME, 0);
    post("new class");
    class_register(CLASS_BOX, DoubleIn_class);
}

void DoubleIn_assist(t_DoubleIn *x, void *b, double m, double a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s, "Message In");
}

void DoubleIn_free(t_DoubleIn *x)
{
    m_pRTC->deleteDoubleInPort(x->portId);
}

void DoubleIn_doWrite(t_DoubleIn *x, t_symbol *s /* = NULL*/, double argc, t_atom *argv)
{
    //outlet_int(x, argv[0].a_w.w_Double);
}

void DoubleIn_write(t_object *x, double m)
{
    post("data is %d", m);
    outlet_float(((t_DoubleIn*)x)->m_outlet, m);
}

void *DoubleIn_new(t_symbol *s, long argc, t_atom *argv)
{
	t_DoubleIn *x = NULL;
    if (argc == 0) {
        post("DoubleIn needs one argument that means port_name.");
        return NULL;
    }
    
	x = (t_DoubleIn *)object_alloc((t_class*)DoubleIn_class);
    x->m_outlet = floatout((t_object *)x);
	x->portId = m_pRTC->addDoubleInPort((t_object*)x, argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("DoubleIn failed to create TimedDouble OutPort.");
        return NULL;
    }
	return x;
}
