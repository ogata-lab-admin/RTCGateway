//
//  Velocity2DOut.h
//  RTMPort-x86_64
//
//  Created by kazuma sasaki@ogata-lab on 2013/08/21.
//
//

#ifndef RTMPort_x86_64_Velocity2DOut_h
#define RTMPort_x86_64_Velocity2DOut_h

#include "RTMPort.h"

//double vx, double vy, double va
/**
 * MAX用オブジェクト
 */
typedef struct _Velocity2DOut
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    int portId;
} t_Velocity2DOut;

void Velocity2DOut_init();
void *Velocity2DOut_new(t_symbol *s, long argc, t_atom *argv);

#endif
