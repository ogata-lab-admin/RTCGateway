/**
 * @file RTMPort.cpp
 * @author Yuki Suga (Sugar Sweet Robotics / Ogata Lab. Waseda Univ.), Kazuma Sasaki (Ogata Lab.)
 * @url http://ogata-lab.jp
 * @license MIT License
 * @copyright 2013, Ogata Laboratory, Waseda University
 */

#include "ext.h" // MAXプラグイン用ヘッダ
#include "ext_obex.h" // MAXプラグイン用ヘッダ
#include "RTMPort.h" // RTCとの連絡用関数宣言
#include "RTCGateway.h"
#include "LongIn.h"
#include "LongOut.h"
#include "DoubleIn.h"
#include "DoubleOut.h"
#include "Velocity2DIn.h"
#include "Velocity2DOut.h"
#include "Pose2DIn.h"
#include "Pose2DOut.h"
#include "BooleanSeqIn.h"
#include "BooleanSeqOut.h"
#include "Point2DIn.h"
#include "Point2DOut.h"
#include "UShortIn.h"
#include "UShortOut.h"
#include "NAO.h"

int C74_EXPORT main(void)
{
    post("main function called.");
    //RTM_init((t_object*)NULL);
    
    RTCGateway_init();

    LongIn_init();
    LongOut_init();
    DoubleIn_init();
    DoubleOut_init();
    
    /// Add by ysuga 20130920
    Velocity2DIn_init();
    Velocity2DOut_init();
    
    Pose2DIn_init();
    Pose2DOut_init();

    BooleanSeqIn_init();
    BooleanSeqOut_init();
    
    Point2DIn_init();
    Point2DOut_init();
    
    UShortIn_init();
    UShortOut_init();
    
    NAO_init();

    return 0;
}

