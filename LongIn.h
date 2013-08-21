//
//  LongIn.h
//  RTMPort-x86_64
//
//  Created by 菅 佑樹 on 2013/08/21.
//
//

#ifndef RTMPort_x86_64_LongIn_h
#define RTMPort_x86_64_LongIn_h

#include "RTMPort.h"

/**
 * MAX用オブジェクト
 */
typedef struct _LongIn
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    void *m_outlet;
    int portId;
} t_LongIn;

void LongIn_init();
void LongIn_write(t_object *x, long m);
void *LongIn_new(t_symbol *s, long argc, t_atom *argv);

#endif
