//
//  BooleanSeqOut.cpp
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
#include "BooleanSeqOut.h"


//double vx, double vy, double va
// 関数のプロトタイプ宣言
void *BooleanSeqOut_new(t_symbol *s, long argc, t_atom *argv);
void BooleanSeqOut_free(t_BooleanSeqOut *x);
void BooleanSeqOut_assist(t_BooleanSeqOut *x, void *b, long m, long a, char *s);
void BooleanSeqOut_write(t_BooleanSeqOut *x, t_symbol *s, long argc, t_atom *argv);

t_class *BooleanSeqOut_class;


void BooleanSeqOut_init(){
    BooleanSeqOut_class = class_new("BooleanSeqOut", (method)BooleanSeqOut_new, (method)BooleanSeqOut_free, (long)sizeof(t_BooleanSeqOut), 0L, A_GIMME, 0);
    class_addmethod(BooleanSeqOut_class, (method)BooleanSeqOut_write, "list", A_GIMME, 0);
    class_register(CLASS_BOX, BooleanSeqOut_class);
}

void BooleanSeqOut_assist(t_BooleanSeqOut *x, void *b, long m, long a, char *s){
    if (m == ASSIST_INLET) {
        sprintf(s, "Message In");
    }
}

void BooleanSeqOut_free(t_BooleanSeqOut *x){
    m_pRTC->deleteBooleanSeqOutPort(x->portId);
}

void BooleanSeqOut_write(t_BooleanSeqOut *x, t_symbol *s, long argc, t_atom *argv){
    double value[3];
    if (argc >= 3) {
        for (int i = 0;i < 3;i++) {
            if (argv[i].a_type == A_LONG) {
                value[i] = argv[i].a_w.w_long;
            } else if (argv[i].a_type == A_FLOAT) {
                value[i] = argv[i].a_w.w_float;
            } else {
                post("Uncompatible value type of input for BooleanSeqOut");
            }
        }
    }
    m_pRTC->m_BooleanSeqOut[x->portId].data[0] = value[0];
    m_pRTC->m_BooleanSeqOut[x->portId].data[1] = value[1];
    m_pRTC->m_BooleanSeqOut[x->portId].data[2] = value[2];
    
    m_pRTC->m_BooleanSeqOutOut[x->portId]->write();
}

void *BooleanSeqOut_new(t_symbol *s, long argc, t_atom *argv){
    t_BooleanSeqOut *x = NULL;
    if (argc == 0) {
        post("BooleanSequt needs one argument that means port_name.");
        return NULL;
    }
    x = (t_BooleanSeqOut *)object_alloc((t_class*)BooleanSeqOut_class);
    
    x->portId = m_pRTC->addBooleanSeqOutPort(argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("BooleanSeqOut failed to create BooleanSeqOutPort.");
        return NULL;
    }
	return x;
}