//
//  Point2DIn.h
//  RTMPort-x86_64
//
//  Created by 菅 佑樹 on 2013/08/21.
//
//

#ifndef RTMPort_x86_64_Point2DIn_h
#define RTMPort_x86_64_Point2DIn_h

#include "RTMPort.h"

/**
 * MAX用オブジェクト
 */
typedef struct _Point2DIn
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    void *m_outlet1;
    int portId;
} t_Point2DIn;

void Point2DIn_init();
void Point2DIn_write(t_object *x, double px, double py);
void *Point2DIn_new(t_symbol *s, long argc, t_atom *argv);

#endif
