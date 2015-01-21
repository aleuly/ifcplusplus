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

// TYPE IfcAssemblyPlaceEnum = ENUMERATION OF	(SITE	,FACTORY	,NOTDEFINED);
class IFCPP_EXPORT IfcAssemblyPlaceEnum : virtual public IfcPPObject
{
public:
	enum IfcAssemblyPlaceEnumEnum
	{
		ENUM_SITE,
		ENUM_FACTORY,
		ENUM_NOTDEFINED
	};

	IfcAssemblyPlaceEnum();
	IfcAssemblyPlaceEnum( IfcAssemblyPlaceEnumEnum e ) { m_enum = e; }
	~IfcAssemblyPlaceEnum();
	virtual const char* className() const { return "IfcAssemblyPlaceEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcAssemblyPlaceEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcAssemblyPlaceEnumEnum m_enum;
};

