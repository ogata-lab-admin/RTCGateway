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
#include "Pose2DIn.h"
#include "BooleanSeqIn.h"
#include "Point2DIn.h"
#include "UShortIn.h"

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
  : RTC::DataFlowComponentBase(manager),
m_NAOServicePort("NAOService"), m_NAOPort_usage_count(0)
    // </rtc-template>
{
    for (int i = 0;i < MAX_PORT;i++) {
        m_UShortInIn[i] = NULL;
        m_UShortOutOut[i] = NULL;
        m_Point2DInIn[i] = NULL;
        m_Point2DOutOut[i] = NULL;
        m_BooleanSeqInIn[i] = NULL;
        m_BooleanSeqOutOut[i] = NULL;
        m_Pose2DInIn[i] = NULL;
        m_Pose2DOutOut[i] = NULL;
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
        delete m_UShortInIn[i];
        delete m_UShortOutOut[i];
        delete m_Point2DInIn[i];
        delete m_Point2DOutOut[i];
        delete m_BooleanSeqInIn[i];
        delete m_BooleanSeqOutOut[i];
        delete m_Pose2DInIn[i];
        delete m_Pose2DOutOut[i];
        delete m_longOutOut[i];
        delete m_longInIn[i];
        delete m_doubleOutOut[i];
        delete m_doubleInIn[i];
        delete m_Velocity2DOutOut[i];
        delete m_Velocity2DInIn[i];
    }
}

int MAX_MSP_RTC::addNAOPort() {
    // Set service consumers to Ports
    m_NAOServicePort.registerConsumer("ALMotion", "ssr::ALMotion", m_motion);
    m_NAOServicePort.registerConsumer("ALTextToSpeech", "ssr::ALTextToSpeech", m_textToSpeech);
    m_NAOServicePort.registerConsumer("ALBehaviorManager", "ssr::ALBehaviorManager", m_behaviorManager);
    m_NAOServicePort.registerConsumer("ALMemory", "ssr::ALMemory", m_memory);
    m_NAOServicePort.registerConsumer("ALVideoDevice", "ssr::ALVideoDevice", m_videoDevice);
    m_NAOServicePort.registerConsumer("ALLeds", "ssr::ALLeds", m_leds);
    
    // Set CORBA Service Ports
    addPort(m_NAOServicePort);
    
    m_NAOPort_usage_count++;
    return 0;
}

void MAX_MSP_RTC::deleteNAOPort() {
    m_NAOPort_usage_count--;
    if(m_NAOPort_usage_count == 0) {
        deletePort(m_NAOServicePort);
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


////----------------------pose2d-----------------------/////

int MAX_MSP_RTC::addPose2DOutPort(const char* name){
    for (int i = 0; i < MAX_PORT; i++) {
        if (m_Pose2DOutOut[i] == NULL) {
            m_Pose2DOutOut[i] = new OutPort<TimedPose2D>(name, m_Pose2DOut[i]);
            addOutPort(name, *m_Pose2DOutOut[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deletePose2DOutPort(const int id){
    if (id < MAX_PORT && id >= 0) {
        if (m_Pose2DOutOut[id] != NULL) {
            this->deletePort(*(m_Pose2DOutOut[id]));
            delete m_Pose2DOutOut[id];
            m_Pose2DOutOut[id] = NULL;
            
        }
    }
}

int MAX_MSP_RTC::addPose2DInPort(t_object* x, const char* name){
    for (int i = 0; i < MAX_PORT; i++) {
        if (m_Pose2DInIn[i] == NULL) {
            m_Pose2DInIn[i] = new InPort<TimedPose2D>(name, m_Pose2DIn[i]);
            m_Pose2DObjectList[i] = x;
            addInPort(name, *m_Pose2DInIn[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deletePose2DInPort(const int id){
    if (id < MAX_PORT && id >= 0) {
        if (m_Pose2DInIn[id] != NULL) {
            this->deletePort(*(m_Pose2DInIn[id]));
            delete m_Pose2DInIn[id];
            m_Pose2DInIn[id] = NULL;
        }
    }
}

////----------------------booleanseq-----------------------/////

int MAX_MSP_RTC::addBooleanSeqOutPort(const char* name){
    for (int i = 0; i < MAX_PORT; i++) {
        if (m_BooleanSeqOutOut[i] == NULL) {
            m_BooleanSeqOutOut[i] = new OutPort<TimedBooleanSeq>(name, m_BooleanSeqOut[i]);
            addOutPort(name, *m_BooleanSeqOutOut[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deleteBooleanSeqOutPort(const int id){
    if (id < MAX_PORT && id >= 0) {
        if (m_BooleanSeqOutOut[id] != NULL) {
            this->deletePort(*(m_BooleanSeqOutOut[id]));
            delete m_BooleanSeqOutOut[id];
            m_BooleanSeqOutOut[id] = NULL;
            
        }
    }
}

int MAX_MSP_RTC::addBooleanSeqInPort(t_object* x, const char* name){
    for (int i = 0; i < MAX_PORT; i++) {
        if (m_BooleanSeqInIn[i] == NULL) {
            m_BooleanSeqInIn[i] = new InPort<TimedBooleanSeq>(name, m_BooleanSeqIn[i]);
            m_BooleanSeqObjectList[i] = x;
            addInPort(name, *m_BooleanSeqInIn[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deleteBooleanSeqInPort(const int id){
    if (id < MAX_PORT && id >= 0) {
        if (m_BooleanSeqInIn[id] != NULL) {
            this->deletePort(*(m_BooleanSeqInIn[id]));
            delete m_BooleanSeqInIn[id];
            m_BooleanSeqInIn[id] = NULL;
        }
    }
}

////----------------------point2d-----------------------/////

int MAX_MSP_RTC::addPoint2DOutPort(const char* name){
    for (int i = 0; i < MAX_PORT; i++) {
        if (m_Point2DOutOut[i] == NULL) {
            m_Point2DOutOut[i] = new OutPort<TimedPoint2D>(name, m_Point2DOut[i]);
            addOutPort(name, *m_Point2DOutOut[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deletePoint2DOutPort(const int id){
    if (id < MAX_PORT && id >= 0) {
        if (m_Point2DOutOut[id] != NULL) {
            this->deletePort(*(m_Point2DOutOut[id]));
            delete m_Point2DOutOut[id];
            m_Point2DOutOut[id] = NULL;
            
        }
    }
}

int MAX_MSP_RTC::addPoint2DInPort(t_object* x, const char* name){
    for (int i = 0; i < MAX_PORT; i++) {
        if (m_Point2DInIn[i] == NULL) {
            m_Point2DInIn[i] = new InPort<TimedPoint2D>(name, m_Point2DIn[i]);
            m_Point2DObjectList[i] = x;
            addInPort(name, *m_Point2DInIn[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deletePoint2DInPort(const int id){
    if (id < MAX_PORT && id >= 0) {
        if (m_Point2DInIn[id] != NULL) {
            this->deletePort(*(m_Point2DInIn[id]));
            delete m_Point2DInIn[id];
            m_Point2DInIn[id] = NULL;
        }
    }
}

////----------------------UShort-----------------------/////
int MAX_MSP_RTC::addUShortOutPort(const char* name) {
    for (int i = 0;i < MAX_PORT;i++) {
        if (m_UShortOutOut[i] == NULL) {
            m_UShortOutOut[i] = new OutPort<TimedUShort>(name, m_UShortOut[i]);
            addOutPort(name, *m_UShortOutOut[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deleteUShortOutPort(const int id) {
    if (id < MAX_PORT && id >= 0) {
        if (m_UShortOutOut[id] != NULL) {
            this->deletePort(*(m_UShortOutOut[id]));
            delete m_UShortOutOut[id];
            m_UShortOutOut[id] = NULL;
        }
    }
}

int MAX_MSP_RTC::addUShortInPort(t_object* x, const char* name) {
    for (int i = 0;i < MAX_PORT;i++) {
        if (m_UShortInIn[i] == NULL) {
            m_UShortInIn[i] = new InPort<TimedUShort>(name, m_UShortIn[i]);
            m_UShortObjectList[i] = x;
            addInPort(name, *m_UShortInIn[i]);
            return i;
        }
    }
    return -1;
}

void MAX_MSP_RTC::deleteUShortInPort(const int id) {
    if (id < MAX_PORT && id >= 0) {
        if (m_UShortInIn[id] != NULL) {
            this->deletePort(*(m_UShortInIn[id]));
            delete m_UShortInIn[id];
            m_UShortInIn[id] = NULL;
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
    for (int i = 0; i < MAX_PORT; i++) {
        if (m_BooleanSeqInIn[i] != NULL) {
            m_BooleanSeqIn[i].data.length(28);
        }
    }
    
    for (int i = 0; i < MAX_PORT; i++) {
        if (m_BooleanSeqOutOut[i] != NULL) {
            m_BooleanSeqOut[i].data.length(4);
        }
    }
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
    
    for (int i = 0;i < MAX_PORT;i++) {
        if (m_Pose2DInIn[i] != NULL) {
            if (m_Pose2DInIn[i]->isNew()) {
                m_Pose2DInIn[i]->read();
                Pose2DIn_write(m_Pose2DObjectList[i], m_Pose2DIn[i].data.position.x, m_Pose2DIn[i].data.position.y, m_Pose2DIn[i].data.heading);
            }
        }
    }
    for (int i = 0;i < MAX_PORT;i++) {
        if (m_BooleanSeqInIn[i] != NULL) {
            if (m_BooleanSeqInIn[i]->isNew()) {
                m_BooleanSeqInIn[i]->read();
                BooleanSeqIn_write(m_BooleanSeqObjectList[i], m_BooleanSeqIn[i].data.length(), &(m_BooleanSeqIn[i].data[0]));
            }
        }
    }
    
    for (int i = 0;i < MAX_PORT;i++) {
        if (m_Point2DInIn[i] != NULL) {
            if (m_Point2DInIn[i]->isNew()) {
                m_Point2DInIn[i]->read();
                Point2DIn_write(m_Point2DObjectList[i], m_Point2DIn[i].data.x, m_Point2DIn[i].data.y);
            }
        }
    }
    
    for (int i = 0;i < MAX_PORT;i++) {
        if (m_UShortInIn[i] != NULL) {
            if (m_UShortInIn[i]->isNew()) {
                m_UShortInIn[i]->read();
                UShortIn_write(m_UShortObjectList[i], m_UShortIn[i].data);
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
