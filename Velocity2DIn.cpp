//
//  Velocity2DIn.cpp
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
#include "Velocity2DIn.h"



// 関数のプロトタイプ宣言
void *Velocity2DIn_new(t_symbol *s, long argc, t_atom *argv);
void Velocity2DIn_free(t_Velocity2DIn *x);
void Velocity2DIn_assist(t_Velocity2DIn *x, void *b, double vx, double vy, double va, double a, char *s);

t_class *Velocity2DIn_class;



void Velocity2DIn_init(){
    Velocity2DIn_class = class_new("Velocity2DIn", (method)Velocity2DIn_new, (method)Velocity2DIn_free, (double)sizeof(t_Velocity2DIn), 0L, A_GIMME, 0);
    post("new class");
    class_register(CLASS_BOX, Velocity2DIn_class);
}

void *Velocity2D_new(t_symbol *s, long argc, t_atom *argv){
    t_Velocity2DIn *x = NULL;
    if (argc == 0) {
        post("Velocity2D needs one argument thas means port_name.");
        return NULL;
    }
    x = (t_Velocity2DIn *)object_alloc((t_class*)Velocity2DIn_class);
    x->m_outlet1 = floatout((t_object *)x);
    x->m_outlet2 = floatout((t_object *)x);
    x->m_outlet3 = floatout((t_object *)x);
    x->portId = m_pRTC->addVelocity2DInPort((t_object*)x, argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("Velocity2DIn failed to create TimedVelocity OutPort.");
        return NULL;
    }
    return x;
}

void Velocity2DIn_assist(t_Velocity2DIn *x, void *b, double m, double a, char *s){
    if (m == ASSIST_INLET) {
        sprintf(s, "Message In");
    }
}

void Velocity2DIn_free(t_Velocity2DIn *x){
    m_pRTC->deleteVelocity2DInPort(x->portId);
}

void Velocity2DIn_doWrite(t_Velocity2DIn *x, t_symbol *s /* = NULL*/, double argc, t_atom *argv)
{
    //outlet_int(x, argv[0].a_w.w_Double);
}

void Velocity2DIn_Write(t_object *x, double vx, double vy, double va){
    post("data is vx:%f, vy:%f, va:%va", vx, vy, va);
    outlet_float(((t_Velocity2DIn*)x)->m_outlet1, vx);
    outlet_float(((t_Velocity2DIn*)x)->m_outlet2, vy);
    outlet_float(((t_Velocity2DIn*)x)->m_outlet3, va);
    
    
}