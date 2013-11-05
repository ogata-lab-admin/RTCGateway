//
//  Point2DOut.h
//  RTMPort-x86_64
//
//  Created by 菅 佑樹 on 2013/08/21.
//
//

#ifndef RTMPort_x86_64_Point2DOut_h
#define RTMPort_x86_64_Point2DOut_h

#include "RTMPort.h"

//double vx, double vy, double va
/**
 * MAX用オブジェクト
 */
typedef struct _Point2DOut
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    int portId;
} t_Point2DOut;

void Point2DOut_init();
void *Point2DOut_new(t_symbol *s, long argc, t_atom *argv);

#endif
