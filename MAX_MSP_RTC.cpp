// -*- C++ -*-
/*!
 * @file  MAX_MSP_RTC.cpp
 * @brief Max/Msp intermediate module 
 * @date $Date$
 *
 * $Id$
 */

#ifdef nil
#undef nil
#endif



#include "MAX_MSP_RTC.h"

#include "RTMPort.h"

#include "ext.h"
#include "ext_obex.h" // MAXプラグイン用ヘッダ

#include "LongIn.h"

#include "DoubleIn.h"
#include "Velocity2DIn.h"

// Module specification
// <rtc-template block="module_spec">
static const char* MAX_MSP_RTC_spec[] =
  {
    "implementation_id", "MAX_MSP_RTC",
    "type_name",         "MAX_MSP_RTC",
    "description",       "Max/Msp intermediate module ",
    "version",           "1.0.0",
    "vendor",            "Ogatalab",
    "category",          "MAX_MSP",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.debug", "0",
    // Widget
    "conf.__widget__.debug", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
MAX_MSP_RTC::MAX_MSP_RTC(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager)
    // </rtc-template>
{
    for (int i = 0;i < MAX_PORT;i++) {
        m_longOutOut[i] = NULL;
        m_longInIn[i] = NULL;
        m_doubleOutOut[i] = NULL;
        m_doubleInIn[i] = NULL;
        m_Velocity2DOutOut[i] = NULL;
        m_Velocity2DInIn[i]=NULL;
        
    }
}

/*!
 * @brief destructor
 */
MAX_MSP_RTC::~MAX_MSP_RTC()
{
    for (int i = 0;i < MAX_PORT;i++) {
        delete m_longOutOut[i];
        delete m_longInIn[i];
        delete m_doubleOutOut[i];
        delete m_doubleInIn[i];
        delete m_Velocity2DOutOut[i];
        delete m_Velocity2DInIn[i];
    }
}
////----------------------long-----------------------/////
int MAX_MSP_RTC::addLongOutPort(const char* name) {
    for (int i = 0;i < MAX_PORT;i++) {
        if (m_longOutOut[i] == NULL) {
            m_longOutOut[i] = new OutPort<TimedLong>(name, m_longOut[i]);
            addOutPort(name, *m_longOutOut[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deleteLongOutPort(const int id) {
    if (id < MAX_PORT && id >= 0) {
        if (m_longOutOut[id] != NULL) {
            this->deletePort(*(m_longOutOut[id]));
            delete m_longOutOut[id];
            m_longOutOut[id] = NULL;
        }
    }
}

int MAX_MSP_RTC::addLongInPort(t_object* x, const char* name) {
    for (int i = 0;i < MAX_PORT;i++) {
        if (m_longInIn[i] == NULL) {
            m_longInIn[i] = new InPort<TimedLong>(name, m_longIn[i]);
            m_longObjectList[i] = x;
            addInPort(name, *m_longInIn[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deleteLongInPort(const int id) {
    if (id < MAX_PORT && id >= 0) {
        if (m_longInIn[id] != NULL) {
            this->deletePort(*(m_longInIn[id]));
            delete m_longInIn[id];
            m_longInIn[id] = NULL;
        }
    }
}
////----------------------double-----------------------/////
int MAX_MSP_RTC::addDoubleOutPort(const char* name) {
    for (int i = 0;i < MAX_PORT;i++) {
        if (m_doubleOutOut[i] == NULL) {
            m_doubleOutOut[i] = new OutPort<TimedDouble>(name, m_doubleOut[i]);
            addOutPort(name, *m_doubleOutOut[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deleteDoubleOutPort(const int id) {
    if (id < MAX_PORT && id >= 0) {
        if (m_doubleOutOut[id] != NULL) {
            this->deletePort(*(m_doubleOutOut[id]));
            delete m_doubleOutOut[id];
            m_doubleOutOut[id] = NULL;
        }
    }
}

int MAX_MSP_RTC::addDoubleInPort(t_object* x, const char* name) {
    for (int i = 0;i < MAX_PORT;i++) {
        if (m_doubleInIn[i] == NULL) {
            m_doubleInIn[i] = new InPort<TimedDouble>(name, m_doubleIn[i]);
            m_doubleObjectList[i] = x;
            addInPort(name, *m_doubleInIn[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deleteDoubleInPort(const int id) {
    if (id < MAX_PORT && id >= 0) {
        if (m_doubleInIn[id] != NULL) {
            this->deletePort(*(m_doubleInIn[id]));
            delete m_doubleInIn[id];
            m_doubleInIn[id] = NULL;
        }
    }
}

////----------------------velocity2d-----------------------/////

int MAX_MSP_RTC::addVelocity2DOutPort(const char* name){
    for (int i = 0; i < MAX_PORT; i++) {
        if (m_Velocity2DOutOut[i] == NULL) {
            m_Velocity2DOutOut[i] = new OutPort<TimedVelocity2D>(name, m_Velocity2DOut[i]);
            addOutPort(name, *m_Velocity2DOutOut[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deleteVelocity2DOutPort(const int id){
    if (id < MAX_PORT && id >= 0) {
        if (m_Velocity2DOutOut[id] != NULL) {
            this->deletePort(*(m_Velocity2DOutOut[id]));
            delete m_Velocity2DOutOut[id];
            m_Velocity2DOutOut[id] = NULL;
            
        }
    }
}

int MAX_MSP_RTC::addVelocity2DInPort(t_object* x, const char* name){
    for (int i = 0; i < MAX_PORT; i++) {
        if (m_Velocity2DInIn[i] == NULL) {
            m_Velocity2DInIn[i] = new InPort<TimedVelocity2D>(name, m_Velocity2DIn[i]);
            m_Velocity2DObjectList[i] = x;
            addInPort(name, *m_Velocity2DInIn[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deleteVelocity2DInPort(const int id){
    if (id < MAX_PORT && id >= 0) {
        if (m_Velocity2DInIn[id] != NULL) {
            this->deletePort(*(m_Velocity2DInIn[id]));
            delete m_Velocity2DInIn[id];
            m_Velocity2DInIn[id] = NULL;
        }
    }
}


RTC::ReturnCode_t MAX_MSP_RTC::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("debug", m_debug, "0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t MAX_MSP_RTC::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MAX_MSP_RTC::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MAX_MSP_RTC::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t MAX_MSP_RTC::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MAX_MSP_RTC::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MAX_MSP_RTC::onExecute(RTC::UniqueId ec_id)
{
    for (int i = 0;i < MAX_PORT;i++) {
        if (m_longInIn[i] != NULL) {
            if (m_longInIn[i]->isNew()) {
                m_longInIn[i]->read();
                LongIn_write(m_longObjectList[i], m_longIn[i].data);
            }
        }
    }
    
    for (int i = 0;i < MAX_PORT;i++) {
        if (m_doubleInIn[i] != NULL) {
            if (m_doubleInIn[i]->isNew()) {
                m_doubleInIn[i]->read();
                DoubleIn_write(m_doubleObjectList[i], m_doubleIn[i].data);
            }
        }
    }
    
    for (int i = 0;i < MAX_PORT;i++) {
        if (m_Velocity2DInIn[i] != NULL) {
            if (m_Velocity2DInIn[i]->isNew()) {
                m_Velocity2DInIn[i]->read();
                Velocity2DIn_write(m_Velocity2DObjectList[i], m_Velocity2DIn[i].data.vx, m_Velocity2DIn[i].data.vy, m_Velocity2DIn[i].data.va);
            }
        }
    }
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t MAX_MSP_RTC::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MAX_MSP_RTC::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MAX_MSP_RTC::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MAX_MSP_RTC::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MAX_MSP_RTC::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void MAX_MSP_RTCInit(RTC::Manager* manager)
  {
    coil::Properties profile(MAX_MSP_RTC_spec);
    manager->registerFactory(profile,
                             RTC::Create<MAX_MSP_RTC>,
                             RTC::Delete<MAX_MSP_RTC>);
  }
  
};