//
//  LongOut.h
//  RTMPort-x86_64
//
//  Created by 菅 佑樹 on 2013/08/21.
//
//

#ifndef RTMPort_x86_64_LongOut_h
#define RTMPort_x86_64_LongOut_h

#include "RTMPort.h"


/**
 * MAX用オブジェクト
 */
typedef struct _LongOut
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    int portId;
} t_LongOut;

void LongOut_init();
void *LongOut_new(t_symbol *s, long argc, t_atom *argv);

#endif
