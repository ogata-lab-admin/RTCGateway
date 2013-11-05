//
//  Point2DOut.cpp
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
#include "Point2DOut.h"


//double vx, double vy, double va
// 関数のプロトタイプ宣言
void *Point2DOut_new(t_symbol *s, long argc, t_atom *argv);
void Point2DOut_free(t_Point2DOut *x);
void Point2DOut_assist(t_Point2DOut *x, void *b, long m, long a, char *s);
void Point2DOut_write(t_Point2DOut *x, t_symbol *s, long argc, t_atom *argv);

t_class *Point2DOut_class;


void Point2DOut_init(){
    Point2DOut_class = class_new("Point2DOut", (method)Point2DOut_new, (method)Point2DOut_free, (long)sizeof(t_Point2DOut), 0L, A_GIMME, 0);
    class_addmethod(Point2DOut_class, (method)Point2DOut_write, "list", A_GIMME, 0);
    class_register(CLASS_BOX, Point2DOut_class);
}

void Point2DOut_assist(t_Point2DOut *x, void *b, long m, long a, char *s){
    if (m == ASSIST_INLET) {
        sprintf(s, "Message In");
    }
}

void Point2DOut_free(t_Point2DOut *x){
    m_pRTC->deletePoint2DOutPort(x->portId);
}

void Point2DOut_write(t_Point2DOut *x, t_symbol *s, long argc, t_atom *argv){
    double value[2];
    if (argc >= 2) {
        for (int i = 0;i < 2;i++) {
            if (argv[i].a_type == A_LONG) {
                value[i] = argv[i].a_w.w_long;
            } else if (argv[i].a_type == A_FLOAT) {
                value[i] = argv[i].a_w.w_float;
            } else {
                post("Uncompatible value type of input for Point2DOut");
            }
        }
    
    }
    m_pRTC->m_Point2DOut[x->portId].data.x = value[0];
    m_pRTC->m_Point2DOut[x->portId].data.y = value[1];
    m_pRTC->m_Point2DOutOut[x->portId]->write();
}

void *Point2DOut_new(t_symbol *s, long argc, t_atom *argv){
    t_Point2DOut *x = NULL;
    if (argc == 0) {
        post("Point2Dut needs one argument that means port_name.");
        return NULL;
    }
    x = (t_Point2DOut *)object_alloc((t_class*)Point2DOut_class);
    
    x->portId = m_pRTC->addPoint2DOutPort(argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("Point2DOut failed to create Point2DOutPort.");
        return NULL;
    }
	return x;
}