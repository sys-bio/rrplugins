/**
 * @file rrplugins_properties_api.h
 * @brief Plugins API Properties Header
 * @author Totte Karlsson & Herbert M Sauro
 *
 * <--------------------------------------------------------------
 * This file is part of cRoadRunner.
 * See http://code.google.com/p/roadrunnerlib for more details.
 *
 * Copyright (C) 2012-2013
 *   University of Washington, Seattle, WA, USA
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * In plain english this means:
 *
 * You CAN freely download and use this software, in whole or in part, for personal,
 * company internal, or commercial purposes;
 *
 * You CAN use the software in packages or distributions that you create.
 *
 * You SHOULD include a copy of the license in any redistribution you may make;
 *
 * You are NOT required include the source of software, or of any modifications you may
 * have made to it, in any redistribution you may assemble that includes it.
 *
 * YOU CANNOT:
 *
 * redistribute any piece of this software without proper attribution;
*/

#ifndef rrp_parameter_apiH
#define rrp_parameter_apiH
#include "rrplugins_exporter.h"
#include "rrplugins_types.h"
//---------------------------------------------------------------------------

#if defined(__cplusplus)
namespace rrp { extern "C" {
#endif

/*! \addtogroup plugin_properties
 *  @{
 */
 
/*!
 \brief Create a property of type "type"
 \param label The property's label as a string
 \param type  The property's type as string. Possible values can be 'double', 'int', 'char*' etc,
 \param hint  The property's hint as string.
 \param value The property's initial value casted to a (void*) pointer
 \return Returns a handle to a new property, if succesful, NULL otherwise
*/
RRP_C_DS RRPropertyHandle rrp_cc createProperty(const char* label, const char* type, const char* hint, void* value);

/*!
 \brief Create a PropertyList, i.e. an object of type Properties
 \return Returns a handle to a new PropertyList, if succesful, NULL otherwise
*/
RRP_C_DS RRPropertiesHandle rrp_cc createPropertyList(void);

/*!
 \brief Free a list of properties
 \param propertiesH A handle a list of properties
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc freeProperties(RRPropertiesHandle propertiesH);

/*!
 \brief Free the memory created by a property
 \param property A handle to the property
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc freeProperty(RRPropertyHandle property);

/*!
 \brief Add a property to a properties container, from a property pointer.
 \param handle Handle to a RoadRunner instance
 \param property Handle to a roadrunner property
 \return Returns a booelan indicating success
*/
RRP_C_DS bool rrp_cc addPropertyToList(RRPropertiesHandle handle, RRPropertyHandle property);

/*!
 \brief Set a property value by a string
 \param handle to a Property instance
 \param value Pointer to string holding the value to assign to the property, e.g. "0.01" to set a double to 0.01
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc setPropertyByString(RRPropertyHandle handle, const char* value);

/*!
 \brief Get a boolean property
 \param handle to a Property instance
 \param value to assign to the property.
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc getBoolProperty(RRPropertyHandle handle, bool* value);

/*!
 \brief Set a boolean property
 \param handle to a Property instance
 \param value to assign to the property.
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc setBoolProperty(RRPropertyHandle handle, bool value);

/*!
 \brief Set an int property
 \param handle to a Property instance
 \param value to assign to the property.
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc setIntProperty(RRPropertyHandle handle, int value);

/*!
 \brief Get the value of an int property
 \param handle to a Property instance
 \param value to assign to the property.
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc getIntProperty(RRPropertyHandle handle, int *value);

/*!
 \brief Set a double property
 \param handle to a Property instance
 \param value to assign to the property.
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc setDoubleProperty(RRPropertyHandle handle, double value);

/*!
 \brief Get the value of a double property
 \param handle to a Property instance
 \param value to assign to the property.
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc getDoubleProperty(RRPropertyHandle handle, double *value);

/*!
 \brief Set a string (char*) property
 \param handle to a Property instance
 \param value to assign to the property.
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc setStringProperty(RRPropertyHandle handle, char* value);

/*!
 \brief Get the value of a string (char*) property
 \param handle to a Property instance
 \param value to assign to the property.
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc getStringProperty(RRPropertyHandle handle, const char* (*value));

/*!
 \brief Set a listOfProperties (Properties) property
 \param handle to a Property instance
 \param value to assign to the property.
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc setListProperty(RRPropertyHandle handle, void* value);

/*!
 \brief Get the value of a listOfProperties (Properties) property
 \param handle to a Property instance
 \param value to assign to the property.
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc getListProperty(RRPropertyHandle handle, void* value);

/*!
 \brief Set a roadRunnerDataProperty property
 \param handle to a Property instance
 \param value to assign to the property.
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc setRoadRunnerDataProperty(RRPropertyHandle handle, void* value);

/*!
 \brief Get the value of a roadRunnerDataProperty property
 \param handle to a Property instance
 \param value to assign to the property.
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc getRoadRunnerDataProperty(RRPropertyHandle handle, void* value);

/*!
 \brief Get a property's info
 \param handle Handle to a property instance
 \return Returns informational text about the property if sucessful, NULL otherwise
*/
RRP_C_DS char* rrp_cc getPropertyInfo(RRPropertyHandle handle);

/*!
 \brief Get a property's value as char*
 \param handle to a Property instance
 \return Returns the property's value if sucessful, NULL otherwise
*/
RRP_C_DS char* rrp_cc getPropertyValueAsString(RRPropertyHandle handle);

/*!
 \brief Get a handle to a property's value
 \param handle to a Property instance
 \return Returns a Handle to the property's value if sucessful, NULL otherwise
*/
RRP_C_DS void* rrp_cc getPropertyValueHandle(RRPropertyHandle handle);

/*!
 \brief Get a property's name
 \param handle to a Property instance
 \return Returns the property's name if sucessful, NULL otherwise
*/
RRP_C_DS char* rrp_cc getPropertyName(RRPropertyHandle handle);

/*!
 \brief Get a property's hint
 \param handle to a Property instance
 \return Returns the property's hint if sucessful, NULL otherwise
*/
RRP_C_DS char* rrp_cc getPropertyHint(RRPropertyHandle handle);

/*!
 \brief Set a property's hint
 \param handle to a Property instance
 \param value The property hint as a string
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc setPropertyHint(RRPropertyHandle handle, const char* value);

/*!
 \brief Get a property's description
 \param handle to a Property instance
 \return Returns the property's description as a string sucessful, NULL otherwise
*/
RRP_C_DS char* rrp_cc getPropertyDescription(RRPropertyHandle handle);

/*!
 \brief Set a property's Description
 \param handle to a Property instance
 \param value The property description as a string
 \return Returns true if sucessful, false otherwise
*/
RRP_C_DS bool rrp_cc setPropertyDescription(RRPropertyHandle handle, const char* value);

/*!
 \brief Get a property's type
 \param handle Handle to a Property instance
 \return Returns the property's type if sucessful, NULL otherwise
*/
RRP_C_DS char* rrp_cc getPropertyType(RRPropertyHandle handle);

/*!
 \brief Get a property containers 'first' property.
 \param handle Handle to a Properties (container for properties) instance
 \return Returns a handle to the 'first property', NULL if container is empty
 \note This function is typically used together with the getNextProperty,
 getPreviuosProperty and getCurrentProperty when iterating trough properties.
*/
RRP_C_DS RRPropertyHandle rrp_cc getFirstProperty(RRPropertiesHandle handle);

/*!
 \brief Get a property containers 'next' property.
 \param handle Handle to a Properties (container for properties) instance
 \return Returns a handle to the 'next property', NULL if unsucccesfull
 \note This function is typically used together with the getFirstProperty,
 getPreviuosProperty and getCurrentProperty when iterating trough properties.
 This function do not wrap around. This function move an internal Property iterator forward one step.
*/
RRP_C_DS RRPropertyHandle rrp_cc getNextProperty(RRPropertiesHandle handle);

/*!
 \brief Get a property containers 'previous' property.
 \param handle Handle to a Properties (container for properties) instance
 \return Returns a handle to the 'previous property', NULL if container is empty
 \note This function is typically used together with the getNextProperty,
 getNextProperty and getCurrentProperty when iterating trough properties. This function
 move an internal Property iterator back one step.
*/
RRP_C_DS RRPropertyHandle rrp_cc getPreviousProperty(RRPropertiesHandle handle);

/*!
 \brief Get a property containers 'current' property.
 \param handle Handle to a Properties (container for properties) instance
 \return Returns a handle to the 'current property', NULL if container is empty
 \note This function is typically used together with the getNextProperty,
 getPreviuosProperty and getFirstProperty, when iterating trough properties.
*/
RRP_C_DS RRPropertyHandle rrp_cc getCurrentProperty(RRPropertiesHandle handle);

/*!
 \brief Get a list of names for a plugins property's.
 \param handle Handle to a plugin
 \return Returns a string with the names of each property, NULL otherwise
 \ingroup plugins
*/
RRP_C_DS char* rrp_cc getNamesFromPropertyList(RRPropertiesHandle handle);

/*!
 \brief Get a handle to a particular property
 \param handle Handle to a property list object
 \param name Name of the property.
 \return Returns a handle to a property if successfull, NULL otherwise
 \ingroup plugins
*/
RRP_C_DS RRPropertyHandle rrp_cc getProperty(RRPropertiesHandle handle, const char* name);

/*!
 \brief Clear a list of properties
 \param handle Handle to a Properties list
  \return Returns true or false indicating result
 \ingroup plugins
*/
RRP_C_DS bool rrp_cc clearPropertyList(RRPropertiesHandle handle);

/*! @} */

#if defined(__cplusplus)
}}    //rrc namespace
#endif


#endif
