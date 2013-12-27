//
//  DoubleOut.h
//  RTMPort-x86_64
//
//  Created by kazuma sasaki@ogata-lab on 2013/08/21.
//
//

#ifndef RTMPort_x86_64_DoubleOut_h
#define RTMPort_x86_64_DoubleOut_h

#include "RTMPort.h"


/**
 * MAX用オブジェクト
 */
typedef struct _DoubleOut
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    int portId;
} t_DoubleOut;

void DoubleOut_init();
void *DoubleOut_new(t_symbol *s, long argc, t_atom *argv);

#endif
