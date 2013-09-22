//
//  Pose2DOut.cpp
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
#include "Pose2DOut.h"


//double vx, double vy, double va
// 関数のプロトタイプ宣言
void *Pose2DOut_new(t_symbol *s, long argc, t_atom *argv);
void Pose2DOut_free(t_Pose2DOut *x);
void Pose2DOut_assist(t_Pose2DOut *x, void *b, long m, long a, char *s);
void Pose2DOut_write(t_Pose2DOut *x, t_symbol *s, long argc, t_atom *argv);

t_class *Pose2DOut_class;


void Pose2DOut_init(){
    Pose2DOut_class = class_new("Pose2DOut", (method)Pose2DOut_new, (method)Pose2DOut_free, (long)sizeof(t_Pose2DOut), 0L, A_GIMME, 0);
    class_addmethod(Pose2DOut_class, (method)Pose2DOut_write, "list", A_GIMME, 0);
    class_register(CLASS_BOX, Pose2DOut_class);
}

void Pose2DOut_assist(t_Pose2DOut *x, void *b, long m, long a, char *s){
    if (m == ASSIST_INLET) {
        sprintf(s, "Message In");
    }
}

void Pose2DOut_free(t_Pose2DOut *x){
    m_pRTC->deletePose2DOutPort(x->portId);
}

void Pose2DOut_write(t_Pose2DOut *x, t_symbol *s, long argc, t_atom *argv){
    double value[3];
    if (argc >= 3) {
        for (int i = 0;i < 3;i++) {
            if (argv[i].a_type == A_LONG) {
                value[i] = argv[i].a_w.w_long;
            } else if (argv[i].a_type == A_FLOAT) {
                value[i] = argv[i].a_w.w_float;
            } else {
                post("Uncompatible value type of input for Pose2DOut");
            }
        }
    }
    m_pRTC->m_Pose2DOut[x->portId].data.position.x = value[0];
    m_pRTC->m_Pose2DOut[x->portId].data.position.y = value[1];
    m_pRTC->m_Pose2DOut[x->portId].data.heading = value[2];
    m_pRTC->m_Pose2DOutOut[x->portId]->write();
}

void *Pose2DOut_new(t_symbol *s, long argc, t_atom *argv){
    t_Pose2DOut *x = NULL;
    if (argc == 0) {
        post("Pose2Dut needs one argument that means port_name.");
        return NULL;
    }
    x = (t_Pose2DOut *)object_alloc((t_class*)Pose2DOut_class);
    
    x->portId = m_pRTC->addPose2DOutPort(argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("Pose2DOut failed to create Pose2DOutPort.");
        return NULL;
    }
	return x;
}