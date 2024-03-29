//
//  RTCGateway.cpp
//  RTCGateway-x86_64
//
//  Author: Yuki Suga, Kazuma Sasaki
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
    RTCGateway_class = class_new("RTC", (method)RTCGateway_new, (method)RTCGateway_free, (long)sizeof(t_RTCGateway),
                                         0L, A_GIMME, 0);
    class_addmethod(RTCGateway_class, (method)RTCGateway_activate, "activate", A_DEFLONG, 0);
    class_addmethod(RTCGateway_class, (method)RTCGateway_deactivate, "deactivate", A_DEFLONG, 0);
    class_addmethod(RTCGateway_class, (method)RTCGateway_reset, "reset", A_DEFLONG, 0);
    class_register(CLASS_BOX, RTCGateway_class);
}


void RTM_init(t_object *x)
{
    if (manager == NULL) {
        int argc = 3;
        //char pgm[] = "RTCGateway";
        
        t_object *mypatcher;
        
        object_obex_lookup(x, gensym("#P"), &mypatcher);
        //post("my patcher is at address %lx",mypatcher);
        t_symbol *path = object_attr_getsym(mypatcher, gensym("filepath"));
        post("my patcher is in %s", path->s_name);
        
        //char* fullpath = strdup("Macintosh HD:/Users/ysuga/Development/rtm/wasanbon/workspace/nao/rtc/NAO/RTCGateway.maxhelp");
        char* root = strchr(path->s_name, ':');
        char* filepath = strrchr((char*)root+1, '/');
        filepath[1] = '\0';
        post("filepath = %s", root+1);
        
        char strbuf[256];
        strcpy(strbuf, root+1);
        strcpy(strbuf + strlen(root+1), "rtc.conf");

        post("strbuf = %s", strbuf);
        
        //String mainPatcherPath = this.getParentPatcher().getFilePath();
        char* argv[] = {"RTCGateway", "-f", strbuf};
        manager = RTC::Manager::init(argc, argv);
        manager->init(argc, argv);
        manager->setModuleInitProc(MyModuleInit);
        manager->activateManager();
        manager->runManager(true);
    }
}

void *RTCGateway_new(t_symbol *s, long argc, t_atom *argv)
{
    t_RTCGateway *x = NULL;
    if (argc < 2) {
        post("RTCGateway may accept one argument which is to be an RTC's name.");
    } else {
    
        x = (t_RTCGateway *)object_alloc((t_class*)RTCGateway_class);
        
        RTM_init((t_object*)x);
        ref_count ++;

        
        if (strcmp(argv[0].a_w.w_sym->s_name, "LongIn") == 0) {
            return LongIn_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "LongOut") == 0) {
            return LongOut_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "DoubleIn") == 0) {
            return DoubleIn_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "DoubleOut") == 0) {
            return DoubleOut_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "Velocity2DIn") == 0){
            return Velocity2DIn_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "Velocity2DOut") == 0){
            return Velocity2DOut_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "Pose2DIn") == 0){
            return Pose2DIn_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "Pose2DOut") == 0){
            return Pose2DOut_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "BooleanSeqIn") == 0){
            return BooleanSeqIn_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "BooleanSeqOut") == 0){
            return BooleanSeqOut_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "Point2DIn") == 0){
            return Point2DIn_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "Point2DOut") == 0){
            return Point2DOut_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "UShortIn") == 0) {
            return UShortIn_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "UShortOut") == 0) {
            return UShortOut_new(s, argc, argv);
        }
        if (strcmp(argv[0].a_w.w_sym->s_name, "NAO") == 0) {
            return NAO_new(s, argc, argv);
        }
    }
   
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