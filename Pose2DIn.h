//
//  Pose2DIn.h
//  RTMPort-x86_64
//
//  Created by kazuma sasaki@ogata-lab on 2013/08/21.
//
//

#ifndef RTMPort_x86_64_Pose2DIn_h
#define RTMPort_x86_64_Pose2DIn_h

#include "RTMPort.h"

/**
 * MAX用オブジェクト
 */
typedef struct _Pose2DIn
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    void *m_outlet1;
    int portId;
} t_Pose2DIn;

void Pose2DIn_init();
void Pose2DIn_write(t_object *x, double px, double py, double heading);
void *Pose2DIn_new(t_symbol *s, long argc, t_atom *argv);

#endif
