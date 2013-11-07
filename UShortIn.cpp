//
//  UShortIn.cpp
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
#include "UShortIn.h"


// 関数のプロトタイプ宣言
void *UShortIn_new(t_symbol *s, long argc, t_atom *argv);
void UShortIn_free(t_UShortIn *x);
void UShortIn_assist(t_UShortIn *x, void *b, long m, long a, char *s);


t_class *UShortIn_class;



void UShortIn_init()
{
    UShortIn_class = class_new("UShortIn", (method)UShortIn_new, (method)UShortIn_free, (long)sizeof(t_UShortIn),
                               0L, A_GIMME, 0);
    class_register(CLASS_BOX, UShortIn_class);
}

void UShortIn_assist(t_UShortIn *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s, "Message In");
}

void UShortIn_free(t_UShortIn *x)
{
    m_pRTC->deleteUShortInPort(x->portId);
}

void UShortIn_doWrite(t_UShortIn *x, t_symbol *s /* = NULL*/, long argc, t_atom *argv)
{
    //outlet_int(x, argv[0].a_w.w_long);
}

void UShortIn_write(t_object *x, int m)
{
    post("Ushort data is %d", m);
    outlet_int(((t_UShortIn*)x)->m_outlet, m);
}

void *UShortIn_new(t_symbol *s, long argc, t_atom *argv)
{
	t_UShortIn *x = NULL;
    if (argc == 0) {
        post("UShortIn needs one argument that means port_name.");
        return NULL;
    }
    
	x = (t_UShortIn *)object_alloc((t_class*)UShortIn_class);
    x->m_outlet = intout((t_object *)x);
	x->portId = m_pRTC->addUShortInPort((t_object*)x, argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("UShortIn failed to create TimedUShort OutPort.");
        return NULL;
    }
	return x;
}
