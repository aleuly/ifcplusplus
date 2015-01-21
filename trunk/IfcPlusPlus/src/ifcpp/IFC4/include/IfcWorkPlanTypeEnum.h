/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com - Copyright (C) 2011 Fabian Gerold
*
* This library is open source and may be redistributed and/or modified under  
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
* (at your option) any later version.  The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
* 
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
* OpenSceneGraph Public License for more details.
*/

#pragma once
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "ifcpp/model/shared_ptr.h"
#include "ifcpp/model/IfcPPObject.h"
#include "ifcpp/model/IfcPPGlobal.h"

// TYPE IfcWorkPlanTypeEnum = ENUMERATION OF	(ACTUAL	,BASELINE	,PLANNED	,USERDEFINED	,NOTDEFINED);
class IFCPP_EXPORT IfcWorkPlanTypeEnum : virtual public IfcPPObject
{
public:
	enum IfcWorkPlanTypeEnumEnum
	{
		ENUM_ACTUAL,
		ENUM_BASELINE,
		ENUM_PLANNED,
		ENUM_USERDEFINED,
		ENUM_NOTDEFINED
	};

	IfcWorkPlanTypeEnum();
	IfcWorkPlanTypeEnum( IfcWorkPlanTypeEnumEnum e ) { m_enum = e; }
	~IfcWorkPlanTypeEnum();
	virtual const char* className() const { return "IfcWorkPlanTypeEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcWorkPlanTypeEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcWorkPlanTypeEnumEnum m_enum;
};

