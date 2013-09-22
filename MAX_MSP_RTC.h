// -*- C++ -*-
/*!
 * @file  MAX_MSP_RTC.h
 * @brief Max/Msp intermediate module 
 * @date  $Date$
 *
 * $Id$
 */

#ifndef MAX_MSP_RTC_H
#define MAX_MSP_RTC_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

#include "ext.h"
#include "ext_obex.h"

/*!
 * @class MAX_MSP_RTC
 * @brief Max/Msp intermediate module 
 *
 */
class MAX_MSP_RTC
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  MAX_MSP_RTC(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~MAX_MSP_RTC();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 
   * - Name:  debug
   * - DefaultValue: 0
   */
  int m_debug;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">

  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

public:
    
#define MAX_PORT 16
    /*
     --Todo--
     inPort: battery TimedDouble, crrentPose TimedPose2D, bumper TimedBooleanSeq
     outPort : targetVelocity TimedVelocity2D, poseUpdated TimedPose2D
     
     */
    
    //====================================
    // For TimePose2D OutPort
    RTC::TimedPose2D m_Pose2DOut[MAX_PORT];
    OutPort<RTC::TimedPose2D>* m_Pose2DOutOut[MAX_PORT];
    
    int addPose2DOutPort(const char* name);
    void deletePose2DOutPort(const int id);
    
    // Fro TimedPose2D InPort
    RTC::TimedPose2D m_Pose2DIn[MAX_PORT];
    InPort<RTC::TimedPose2D>* m_Pose2DInIn[MAX_PORT];
    t_object* m_Pose2DObjectList[MAX_PORT];
    
    int addPose2DInPort(t_object *x, const char* name);
    void deletePose2DInPort(const int id);
    
    // For TimedVelocity2D OutPort
    RTC::TimedVelocity2D m_Velocity2DOut[MAX_PORT];
    OutPort<RTC::TimedVelocity2D>* m_Velocity2DOutOut[MAX_PORT];
    
    int addVelocity2DOutPort(const char* name);
    void deleteVelocity2DOutPort(const int id);
    
    // For TimedVelocity2D Inport
    RTC::TimedVelocity2D m_Velocity2DIn[MAX_PORT];
    InPort<RTC::TimedVelocity2D>* m_Velocity2DInIn[MAX_PORT];
    t_object* m_Velocity2DObjectList[MAX_PORT];
    
    int addVelocity2DInPort(t_object *x, const char* name);
    void deleteVelocity2DInPort(const int id);
    
    
    // For TimedLong OutPort
    RTC::TimedLong m_longOut[MAX_PORT];
    OutPort<RTC::TimedLong>* m_longOutOut[MAX_PORT];
    
    int addLongOutPort(const char* name);
    void deleteLongOutPort(const int id);

    // For TimedLong InPort
    RTC::TimedLong m_longIn[MAX_PORT];
    InPort<RTC::TimedLong>* m_longInIn[MAX_PORT];
    t_object* m_longObjectList[MAX_PORT];

    int addLongInPort(t_object *x, const char* name);
    void deleteLongInPort(const int id);
    
    // For Timeddouble OutPort
    RTC::TimedDouble m_doubleOut[MAX_PORT];
    OutPort<RTC::TimedDouble>* m_doubleOutOut[MAX_PORT];
    
    int addDoubleOutPort(const char* name);
    void deleteDoubleOutPort(const int id);
    
    // For TimedLong InPort
    RTC::TimedDouble m_doubleIn[MAX_PORT];
    InPort<RTC::TimedDouble>* m_doubleInIn[MAX_PORT];
    t_object* m_doubleObjectList[MAX_PORT];
    
    int addDoubleInPort(t_object *x, const char* name);
    void deleteDoubleInPort(const int id);

};


extern "C"
{
  DLL_EXPORT void MAX_MSP_RTCInit(RTC::Manager* manager);
};

#endif // MAX_MSP_RTC_H
