#pragma hdrstop
#include "rrc_cpp_support.h"
#include "rrplugins_cpp_support.h"
#include "rrRoadRunnerData.h"
#include "rrException.h"
#include "rrStringUtils.h"

namespace rrp
{
using namespace rr;

PluginManager* castToPluginManager(RRPluginManagerHandle handle)
{
    PluginManager *pm = static_cast<PluginManager*>(handle);
    if(pm)
    {
        return pm;
    }
    else
    {
        Exception ex("Failed to cast to a valid PluginManager handle");
        throw(ex);
    }
}

Plugin* castToPlugin(RRPluginHandle handle)
{
    Plugin* plugin = (Plugin*) handle;
    if(plugin) //Will only fail if handle is NULL...
    {
        return plugin;
    }
    else
    {
        Exception ex("Failed to cast to a valid Plugin handle");
        throw(ex);
    }
}

Properties* castToProperties(RRPropertiesHandle handle)
{
    Properties* para = (Properties*) handle;
    if(para) //Will only fail if handle is NULL...
    {
        return para;
    }
    else
    {
        Exception ex("Failed to cast to a valid Properties handle");
        throw(ex);
    }
}

PropertyBase* castToProperty(RRPropertyHandle handle)
{
    PropertyBase* para = (PropertyBase*) handle;
    if(para) //Will only fail if handle is NULL...
    {
        return para;
    }
    else
    {
        Exception ex("Failed to cast to a valid Property handle");
        throw(ex);
    }
}

Property<bool>* castToBoolProperty(RRPropertyHandle handle)
{
    Property<bool>* para = (Property<bool>*) handle;
    if(para) //Will only fail if handle is NULL...
    {
        return para;
    }
    else
    {
        Exception ex("Failed to cast to a valid Boolean Property handle");
        throw(ex);
    }
}

Property<int>* castToIntProperty(RRPropertyHandle handle)
{
    Property<int>* para = (Property<int>*) handle;
    if(para) //Will only fail if handle is NULL...
    {
        return para;
    }
    else
    {
        Exception ex("Failed to cast to a valid Integer Property handle");
        throw(ex);
    }
}

Property<double>* castToDoubleProperty(RRPropertyHandle handle)
{
    Property<double>* para = (Property<double>*) handle;
    if(para) //Will only fail if handle is NULL...
    {
        return para;
    }
    else
    {
        Exception ex("Failed to cast to a valid Double Property handle");
        throw(ex);
    }
}

Property<string>* castToStringProperty(RRPropertyHandle handle)
{
    Property<string>* para = (Property<string>*) handle;
    if(para) //Will only fail if handle is NULL...
    {
        return para;
    }
    else
    {
        Exception ex("Failed to cast to a valid string Property handle");
        throw(ex);
    }
}

Property<Properties>* castToPropertiesProperty(RRPropertyHandle handle)
{
    Property<Properties>* para = (Property<Properties>*) handle;
    if(para) //Will only fail if handle is NULL...
    {
        return para;
    }
    else
    {
        Exception ex("Failed to cast to a valid string Property handle");
        throw(ex);
    }
}

RoadRunnerData* castToRoadRunnerData(RRDataHandle handle)
{
    RoadRunnerData* para = (RoadRunnerData*) handle;
    if(para) //Will only fail if handle is NULL...
    {
        return para;
    }
    else
    {
        Exception ex("Failed to cast to a valid string Property handle");
        throw(ex);
    }
}

Property<RoadRunnerData>* castToRoadRunnerDataProperty(RRPropertyHandle handle)
{
    Property<RoadRunnerData>* para = (Property<RoadRunnerData>*) handle;
    if(para) //Will only fail if handle is NULL...
    {
        return para;
    }
    else
    {
        Exception ex("Failed to cast to a valid RoadRunnerData Property handle");
        throw(ex);
    }
}

RRCDataPtr createRRCData(const RoadRunnerData& result)
{
    return rrc::createRRCData(result);     
}


}
