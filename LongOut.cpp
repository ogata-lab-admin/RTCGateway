//
//  LongOut.cpp
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
#include "LongOut.h"



// 関数のプロトタイプ宣言
void *LongOut_new(t_symbol *s, long argc, t_atom *argv);
void LongOut_free(t_LongOut *x);
void LongOut_assist(t_LongOut *x, void *b, long m, long a, char *s);
void LongOut_write(t_LongOut *x, long m);

t_class *LongOut_class;



void LongOut_init()
{
    LongOut_class = class_new("LongOut", (method)LongOut_new, (method)LongOut_free, (long)sizeof(t_LongOut),
                                0L, A_GIMME, 0);
    class_addmethod(LongOut_class, (method)LongOut_write,	"in1", A_LONG, 0);
    class_register(CLASS_BOX, LongOut_class);
}

void LongOut_assist(t_LongOut *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s, "Message In");
}

void LongOut_free(t_LongOut *x)
{
    m_pRTC->deleteLongOutPort(x->portId);
}

void LongOut_write(t_LongOut *x, long m)
{
    m_pRTC->m_longOut[x->portId].data = m;
    m_pRTC->m_longOutOut[x->portId]->write();
}

void *LongOut_new(t_symbol *s, long argc, t_atom *argv)
{
	t_LongOut *x = NULL;
    if (argc == 0) {
        post("LongOut needs one argument that means port_name.");
        return NULL;
    }
    
	x = (t_LongOut *)object_alloc((t_class*)LongOut_class);
    intin(x, 1);
	x->portId = m_pRTC->addLongOutPort(argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("LongOut failed to create TimedLongOutPort.");
        return NULL;
    }
	return x;
}
