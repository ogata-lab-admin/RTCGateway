//
//  Velocity2DIn.h
//  RTMPort-x86_64
//
//  Created by 菅 佑樹 on 2013/08/21.
//
//

#ifndef RTMPort_x86_64_Velocity2DIn_h
#define RTMPort_x86_64_Velocity2DIn_h

#include "RTMPort.h"

/**
 * MAX用オブジェクト
 */
typedef struct _Velocity2DIn
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    void *m_outlet1;
    int portId;
} t_Velocity2DIn;

void Velocity2DIn_init();
void Velocity2DIn_write(t_object *x, double vx, double vy, double va);
void *Velocity2DIn_new(t_symbol *s, long argc, t_atom *argv);

#endif
