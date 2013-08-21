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
void LongIn_write(t_LongIn *x, long m);

t_class *LongIn_class;



void LongIn_init()
{
    LongIn_class = class_new("LongIn", (method)LongIn_new, (method)LongIn_free, (long)sizeof(t_LongIn),
                                0L, A_GIMME, 0);
    class_addmethod(LongIn_class, (method)LongIn_write,	"in1", A_LONG, 0);
    class_register(CLASS_BOX, LongIn_class);
}

void LongIn_assist(t_LongIn *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s, "Message In");
}

void LongIn_free(t_LongIn *x)
{
    m_pRTC->deleteLongOutPort(x->portId);
}

void LongIn_write(t_LongIn *x, long m)
{
    m_pRTC->m_longOut[x->portId].data = m;
    m_pRTC->m_longOutOut[x->portId]->write();
}

void *LongIn_new(t_symbol *s, long argc, t_atom *argv)
{
	t_LongIn *x = NULL;
    if (argc == 0) {
        post("LongIn needs one argument that means port_name.");
        return NULL;
    }
    
	x = (t_LongIn *)object_alloc((t_class*)LongIn_class);
    intin(x, 1);
	x->portId = m_pRTC->addLongOutPort(argv[0].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("LongIn failed to create TimedLongOutPort.");
        return NULL;
    }
	return x;
}
