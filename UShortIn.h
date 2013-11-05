//
//  UShortIn.h
//  RTMPort-x86_64
//
//  Created by 菅 佑樹 on 2013/08/21.
//
//

#ifndef RTMPort_x86_64_UShortIn_h
#define RTMPort_x86_64_UShortIn_h

#include "RTMPort.h"

/**
 * MAX用オブジェクト
 */
typedef struct _UShortIn
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    void *m_outlet;
    int portId;
} t_UShortIn;

void UShortIn_init();
void UShortIn_write(t_object *x, int m);
void *UShortIn_new(t_symbol *s, long argc, t_atom *argv);

#endif
