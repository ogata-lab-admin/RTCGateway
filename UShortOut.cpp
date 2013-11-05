//
//  UShortOut.cpp
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
#include "UShortOut.h"



// 関数のプロトタイプ宣言
void *UShortOut_new(t_symbol *s, long argc, t_atom *argv);
void UShortOut_free(t_UShortOut *x);
void UShortOut_assist(t_UShortOut *x, void *b, long m, long a, char *s);
void UShortOut_write(t_UShortOut *x, int m);

t_class *UShortOut_class;



void UShortOut_init()
{
    UShortOut_class = class_new("UShortOut", (method)UShortOut_new, (method)UShortOut_free, (long)sizeof(t_UShortOut),
                                0L, A_GIMME, 0);
    class_addmethod(UShortOut_class, (method)UShortOut_write,	"in1", A_LONG, 0);
    class_register(CLASS_BOX, UShortOut_class);
}

void UShortOut_assist(t_UShortOut *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s, "Message In");
}

void UShortOut_free(t_UShortOut *x)
{
    m_pRTC->deleteUShortOutPort(x->portId);
}

void UShortOut_write(t_UShortOut *x, int m)
{
    m_pRTC->m_longOut[x->portId].data = m;
    m_pRTC->m_longOutOut[x->portId]->write();
}

void *UShortOut_new(t_symbol *s, long argc, t_atom *argv)
{
	t_UShortOut *x = NULL;
    if (argc == 0) {
        post("UShortOut needs one argument that means port_name.");
        return NULL;
    }
    
	x = (t_UShortOut *)object_alloc((t_class*)UShortOut_class);
    intin(x, 1);
	x->portId = m_pRTC->addUShortOutPort(argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("UShortOut failed to create TimedUShortOutPort.");
        return NULL;
    }
	return x;
}
