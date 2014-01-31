#pragma hdrstop
#include <string>
#include "rr/rrRoadRunner.h"
#include "rr/rrException.h"
#include "rr/rrLogger.h"
#include "telOSSpecifics.h"
#include "telTelluriumData.h"
#include "telplugins_properties_api.h"
#include "telplugins_c_api.h"
#include "telplugins_cpp_support.h"
#include "telProperty.h"
#include "telPropertyBase.h"
//---------------------------------------------------------------------------

namespace tlpc
{
using namespace std;
using tlp::TelluriumData;


TELHandle tlp_cc createProperty(const char* label, const char* type, const char* _hint, void* value)
{
    start_try
        char* hint = (char*) _hint;
        if(!hint)
        {
            hint = "";
        }


        if(string(type) == string("bool"))
        {
            bool iniVal  = false;
            if(value != NULL)
            {
                //cast it
                bool* val = (bool*) value;
                iniVal = (*val);
            }
            Property<bool>* para = new Property<bool>(iniVal, label, hint);
            gHM.registerHandle(para, typeid(para).name());
            return para;
        }

        if(string(type) == string("int"))
        {
            int iniVal  = 0;
            if(value != NULL)
            {
                //cast it
                int* val = (int*) value;
                iniVal = (*val);
            }
            Property<int> *para = new Property<int>(iniVal, label, hint);
            gHM.registerHandle(para, typeid(para).name());
            return para;
        }

        //Don't support type 'float', it just causes problems. Make it a double
        if(string(type) == string("float"))
        {
            double iniVal  = 0;
            if(value != NULL)
            {
                //cast it
                double* dVal = (double*) value;
                iniVal = (*dVal);
            }
            Property<double> *para = new Property<double>(iniVal, label, hint);
            gHM.registerHandle(para, typeid(para).name());
            return para;
        }

        if(string(type) == string("double"))
        {
            double iniVal  = 0;
            if(value != NULL)
            {
                //cast it
                double* dVal = (double*) value;
                iniVal = (*dVal);
            }
            Property<double> *para = new Property<double>(iniVal, label, hint);
            gHM.registerHandle(para, typeid(para).name());
            return para;
        }

        //if(string(type) == string("string"))
        //{
        //    char* iniVal  = "";
        //    if(value != NULL)
        //    {
        //        //cast it
        //        char* *val = (char**) value;
        //        iniVal = (*val);
        //    }
        //    Property<char*> *para = new Property<char*>(iniVal, label, hint);
        //    return para;
        //}

        if(string(type) == string("std::string") || string(type) == string("string"))
        {
            string iniVal  = "";
            if(value != NULL)
            {
                //cast it
                string* val = (string*) value;
                iniVal = (*val);
            }
            Property<string> *para = new Property<string>(iniVal, label, hint);
            gHM.registerHandle(para, typeid(para).name());
            return para;
        }

        if(string(type) == string("listOfProperties"))
        {
            Properties iniVal;
            if(value != NULL)
            {
                //cast it
                Properties* val = (Properties*) value;
                iniVal = (*val);
            }

            Property<Properties> *para = new Property<Properties>(iniVal, label, hint);
            gHM.registerHandle(para, typeid(para).name());
            return para;
        }

        if(string(type) == string("telluriumData"))
        {
            TelluriumData iniVal;
            if(value != NULL)
            {
                //cast it
                TelluriumData* val = (TelluriumData*) value;
                iniVal = (*val);
            }

            Property<TelluriumData> *para = new Property<TelluriumData>(iniVal, label, hint);
            gHM.registerHandle(para, typeid(para).name());
            return para;
        }

        return NULL;
    catch_ptr_macro
}

bool tlp_cc freeProperty(TELHandle paraHandle)
{
    start_try
        PropertyBase* para   = castHandle<PropertyBase>(paraHandle, __FUNC__);
        delete para;
        return true;
    catch_bool_macro
}

TELHandle tlp_cc createPropertyList()
{
    start_try
        Properties* props   = new Properties();
        gHM.registerHandle(props, typeid(props).name());
        if(!props)
        {
            throw("Failed to create a list of Properties");
        }
        else
        {
            return props;
        }
    catch_ptr_macro
}

bool tlp_cc freeProperties(TELHandle handle)
{
    start_try
        Properties* props   = castHandle<Properties>(handle, __FUNC__);
        delete props;
        return true;
    catch_ptr_macro
}

bool tlp_cc addPropertyToList(TELHandle handle, TELHandle para)
{
    start_try
        Properties* paras   = castHandle<Properties>(handle, __FUNC__);
        PropertyBase* bPara = castHandle<PropertyBase>(para, __FUNC__);
        paras->add(bPara, false);
        return true;
    catch_bool_macro
}

char* tlp_cc getPropertyInfo(TELHandle handle)
{
    start_try
        PropertyBase* para = castHandle<PropertyBase>(handle, __FUNC__);
        stringstream s;
        s<<"Name="<<para->getName()<<"\tType="<<para->getType()<<"\tDescription="<<para->getDescription()<<"\tHint="<<para->getHint();
        return tlp::createText(s.str());
    catch_ptr_macro
}

bool tlp_cc setPropertyDescription(TELHandle handle, const char* value)
{
    start_try
        PropertyBase* para = castHandle<PropertyBase>(handle, __FUNC__);
        para->setDescription(string(value));
        return true;
    catch_bool_macro
}

char* tlp_cc getPropertyDescription(TELHandle handle)
{
    start_try
        PropertyBase* para = castHandle<PropertyBase>(handle, __FUNC__);
        return tlp::createText(para->getDescription());
    catch_ptr_macro
}

bool tlp_cc setPropertyHint(TELHandle handle, const char* value)
{
    start_try
        PropertyBase* para = castHandle<PropertyBase>(handle, __FUNC__);
        para->setHint(string(value));
        return true;
    catch_bool_macro
}

bool tlp_cc setPropertyByString(TELHandle handle, const char* value)
{
    start_try
        PropertyBase* para = castHandle<PropertyBase>(handle, __FUNC__);
        para->setValueFromString(string(value));
        return true;
    catch_bool_macro
}

bool tlp_cc setBoolProperty(TELHandle handle, bool value)
{
    start_try
        Property<bool>* para = castHandle< Property<bool> >(handle, __FUNC__);
        para->setValue(value);
        return true;
    catch_bool_macro
}

bool tlp_cc getBoolProperty(TELHandle handle, bool* value)
{
    start_try
        Property<bool>* para = castHandle< Property<bool> >(handle, __FUNC__);
        (*value) = para->getValue();
        return true;
    catch_bool_macro
}


bool tlp_cc setIntProperty(TELHandle handle, int value)
{
    start_try
        Property<int>* para = castHandle< Property<int> >(handle,__FUNC__);
        para->setValue(value);
        return true;
    catch_bool_macro
}

bool tlp_cc getIntProperty(TELHandle handle, int *value)
{
    start_try
        Property<int>* para = castHandle< Property<int> >(handle, __FUNC__);
        (*value) = para->getValue();
        return true;
    catch_bool_macro
}

bool tlp_cc setDoubleProperty(TELHandle handle, double value)
{
    start_try
        Property<double>* para = castHandle< Property<double> >(handle, __FUNC__);
        para->setValue(value);
        return true;
    catch_bool_macro
}

bool tlp_cc getDoubleProperty(TELHandle handle, double *value)
{
    start_try
        Property<double>* para = castHandle< Property<double> >(handle, __FUNC__);
        (*value) = para->getValue();
        return true;
    catch_bool_macro
}

bool tlp_cc setStringProperty(TELHandle handle, char* value)
{
    start_try
        Property<string>* para = castHandle< Property<string> >(handle, __FUNC__);
        para->setValue(value);
        return true;
    catch_bool_macro
}

bool tlp_cc getStringProperty(TELHandle handle, const char* (*value))
{
    start_try
        Property<string>* para = castHandle< Property<string> >(handle, __FUNC__);

        (*value) = para->getValue().c_str();
        return true;
    catch_bool_macro
}

bool tlp_cc setListProperty(TELHandle handle, void* value)
{
    start_try
        Property<Properties>* para = castHandle< Property<Properties> >(handle, __FUNC__);
        para->setValue((Properties*)(value));
        return true;
    catch_bool_macro
}

bool tlp_cc getListProperty(TELHandle handle, void* (value))
{
    start_try
        Property<Properties>* para = castHandle< Property<Properties> >(handle, __FUNC__);
        Properties* assignTo = castHandle<Properties>(value, __FUNC__);
        
        (assignTo) = (para->getValuePointer()); 
        return true;
    catch_bool_macro
}

bool tlp_cc setTelluriumDataProperty(TELHandle handle, void* value)
{
    start_try
        Property<TelluriumData>* para = castHandle< Property<TelluriumData> >(handle, __FUNC__);
        para->setValue(*((TelluriumData*) value));
        return true;
    catch_bool_macro
}

bool tlp_cc getTelluriumDataProperty(TELHandle handle, void* value)
{
    start_try
        Property<TelluriumData>* para = castHandle< Property<TelluriumData> >(handle, __FUNC__);
        TelluriumData* assignTo = castHandle< TelluriumData >(value, __FUNC__);
        (*assignTo) = (para->getValueReference()); 
        return true;
    catch_bool_macro
}

char* tlp_cc getPropertyValueAsString(TELHandle handle)
{
    start_try
        PropertyBase* para = castHandle<PropertyBase>(handle, __FUNC__);
        string val = para->getValueAsString();
        return tlp::createText(val);
    catch_ptr_macro
}

void* tlp_cc getPropertyValueHandle(TELHandle handle)
{
    start_try
        PropertyBase* para = castHandle<PropertyBase>(handle, __FUNC__);
        return para->getValueHandle();
    catch_ptr_macro
}

char* tlp_cc getPropertyName(TELHandle handle)
{
    start_try
        PropertyBase* para = castHandle<PropertyBase>(handle, __FUNC__);
        return tlp::createText(para->getName());
    catch_ptr_macro
}

char* tlp_cc getPropertyHint(TELHandle handle)
{
    start_try
        PropertyBase* para = castHandle<PropertyBase>(handle, __FUNC__);
        return tlp::createText(para->getHint());
    catch_ptr_macro
}

char* tlp_cc getPropertyType(TELHandle handle)
{
    start_try
        PropertyBase* para = castHandle<PropertyBase>(handle, __FUNC__);
        return tlp::createText(para->getType());
    catch_ptr_macro
}

TELHandle tlp_cc getFirstProperty(TELHandle handle)
{
    start_try
        Properties *paras = castHandle<Properties>(handle, __FUNC__);
        return paras->getFirst();
    catch_ptr_macro
}

TELHandle tlp_cc getNextProperty(TELHandle handle)
{
    start_try
        Properties *paras = castHandle<Properties>(handle, __FUNC__);
        return paras->getNext();
    catch_ptr_macro
}

TELHandle tlp_cc getPreviousProperty(TELHandle handle)
{
    start_try
        Properties *paras = castHandle<Properties>(handle, __FUNC__);
        return paras->getPrevious();
    catch_ptr_macro
}

TELHandle tlp_cc getCurrentProperty(TELHandle handle)
{
    start_try
        Properties *paras = castHandle<Properties>(handle, __FUNC__);
        return paras->getCurrent();
    catch_ptr_macro
}

bool tlp_cc clearPropertyList(TELHandle handle)
{
    start_try
        Properties* paras = castHandle<Properties>(handle, __FUNC__);
        return paras->clear();
    catch_bool_macro
}

TELHandle tlp_cc getProperty(TELHandle handle, const char* name)
{
    start_try
        Properties* props = castHandle<Properties>(handle, __FUNC__);
        return props->getProperty(name);
    catch_ptr_macro
}

char* tlp_cc getNamesFromPropertyList(TELHandle handle)
{
    start_try
        Properties* paras = castHandle<Properties>(handle, __FUNC__);
        tlp::StringList aList;
        for(int i = 0; i < paras->count(); i++)
        {
            aList.add((*paras)[i]->getName());
        }
        return tlp::createText(aList.AsString().c_str());

    catch_ptr_macro
}


}
