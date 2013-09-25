//
//  BooleanSeqOut.h
//  RTMPort-x86_64
//
//  Created by 菅 佑樹 on 2013/08/21.
//
//

#ifndef RTMPort_x86_64_BooleanSeqOut_h
#define RTMPort_x86_64_BooleanSeqOut_h

#include "RTMPort.h"

//double vx, double vy, double va
/**
 * MAX用オブジェクト
 */
typedef struct _BooleanSeqOut
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    int portId;
} t_BooleanSeqOut;

void BooleanSeqOut_init();
void *BooleanSeqOut_new(t_symbol *s, long argc, t_atom *argv);

#endif
