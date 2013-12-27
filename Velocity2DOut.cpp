//
//  Velocity2DOut.cpp
//  RTMPort-x86_64
//
//  Created by kazuma sasaki@ogata-lab on 2013/08/21.
//
//

#ifdef nil
#undef nil
#endif 

#include "RTCGateway.h"
#include "MAX_MSP_RTC.h"

#include "ext.h" // MAXプラグイン用ヘッダ
#include "ext_obex.h" // MAXプラグイン用ヘッダ
#include "Velocity2DOut.h"


//double vx, double vy, double va
// 関数のプロトタイプ宣言
void *Velocity2DOut_new(t_symbol *s, long argc, t_atom *argv);
void Velocity2DOut_free(t_Velocity2DOut *x);
void Velocity2DOut_assist(t_Velocity2DOut *x, void *b, long m, long a, char *s);
void Velocity2DOut_write(t_Velocity2DOut *x, t_symbol *s, long argc, t_atom *argv);

t_class *Velocity2DOut_class;


void Velocity2DOut_init(){
    Velocity2DOut_class = class_new("Velocity2DOut", (method)Velocity2DOut_new, (method)Velocity2DOut_free, (long)sizeof(t_Velocity2DOut), 0L, A_GIMME, 0);
    class_addmethod(Velocity2DOut_class, (method)Velocity2DOut_write, "list", A_GIMME, 0);
    class_register(CLASS_BOX, Velocity2DOut_class);
}

void Velocity2DOut_assist(t_Velocity2DOut *x, void *b, long m, long a, char *s){
    if (m == ASSIST_INLET) {
        sprintf(s, "Message In");
    }
}

void Velocity2DOut_free(t_Velocity2DOut *x){
    m_pRTC->deleteVelocity2DOutPort(x->portId);
}

void Velocity2DOut_write(t_Velocity2DOut *x, t_symbol *s, long argc, t_atom *argv){
    double value[3];
    if (argc >= 3) {
        for (int i = 0;i < 3;i++) {
            if (argv[i].a_type == A_LONG) {
                value[i] = argv[i].a_w.w_long;
            } else if (argv[i].a_type == A_FLOAT) {
                value[i] = argv[i].a_w.w_float;
            } else {
                post("Uncompatible value type of input for Velocity2DOut");
            }
        }
    }
    m_pRTC->m_Velocity2DOut[x->portId].data.vx = value[0];
    m_pRTC->m_Velocity2DOut[x->portId].data.vy = value[1];
    m_pRTC->m_Velocity2DOut[x->portId].data.va = value[2];
    m_pRTC->m_Velocity2DOutOut[x->portId]->write();
}

void *Velocity2DOut_new(t_symbol *s, long argc, t_atom *argv){
    t_Velocity2DOut *x = NULL;
    if (argc == 0) {
        post("Velocity2Dut needs one argument that means port_name.");
        return NULL;
    }
    x = (t_Velocity2DOut *)object_alloc((t_class*)Velocity2DOut_class);
    
    x->portId = m_pRTC->addVelocity2DOutPort(argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("Velocity2DOut failed to create Velocity2DOutPort.");
        return NULL;
    }
	return x;
}