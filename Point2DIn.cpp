//
//  Point2DIn.cpp
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
#include "Point2DIn.h"



// 関数のプロトタイプ宣言
void *Point2DIn_new(t_symbol *s, long argc, t_atom *argv);
void Point2DIn_free(t_Point2DIn *x);
void Point2DIn_assist(t_Point2DIn *x, void *b, double px, double py, double heading, double a, char *s);

t_class *Point2DIn_class;



void Point2DIn_init(){
    Point2DIn_class = class_new("Point2DIn", (method)Point2DIn_new, (method)Point2DIn_free, (double)sizeof(t_Point2DIn), 0L, A_GIMME, 0);
    post("new class");
    class_register(CLASS_BOX, Point2DIn_class);
}

void *Point2DIn_new(t_symbol *s, long argc, t_atom *argv){
    t_Point2DIn *x = NULL;
    if (argc == 0) {
        post("Point2D needs one argument thas means port_name.");
        return NULL;
    }
    x = (t_Point2DIn *)object_alloc((t_class*)Point2DIn_class);
    x->m_outlet1 = listout((t_object *)x);
    x->portId = m_pRTC->addPoint2DInPort((t_object*)x, argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("Point2DIn failed to create TimedPoint2D OutPort.");
        return NULL;
    }
    return x;
}

void Point2DIn_assist(t_Point2DIn *x, void *b, double m, double a, char *s){
    if (m == ASSIST_INLET) {
        sprintf(s, "Message In");
    }
}

void Point2DIn_free(t_Point2DIn *x){
    m_pRTC->deletePoint2DInPort(x->portId);
}

void Point2DIn_doWrite(t_Point2DIn *x, t_symbol *s /* = NULL*/, double argc, t_atom *argv)
{
    //outlet_int(x, argv[0].a_w.w_Double);
}

void Point2DIn_write(t_object *x, double px, double py){
    post("data is x:%f, y:%f. ", px, py);
    t_atom list_value[2];
    float value[2];
    short i;
    value[0] = px;
    value[1] = py;
    for (i=0; i < 2; i++) {
        atom_setfloat(list_value+i, value[i]);
    }
    
    outlet_list(((t_Point2DIn*)x)->m_outlet1, 0, 2, list_value);
}