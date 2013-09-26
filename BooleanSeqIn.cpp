//
//  BooleanSeqIn.cpp
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
#include "BooleanSeqIn.h"



// 関数のプロトタイプ宣言
void *BooleanSeqIn_new(t_symbol *s, long argc, t_atom *argv);
void BooleanSeqIn_free(t_BooleanSeqIn *x);
void BooleanSeqIn_assist(t_BooleanSeqIn *x, void *b, double px, double py, double heading, double a, char *s);

t_class *BooleanSeqIn_class;



void BooleanSeqIn_init(){
    BooleanSeqIn_class = class_new("BooleanSeqIn", (method)BooleanSeqIn_new, (method)BooleanSeqIn_free, (double)sizeof(t_BooleanSeqIn), 0L, A_GIMME, 0);
    post("new class");
    class_register(CLASS_BOX, BooleanSeqIn_class);
}

void *BooleanSeqIn_new(t_symbol *s, long argc, t_atom *argv){
    t_BooleanSeqIn *x = NULL;
    if (argc == 0) {
        post("BooleanSeq needs one argument thas means port_name.");
        return NULL;
    }
    x = (t_BooleanSeqIn *)object_alloc((t_class*)BooleanSeqIn_class);
    x->m_outlet1 = listout((t_object *)x);
    x->portId = m_pRTC->addBooleanSeqInPort((t_object*)x, argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("BooleanSeqIn failed to create TimedBooleanSeq OutPort.");
        return NULL;
    }
    return x;
}

void BooleanSeqIn_assist(t_BooleanSeqIn *x, void *b, double m, double a, char *s){
    if (m == ASSIST_INLET) {
        sprintf(s, "Message In");
    }
}

void BooleanSeqIn_free(t_BooleanSeqIn *x){
    m_pRTC->deleteBooleanSeqInPort(x->portId);
}

void BooleanSeqIn_doWrite(t_BooleanSeqIn *x, t_symbol *s /* = NULL*/, double argc, t_atom *argv)
{
    //outlet_int(x, argv[0].a_w.w_Double);
}

void BooleanSeqIn_write(t_object *x, int argc, bool argv[]) { ///double right_bumper, double center_bumper, double left_bumper){
  //post("bumper state is right:%d, center:%d, left:%f", right_bumper, center_bumper, left_bumper);
  t_atom *list_value = new t_atom[argc];
    long *value = new long[argc];
  for (int i = 0;i < argc;i++) {
    value[i] = argv[i];
    atom_setlong(list_value+i, value[i]);
  }
  outlet_list(((t_BooleanSeqIn*)x)->m_outlet1, 0, argc, list_value);
  delete[] list_value;
  delete value;
}
