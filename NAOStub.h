// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file NAOStub.h 
 * @brief NAO client stub header wrapper code
 * @date Mon Dec 16 15:33:22 2013 
 *
 */

#ifndef _NAOSTUB_H
#define _NAOSTUB_H



#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "NAOC.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "NAO.hh"
#elif defined ORB_IS_MICO
#  include "NAO.h"
#elif defined ORB_IS_ORBIT2
#  include "NAO-cpp-stubs.h"
#elif defined ORB_IS_RTORB
#  include "NAO.h"
#else
#  error "NO ORB defined"
#endif

#endif // _NAOSTUB_H
