/**
 * @file rrplugins_cpp_support.h
 * @brief Plugins API CPP Support Functions.
 * @author Totte Karlsson & Herbert M Sauro
 *
 * <--------------------------------------------------------------
 * 
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
 * redistribute any piece of this software without proper attribution.
 * 
*/

#ifndef rrplugins_cpp_supportH
#define rrplugins_cpp_supportH
#include <string>
#include "rrplugins_c_api.h"
#include "rrRoadRunnerData.h"
namespace rrp
{
using std::string;
template <class T>
class Property;
class Properties;
class PropertyBase;
class Plugin;
class PluginManager;


/*!
 \brief Cast a handle to RoadRunner PluginManager pointer, throws if it fails
 \param[in] handle  A RRPluginManagerHandle
 \return Pointer to a PluginManager object
 \ingroup cpp_support
*/
PluginManager*                       castToPluginManager(RRPluginManagerHandle handle);

/*!
 \brief Cast a handle to RoadRunner Plugin pointer, throws if it fails
 \param[in] handle  A RRPluginHandle
 \return Pointer to a Plugin object
 \ingroup cpp_support
*/
Plugin*                             castToPlugin(RRPluginHandle handle);

/*!
 \brief Cast a handle to RoadRunner Properties pointer, throws if it fails
 \param[in] handle  A handle to a roadrunner parameters instance
 \return Pointer to a parameters instance
 \ingroup cpp_support
*/
Properties*                         castToProperties(RRPropertiesHandle handle);

/*!
 \brief Cast a handle to RoadRunner PropertyBase pointer, throws if it fails
 \param[in] handle  A handle to a roadrunner parameter instance
 \return Pointer to a baseparameter instance
 \ingroup cpp_support
*/
PropertyBase*                      castToProperty(RRPropertyHandle handle);

/*!
 \brief Cast a handle to RoadRunner Property<bool> pointer, throws if it fails
 \param[in] handle  A handle to a roadrunner parameter instance
 \return Pointer to a Property<int>* instance
 \ingroup cpp_support
*/
Property< bool >*                   castToBoolProperty(RRPropertyHandle handle);

/*!
 \brief Cast a handle to RoadRunner Property<int> pointer, throws if it fails
 \param[in] handle  A handle to a roadrunner parameter instance
 \return Pointer to a Property<int>* instance
 \ingroup cpp_support
*/
Property< int >*                   castToIntProperty(RRPropertyHandle handle);

/*!
 \brief Cast a handle to RoadRunner Property<double> pointer, throws if it fails
 \param[in] handle  A handle to a roadrunner parameter instance
 \return Pointer to a Property<double>* instance
 \ingroup cpp_support
*/
Property<double>*                  castToDoubleProperty(RRPropertyHandle handle);

/*!
 \brief Cast a handle to RoadRunner Property<string> pointer, throws if it fails
 \param[in] handle  A handle to a roadrunner parameter instance
 \return Pointer to a Property<double>* instance
 \ingroup cpp_support
*/
Property<string>*                   castToStringProperty(RRPropertyHandle handle);

/*!
 \brief Cast a handle to RoadRunner Property<Properties> pointer, throws if it fails
 \param[in] handle  A handle to a roadrunner parameter instance
 \return Pointer to a Property<Properties>* instance
 \ingroup cpp_support
*/
Property<Properties>*              castToPropertiesProperty(RRPropertyHandle handle);

/*!
 \brief Cast a handle to RoadRunnerData pointer, throws if it fails
 \param[in] handle  A handle to a roadrunnerdata instance
 \return Pointer to a RoadRunnerData instance
 \ingroup cpp_support
*/
rr::RoadRunnerData*                 castToRoadRunnerData(RRPropertyHandle handle);

/*!
 \brief Cast a handle to RoadRunner Property<RoadRunnerData> pointer, throws if it fails
 \param[in] handle  A handle to a roadrunner parameter instance
 \return Pointer to a Property<RoadRunnerData> instance
 \note To limit the amount of supported types, the underlying type can only be of RoadRunnerData, not pointer to
  data.
 \ingroup cpp_support
*/
Property<rr::RoadRunnerData>*      castToRoadRunnerDataProperty(RRPropertyHandle handle);

//Result data
/*!
 \brief Creates a RRData structure from rr::RoadRunnerData object
 \param[in] data  Input RoadRunner data
 \return A handle to a RRData structure. Null if it fails
 \ingroup cpp_support
*/
RRCDataPtr                          createRRCData(const rr::RoadRunnerData& result);

}

#endif
