//
//  BooleanSeqIn.h
//  RTMPort-x86_64
//
//  Created by 菅 佑樹 on 2013/08/21.
//
//

#ifndef RTMPort_x86_64_BooleanSeqIn_h
#define RTMPort_x86_64_BooleanSeqIn_h

#include "RTMPort.h"

/**
 * MAX用オブジェクト
 */
typedef struct _BooleanSeqIn
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    void *m_outlet1;
    int portId;
} t_BooleanSeqIn;

void BooleanSeqIn_init();
void BooleanSeqIn_write(t_object *x, double right_bumper, double center_bumper, double left_bumper);
void *BooleanSeqIn_new(t_symbol *s, long argc, t_atom *argv);

#endif
