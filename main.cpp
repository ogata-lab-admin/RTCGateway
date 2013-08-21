/**
 * @file RTMPort.cpp
 * @author Yuki Suga (Sugar Sweet Robotics / Ogata Lab. Waseda Univ.)
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


int C74_EXPORT main(void)
{
    RTM_init();
    
    RTCGateway_init();

    LongIn_init();
    LongOut_init();

    
	return 0;
}

