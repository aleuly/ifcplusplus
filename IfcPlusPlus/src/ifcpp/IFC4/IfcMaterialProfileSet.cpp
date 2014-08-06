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
#include <sstream>
#include <limits>

#include "ifcpp/model/IfcPPException.h"
#include "ifcpp/model/IfcPPAttributeObject.h"
#include "ifcpp/reader/ReaderUtil.h"
#include "ifcpp/writer/WriterUtil.h"
#include "ifcpp/IfcPPEntityEnums.h"
#include "include/IfcCompositeProfileDef.h"
#include "include/IfcExternalReferenceRelationship.h"
#include "include/IfcLabel.h"
#include "include/IfcMaterialProfile.h"
#include "include/IfcMaterialProfileSet.h"
#include "include/IfcMaterialProperties.h"
#include "include/IfcRelAssociatesMaterial.h"
#include "include/IfcText.h"

// ENTITY IfcMaterialProfileSet 
IfcMaterialProfileSet::IfcMaterialProfileSet() {}
IfcMaterialProfileSet::IfcMaterialProfileSet( int id ) { m_id = id; }
IfcMaterialProfileSet::~IfcMaterialProfileSet() {}
shared_ptr<IfcPPObject> IfcMaterialProfileSet::getDeepCopy()
{
	shared_ptr<IfcMaterialProfileSet> copy_self( new IfcMaterialProfileSet() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy() ); }
	if( m_Description ) { copy_self->m_Description = dynamic_pointer_cast<IfcText>( m_Description->getDeepCopy() ); }
	for( size_t ii=0; ii<m_MaterialProfiles.size(); ++ii )
	{
		auto item_ii = m_MaterialProfiles[ii];
		if( item_ii )
		{
			copy_self->m_MaterialProfiles.push_back( dynamic_pointer_cast<IfcMaterialProfile>(item_ii->getDeepCopy() ) );
		}
	}
	if( m_CompositeProfile ) { copy_self->m_CompositeProfile = dynamic_pointer_cast<IfcCompositeProfileDef>( m_CompositeProfile->getDeepCopy() ); }
	return copy_self;
}
void IfcMaterialProfileSet::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCMATERIALPROFILESET" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	writeEntityList( stream, m_MaterialProfiles );
	stream << ",";
	if( m_CompositeProfile ) { stream << "#" << m_CompositeProfile->getId(); } else { stream << "$"; }
	stream << ");";
}
void IfcMaterialProfileSet::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcMaterialProfileSet::readStepArguments( const std::vector<std::wstring>& args, const std::map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args<4 ){ std::stringstream strserr; strserr << "Wrong parameter count for entity IfcMaterialProfileSet, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; throw IfcPPException( strserr.str().c_str() ); }
	#ifdef _DEBUG
	if( num_args>4 ){ std::cout << "Wrong parameter count for entity IfcMaterialProfileSet, expecting 4, having " << num_args << ". Object id: " << getId() << std::endl; }
	#endif
	m_Name = IfcLabel::createObjectFromStepData( args[0] );
	m_Description = IfcText::createObjectFromStepData( args[1] );
	readEntityReferenceList( args[2], m_MaterialProfiles, map );
	readEntityReference( args[3], m_CompositeProfile, map );
}
void IfcMaterialProfileSet::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcMaterialDefinition::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "Name", m_Name ) );
	vec_attributes.push_back( std::make_pair( "Description", m_Description ) );
	if( m_MaterialProfiles.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> MaterialProfiles_vec_object( new  IfcPPAttributeObjectVector() );
		std::copy( m_MaterialProfiles.begin(), m_MaterialProfiles.end(), std::back_inserter( MaterialProfiles_vec_object->m_vec ) );
		vec_attributes.push_back( std::make_pair( "MaterialProfiles", MaterialProfiles_vec_object ) );
	}
	vec_attributes.push_back( std::make_pair( "CompositeProfile", m_CompositeProfile ) );
}
void IfcMaterialProfileSet::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcMaterialDefinition::getAttributesInverse( vec_attributes_inverse );
}
void IfcMaterialProfileSet::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcMaterialDefinition::setInverseCounterparts( ptr_self_entity );
	shared_ptr<IfcMaterialProfileSet> ptr_self = dynamic_pointer_cast<IfcMaterialProfileSet>( ptr_self_entity );
	if( !ptr_self ) { throw IfcPPException( "IfcMaterialProfileSet::setInverseCounterparts: type mismatch" ); }
	for( int i=0; i<m_MaterialProfiles.size(); ++i )
	{
		if( m_MaterialProfiles[i] )
		{
			m_MaterialProfiles[i]->m_ToMaterialProfileSet_inverse = ptr_self;
		}
	}
}
void IfcMaterialProfileSet::unlinkSelf()
{
	IfcMaterialDefinition::unlinkSelf();
	for( int i=0; i<m_MaterialProfiles.size(); ++i )
	{
		if( m_MaterialProfiles[i] )
		{
			shared_ptr<IfcMaterialProfileSet> self_candidate( m_MaterialProfiles[i]->m_ToMaterialProfileSet_inverse );
			if( self_candidate->getId() == this->getId() )
			{
				weak_ptr<IfcMaterialProfileSet>& self_candidate_weak = m_MaterialProfiles[i]->m_ToMaterialProfileSet_inverse;
				self_candidate_weak.reset();
			}
		}
	}
}