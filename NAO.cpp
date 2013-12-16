//
//  NAO.cpp
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
#include "NAO.h"


//double vx, double vy, double va
// 関数のプロトタイプ宣言


t_class *NAO_Motion_class;
t_class *NAO_TextToSpeech_class;
t_class *NAO_BehaviorManager_class;

void *NAO_new(t_symbol *s, long argc, t_atom *argv){
    m_pRTC->addNAOPort();
    post("NAO_new %d", argc);
    if (strcmp(argv[1].a_w.w_sym->s_name, "ALMotion") == 0) {
        t_NAO_Motion *x = NULL;
        post("Create NAO ALMotion Port.");
        x = (t_NAO_Motion *)object_alloc((t_class*)NAO_Motion_class);
        x->m_outlet1 = listout((t_object *)x);
        return x;
    }
    else if (strcmp(argv[1].a_w.w_sym->s_name, "ALTextToSpeech") == 0) {
        t_NAO_TextToSpeech *x = NULL;
        post("Create NAO ALTextToSpeech Port.");
        x = (t_NAO_TextToSpeech *)object_alloc((t_class*)NAO_TextToSpeech_class);
        return x;
    }
    else if (strcmp(argv[1].a_w.w_sym->s_name, "ALBehaviorManager") == 0) {
        t_NAO_BehaviorManager *x = NULL;
        post("Create NAO ALBehaviorManager Port.");
        x = (t_NAO_BehaviorManager *)object_alloc((t_class*)NAO_BehaviorManager_class);
        x->m_outlet1 = intout((t_object *)x);
        return x;
    }
    else {
        post("Invalid Argument for NAO port.");
    }
    
    return NULL;
}

void NAO_free(t_NAO_Motion *x){
    m_pRTC->deleteNAOPort();
}

void NAO_Motion_setAngles(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    //post("setAngles:%d", argc);
    int len = (argc-1)/2;
    if (len == 0) {
        post("Invalid Number of argument");
    }
    
    if(m_pRTC->isNAOConnected()) {
        ssr::StringArray sa;
        ssr::FloatArray fa;
        sa.data.length(len);
        fa.data.length(len);
        for(int i = 0;i < len;i++) {
            sa.data[i] = argv[i].a_w.w_sym->s_name;
            
            if(argv[len+i].a_type == A_LONG) {
                fa.data[i] = argv[len+i].a_w.w_long;
            } else if(argv[len+i].a_type == A_FLOAT) {
                fa.data[i] = argv[len+i].a_w.w_float;
            }
        }
        
        float spd = 1.0;
        if(argv[argc].a_type == A_LONG) {
            spd = argv[argc].a_w.w_long;
        } else if(argv[argc].a_type == A_FLOAT) {
            spd = argv[argc].a_w.w_float;
        }
        m_pRTC->m_motion->setAngles(sa, fa, spd);
    }
    
}

void NAO_Motion_getAngles(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    //post("getAngles:%d", argc);
    int len = (argc-1);
    if (len == 0) {
        post("Invalid Number of argument");
    }
    
    if(m_pRTC->isNAOConnected()) {
        ssr::StringArray sa;
        sa.data.length(len);
        for(int i = 0;i < len;i++) {
            sa.data[i] = argv[i].a_w.w_sym->s_name;
        }
        
        long flg = 0;
        if(argv[argc].a_type == A_LONG) {
            flg = argv[argc].a_w.w_long;
        } else if(argv[argc].a_type == A_FLOAT) {
            flg = argv[argc].a_w.w_float;
        }
        ssr::FloatArray *fa = m_pRTC->m_motion->getAngles(sa, flg);
        t_atom *list_value = new t_atom[len];
        float *value = new float[len];
        for (int i = 0;i < len;i++) {
            value[i] = fa->data[i];
            atom_setfloat(list_value+i, value[i]);
        }
        outlet_list((x)->m_outlet1, 0, len, list_value);
        delete[] list_value;
        delete value;
        delete fa;
    }
    
}

void NAO_Motion_setStiffnesses(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    //post("setStiffnesses:%d", argc);
    int len = (argc)/2;
    if (len == 0) {
        post("Invalid Number of argument");
    }
    
    if(m_pRTC->isNAOConnected()) {
        ssr::StringArray sa;
        ssr::FloatArray fa;
        sa.data.length(len);
        fa.data.length(len);
        for(int i = 0;i < len;i++) {
            sa.data[i] = argv[i].a_w.w_sym->s_name;
            
            if(argv[len+i].a_type == A_LONG) {
                fa.data[i] = argv[len+i].a_w.w_long;
            } else if(argv[len+i].a_type == A_FLOAT) {
                fa.data[i] = argv[len+i].a_w.w_float;
            }
        }
        m_pRTC->m_motion->setStiffness(sa, fa);
    }
    
}

void NAO_Motion_getStiffnesses(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    //post("getAngles:%d", argc);
    int len = (argc);
    if (len == 0) {
        post("Invalid Number of argument");
    }
    
    if(m_pRTC->isNAOConnected()) {
        ssr::StringArray sa;
        sa.data.length(len);
        for(int i = 0;i < len;i++) {
            sa.data[i] = argv[i].a_w.w_sym->s_name;
        }
        
        ssr::FloatArray *fa = m_pRTC->m_motion->getStiffness(sa);
        t_atom *list_value = new t_atom[len];
        float *value = new float[len];
        for (int i = 0;i < len;i++) {
            value[i] = fa->data[i];
            atom_setfloat(list_value+i, value[i]);
        }
        outlet_list((x)->m_outlet1, 0, len, list_value);
        delete[] list_value;
        delete value;
        delete fa;
    }
    
}

void NAO_Motion_moveTo(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    post("moveTo:%d", argc);
    int len = (argc)/2;
    if (len != 3) {
        post("Invalid Number of argument");
    }
    if(m_pRTC->isNAOConnected()) {
         
        float vx = argv[0].a_type == A_LONG ? argv[0].a_w.w_long : argv[0].a_w.w_float;
        float vy = argv[1].a_type == A_LONG ? argv[1].a_w.w_long : argv[1].a_w.w_float;
        float va = argv[2].a_type == A_LONG ? argv[2].a_w.w_long : argv[2].a_w.w_float;
        m_pRTC->m_motion->moveTo(vx, vy, va);
    }
}


void NAO_Motion_moveToward(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    post("moveToward:%d", argc);
    int len = (argc)/2;
    if (len != 3) {
        post("Invalid Number of argument");
    }
    if(m_pRTC->isNAOConnected()) {
        
        float vx = argv[0].a_type == A_LONG ? argv[0].a_w.w_long : argv[0].a_w.w_float;
        float vy = argv[1].a_type == A_LONG ? argv[1].a_w.w_long : argv[1].a_w.w_float;
        float va = argv[2].a_type == A_LONG ? argv[2].a_w.w_long : argv[2].a_w.w_float;
        m_pRTC->m_motion->moveToward(vx, vy, va);
    }
}

void NAO_Motion_stopMove(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    post("stopMove");
    if(m_pRTC->isNAOConnected()) {
        m_pRTC->m_motion->stopMove();
    }
}

void NAO_TextToSpeech_say(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    post("say:%d", argc);
    if (argc == 0) {
        return;
    }
    if(m_pRTC->isNAOConnected()) {
        m_pRTC->m_textToSpeech->say(argv[0].a_w.w_sym->s_name);
    }
}

void NAO_BehaviorManager_runBehavior(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    post("runBehavior:%d", argc);
    if (argc == 0) {
        return;
    }
    if(m_pRTC->isNAOConnected()) {
        m_pRTC->m_behaviorManager->runBehavior(argv[0].a_w.w_sym->s_name);
    }
}

void NAO_BehaviorManager_stopBehavior(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    post("stopBehavior:%d", argc);
    if(m_pRTC->isNAOConnected()) {
        m_pRTC->m_behaviorManager->stopBehavior(argv[0].a_w.w_sym->s_name);
    }
}

void NAO_BehaviorManager_isBehaviorRunning(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    post("isBehaviorRunning:%d", argc);
    if (argc == 0) {
        return;
    }
    if(m_pRTC->isNAOConnected()) {
        t_atom *list_value = new t_atom[1];
        if(m_pRTC->m_behaviorManager->isBehaviorRunning(argv[0].a_w.w_sym->s_name)) {
            atom_setlong(list_value, 1);
        } else {
            atom_setlong(list_value, 0);
        }
        outlet_list((x)->m_outlet1, 0, 1, list_value);
        delete[] list_value;
    }
}

void NAO_BehaviorManager_isBehaviorInstalled(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    post("isBehaviorInstalled:%d", argc);
    if (argc == 0) {
        return;
    }
    if(m_pRTC->isNAOConnected()) {
        t_atom *list_value = new t_atom[1];
        if(m_pRTC->m_behaviorManager->isBehaviorInstalled(argv[0].a_w.w_sym->s_name)) {
            atom_setlong(list_value, 1);
        } else {
            atom_setlong(list_value, 0);
        }
        outlet_list((x)->m_outlet1, 0, 1, list_value);
        delete[] list_value;
    }
}

void NAO_BehaviorManager_stopAllBehaviors(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    post("stopAllBehaviors:%d", argc);
    if (argc == 0) {
        return;
    }
    if(m_pRTC->isNAOConnected()) {
        m_pRTC->m_behaviorManager->stopAllBehaviors();
    }
}

void NAO_BehaviorManager_getInstalledBehaviors(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    post("getInstalledBehaviors:%d", argc);
    if(m_pRTC->isNAOConnected()) {
        ssr::StringArray *sa = m_pRTC->m_behaviorManager->getInstalledBehaviors();
        t_atom *list_value = new t_atom[sa->data.length()];
        for(int i = 0;i < sa->data.length();i++) {
            
            atom_setsym(list_value+i, gensym(sa->data[i]));
        }
        outlet_list((x)->m_outlet1, 0, sa->data.length(), list_value);
        delete[] list_value;
        delete sa;
    }
}

void NAO_BehaviorManager_getRunningBehaviors(t_NAO_Motion *x, t_symbol *s, long argc, t_atom *argv){
    post("getRunningBehaviors:%d", argc);
    if(m_pRTC->isNAOConnected()) {
        ssr::StringArray *sa = m_pRTC->m_behaviorManager->getRunningBehaviors();
        t_atom *list_value = new t_atom[sa->data.length()];
        for(int i = 0;i < sa->data.length();i++) {
            
            atom_setsym(list_value+i, gensym(sa->data[i]));
        }
        outlet_list((x)->m_outlet1, 0, sa->data.length(), list_value);
        delete[] list_value;
        delete sa;
    }
}
void NAO_init(){
    NAO_Motion_class = class_new("NAO", (method)NAO_new, (method)NAO_free, (long)sizeof(t_NAO_Motion), 0L, A_GIMME, 0);
    
    class_addmethod(NAO_Motion_class, (method)NAO_Motion_setAngles, "setAngles", A_GIMME, 0);
    class_addmethod(NAO_Motion_class, (method)NAO_Motion_getAngles, "getAngles", A_GIMME, 0);
    class_addmethod(NAO_Motion_class, (method)NAO_Motion_setStiffnesses, "setStiffnesses", A_GIMME, 0);
    class_addmethod(NAO_Motion_class, (method)NAO_Motion_getStiffnesses, "getStiffnesses", A_GIMME, 0);
    class_addmethod(NAO_Motion_class, (method)NAO_Motion_moveTo, "moveTo", A_GIMME, 0);
    class_addmethod(NAO_Motion_class, (method)NAO_Motion_moveToward, "moveToward", A_GIMME, 0);
    class_addmethod(NAO_Motion_class, (method)NAO_Motion_stopMove, "stopMove", A_GIMME, 0);
    //class_addmethod(NAO_class, (method)NAO_write, "list", A_GIMME, 0);
    class_register(CLASS_BOX, NAO_Motion_class);
    
    
    NAO_TextToSpeech_class = class_new("NAO", (method)NAO_new, (method)NAO_free, (long)sizeof(t_NAO_TextToSpeech), 0L, A_GIMME, 0);
    
    class_addmethod(NAO_TextToSpeech_class, (method)NAO_TextToSpeech_say, "say", A_GIMME, 0);
    class_register(CLASS_BOX, NAO_TextToSpeech_class);
    
    NAO_BehaviorManager_class = class_new("NAO", (method)NAO_new, (method)NAO_free, (long)sizeof(t_NAO_BehaviorManager), 0L, A_GIMME, 0);
    
    class_addmethod(NAO_BehaviorManager_class, (method)NAO_BehaviorManager_runBehavior, "runBehavior", A_GIMME, 0);
    class_addmethod(NAO_BehaviorManager_class, (method)NAO_BehaviorManager_stopBehavior, "stopBehavior", A_GIMME, 0);
    class_addmethod(NAO_BehaviorManager_class, (method)NAO_BehaviorManager_isBehaviorRunning, "isBehaviorRunning", A_GIMME, 0);
    class_addmethod(NAO_BehaviorManager_class, (method)NAO_BehaviorManager_isBehaviorInstalled, "isBehaviorInstalled", A_GIMME, 0);
    class_addmethod(NAO_BehaviorManager_class, (method)NAO_BehaviorManager_stopAllBehaviors, "stopAllBehavior", A_GIMME, 0);
    class_addmethod(NAO_BehaviorManager_class, (method)NAO_BehaviorManager_getInstalledBehaviors, "getInstalledBehaviors", A_GIMME, 0);
    class_addmethod(NAO_BehaviorManager_class, (method)NAO_BehaviorManager_getRunningBehaviors, "getRunningBehaviors", A_GIMME, 0);
    
    class_register(CLASS_BOX, NAO_BehaviorManager_class);

}

/*
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
 */
