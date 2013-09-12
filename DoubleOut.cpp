//
//  DoubleOut.cpp
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
#include "DoubleOut.h"



// 関数のプロトタイプ宣言
void *DoubleOut_new(t_symbol *s, long argc, t_atom *argv);
void DoubleOut_free(t_DoubleOut *x);
void DoubleOut_assist(t_DoubleOut *x, void *b, double m, double a, char *s);
void DoubleOut_write(t_DoubleOut *x, double m);

t_class *DoubleOut_class;


void DoubleOut_init()
{
   
    DoubleOut_class = class_new("DoubleOut", (method)DoubleOut_new, (method)DoubleOut_free, (long)sizeof(t_DoubleOut),
                                0L, A_GIMME, 0);
    class_addmethod(DoubleOut_class, (method)DoubleOut_write, "ft1", A_FLOAT, 0);
    class_register(CLASS_BOX, DoubleOut_class);
}

void DoubleOut_assist(t_DoubleOut *x, void *b, double m, double a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s, "Message In");
}

void DoubleOut_free(t_DoubleOut *x)
{
    m_pRTC->deleteDoubleOutPort(x->portId);
}

void DoubleOut_write(t_DoubleOut *x, double m)
{
    m_pRTC->m_doubleOut[x->portId].data = m;
    m_pRTC->m_doubleOutOut[x->portId]->write();
}

void *DoubleOut_new(t_symbol *s, long argc, t_atom *argv)
{
	t_DoubleOut *x = NULL;
    if (argc == 0) {
        post("DoubleOut needs one argument that means port_name.");
        return NULL;
    }
	x = (t_DoubleOut *)object_alloc((t_class*)DoubleOut_class);    
    floatin(x, 1);
    post("hogehoge");
    //return x;


    //x->portId=0;
	x->portId = m_pRTC->addDoubleOutPort(argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("DoubleOut failed to create TimedDoubleOutPort.");
        return NULL;
    }
	return x;
}
