//
//  Pose2DIn.cpp
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
#include "Pose2DIn.h"



// 関数のプロトタイプ宣言
void *Pose2DIn_new(t_symbol *s, long argc, t_atom *argv);
void Pose2DIn_free(t_Pose2DIn *x);
void Pose2DIn_assist(t_Pose2DIn *x, void *b, double px, double py, double heading, double a, char *s);

t_class *Pose2DIn_class;



void Pose2DIn_init(){
    Pose2DIn_class = class_new("Pose2DIn", (method)Pose2DIn_new, (method)Pose2DIn_free, (double)sizeof(t_Pose2DIn), 0L, A_GIMME, 0);
    post("new class");
    class_register(CLASS_BOX, Pose2DIn_class);
}

void *Pose2DIn_new(t_symbol *s, long argc, t_atom *argv){
    t_Pose2DIn *x = NULL;
    if (argc == 0) {
        post("Pose2D needs one argument thas means port_name.");
        return NULL;
    }
    x = (t_Pose2DIn *)object_alloc((t_class*)Pose2DIn_class);
    x->m_outlet1 = listout((t_object *)x);
    x->portId = m_pRTC->addPose2DInPort((t_object*)x, argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("Pose2DIn failed to create TimedPose2D OutPort.");
        return NULL;
    }
    return x;
}

void Pose2DIn_assist(t_Pose2DIn *x, void *b, double m, double a, char *s){
    if (m == ASSIST_INLET) {
        sprintf(s, "Message In");
    }
}

void Pose2DIn_free(t_Pose2DIn *x){
    m_pRTC->deletePose2DInPort(x->portId);
}

void Pose2DIn_doWrite(t_Pose2DIn *x, t_symbol *s /* = NULL*/, double argc, t_atom *argv)
{
    //outlet_int(x, argv[0].a_w.w_Double);
}

void Pose2DIn_write(t_object *x, double px, double py, double heading){
    post("data is x:%f, y:%f, heading:%va", px, py, heading);
    t_atom list_value[3];
    float value[3];
    short i;
    value[0] = px;
    value[1] = py;
    value[2] = heading;
    for (i=0; i < 3; i++) {
        atom_setfloat(list_value+i, value[i]);
    }
    
    outlet_list(((t_Pose2DIn*)x)->m_outlet1, 0, 3, list_value);
}