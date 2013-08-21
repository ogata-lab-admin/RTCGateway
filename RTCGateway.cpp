//
//  RTCGateway.cpp
//  RTCGateway-x86_64
//
//  Created by 菅 佑樹 on 2013/08/21.
//
//

#include "RTCGateway.h"


#include <iostream>
#include <fstream>

#ifdef nil
#undef nil
#endif


#include "MAX_MSP_RTC.h"

#include "ext.h" // MAXプラグイン用ヘッダ
#include "ext_obex.h" // MAXプラグイン用ヘッダ

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

/**
 * MAX用オブジェクト
 */
typedef struct _RTCGateway
{
    t_object ob; // MAXオブジェクトデータ（構造体の先頭固定）
} t_RTCGateway;

// 関数のプロトタイプ宣言
void *RTCGateway_new(t_symbol *s, long argc, t_atom *argv);
void RTCGateway_free(t_RTCGateway *x);

void RTCGateway_activate(t_RTCGateway *x, long m);
void RTCGateway_deactivate(t_RTCGateway *x, long m);
void RTCGateway_reset(t_RTCGateway *x, long m);


t_class *RTCGateway_class;


static RTC::Manager* manager = NULL;
static int ref_count = 0;
MAX_MSP_RTC* m_pRTC;

void MyModuleInit(RTC::Manager* manager)
{
    MAX_MSP_RTCInit(manager);
    
    // Create a component
    if(m_pRTC==NULL) {
        m_pRTC = (MAX_MSP_RTC*)manager->createComponent("MAX_MSP_RTC?naming.formats=%m.rtc");
        if (m_pRTC==NULL)
        {
            post("Component create failed.");
            abort();
        }
    }
    
    // Example
    // The following procedure is examples how handle RT-Components.
    // These should not be in this function.
    
    // Get the component's object reference
    //  RTC::RTObject_var rtobj;
    //  rtobj = RTC::RTObject::_narrow(manager->getPOA()->servant_to_reference(comp));
    
    // Get the port list of the component
    //  PortServiceList* portlist;
    //  portlist = rtobj->get_ports();
    
    // getting port profiles
    //  std::cout << "Number of Ports: ";
    //  std::cout << portlist->length() << std::endl << std::endl;
    //  for (CORBA::ULong i(0), n(portlist->length()); i < n; ++i)
    //  {
    //    PortService_ptr port;
    //    port = (*portlist)[i];
    //    std::cout << "Port" << i << " (name): ";
    //    std::cout << port->get_port_profile()->name << std::endl;
    //
    //    RTC::PortInterfaceProfileList iflist;
    //    iflist = port->get_port_profile()->interfaces;
    //    std::cout << "---interfaces---" << std::endl;
    //    for (CORBA::ULong i(0), n(iflist.length()); i < n; ++i)
    //    {
    //      std::cout << "I/F name: ";
    //      std::cout << iflist[i].instance_name << std::endl;
    //      std::cout << "I/F type: ";
    //      std::cout << iflist[i].type_name << std::endl;
    //      const char* pol;
    //      pol = iflist[i].polarity == 0 ? "PROVIDED" : "REQUIRED";
    //      std::cout << "Polarity: " << pol << std::endl;
    //    }
    //    std::cout << "---properties---" << std::endl;
    //    NVUtil::dump(port->get_port_profile()->properties);
    //    std::cout << "----------------" << std::endl << std::endl;
    //  }
    
    return;
}


void RTCGateway_init()
{
    RTCGateway_class = class_new("RTCGateway", (method)RTCGateway_new, (method)RTCGateway_free, (long)sizeof(t_RTCGateway),
                                         0L, A_GIMME, 0);
    class_addmethod(RTCGateway_class, (method)RTCGateway_activate, "activate", A_DEFLONG, 0);
    class_addmethod(RTCGateway_class, (method)RTCGateway_deactivate, "deactivate", A_DEFLONG, 0);
    class_addmethod(RTCGateway_class, (method)RTCGateway_reset, "reset", A_DEFLONG, 0);
    class_register(CLASS_BOX, RTCGateway_class);
}

void *RTCGateway_new(t_symbol *s, long argc, t_atom *argv)
{
    t_RTCGateway *x = NULL;
    if (argc == 0) {
        post("RTCGateway may accept one argument which is to be an RTC's name.");
    }
    
	x = (t_RTCGateway *)object_alloc((t_class*)RTCGateway_class);
    
    if (manager == NULL) {
        int argc = 1;
        char pgm[] = "RTCGateway";
        char* argv[] = {pgm};
        manager = RTC::Manager::init(argc, argv);
        manager->init(argc, argv);
        manager->setModuleInitProc(MyModuleInit);
        manager->activateManager();
        manager->runManager(true);
    }
    ref_count ++;

    return x;
}

void RTCGateway_free(t_RTCGateway *x)
{
    ref_count--;
    if (ref_count==0) {
        manager->cleanupComponents();
        manager->shutdown();
    }
}

void RTCGateway_activate(t_RTCGateway *x, long m)
{
    RTC::RTObject_var rtobj = RTC::RTObject::_narrow(manager->getPOA()->servant_to_reference(m_pRTC));
    (*(rtobj->get_owned_contexts()))[0]->activate_component(rtobj);
}

void RTCGateway_deactivate(t_RTCGateway *x, long m)
{
    RTC::RTObject_var rtobj = RTC::RTObject::_narrow(manager->getPOA()->servant_to_reference(m_pRTC));
    (*(rtobj->get_owned_contexts()))[0]->deactivate_component(rtobj);
}

void RTCGateway_reset(t_RTCGateway *x, long m)
{
    RTC::RTObject_var rtobj = RTC::RTObject::_narrow(manager->getPOA()->servant_to_reference(m_pRTC));
    (*(rtobj->get_owned_contexts()))[0]->reset_component(rtobj);
}