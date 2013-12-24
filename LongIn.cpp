//
//  LongIn.cpp
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
#include "LongIn.h"


// 関数のプロトタイプ宣言
void *LongIn_new(t_symbol *s, long argc, t_atom *argv);
void LongIn_free(t_LongIn *x);
void LongIn_assist(t_LongIn *x, void *b, long m, long a, char *s);


t_class *LongIn_class;



void LongIn_init()
{
    LongIn_class = class_new("LongIn", (method)LongIn_new, (method)LongIn_free, (long)sizeof(t_LongIn),
                                0L, A_GIMME, 0);
    class_register(CLASS_BOX, LongIn_class);
}

void LongIn_assist(t_LongIn *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s, "Message In");
}

void LongIn_free(t_LongIn *x)
{
    m_pRTC->deleteLongInPort(x->portId);
}

void LongIn_doWrite(t_LongIn *x, t_symbol *s /* = NULL*/, long argc, t_atom *argv)
{
    //outlet_int(x, argv[0].a_w.w_long);
}

void LongIn_write(t_object *x, long m)
{
    post("data is %d", m);
    outlet_int(((t_LongIn*)x)->m_outlet, m);
}

void *LongIn_new(t_symbol *s, long argc, t_atom *argv)
{
    post("LongIn_new");
	t_LongIn *x = NULL;
    if (argc == 0) {
        post("LongIn needs one argument that means port_name.");
        return NULL;
    }
    
	x = (t_LongIn *)object_alloc((t_class*)LongIn_class);
    x->m_outlet = intout((t_object *)x);
	x->portId = m_pRTC->addLongInPort((t_object*)x, argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("LongIn failed to create TimedLong OutPort.");
        return NULL;
    }
	return x;
}
