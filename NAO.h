//
//  NAO.h
//  RTMPort-x86_64
//
//  Created by 菅 佑樹 on 2013/08/21.
//
//

#ifndef RTMPort_x86_64_NAO_h
#define RTMPort_x86_64_NAO_h

#include "RTMPort.h"
#include <vector>
#include <string>


/**
 * MAX用オブジェクト
 */
typedef struct _NAO_Motion
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    int portId;
    void *m_outlet1;
} t_NAO_Motion;

typedef struct _NAO_TextToSpeech
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    int portId;
} t_NAO_TextToSpeech;

typedef struct _NAO_BehaviorManager
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
    int portId;
    void *m_outlet1;
} t_NAO_BehaviorManager;

void NAO_init();
void *NAO_new(t_symbol *s, long argc, t_atom *argv);

#endif
