//
//  UShortOut.h
//  RTMPort-x86_64
//
//  Created by 菅 佑樹 on 2013/08/21.
//
//

#ifndef RTMPort_x86_64_UShortOut_h
#define RTMPort_x86_64_UShortOut_h

#include "RTMPort.h"


/**
 * MAX用オブジェクト
 */
typedef struct _UShortOut
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    int portId;
} t_UShortOut;

void UShortOut_init();
void *UShortOut_new(t_symbol *s, long argc, t_atom *argv);

#endif
