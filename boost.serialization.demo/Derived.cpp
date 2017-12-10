//
//  Derived.cpp
//  boost.serialization.demo
//
//  Created by Abhijit Sovakar on 10.12.17.
//  Copyright © 2017 Abhijit Sovakar. All rights reserved.
//

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include "Derived.h"

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

template <typename Tag, typename V>
template <typename Archive>
void Derived<Tag,V>::serialize( Archive & ar, unsigned int version [[maybe_unused]] )
{
  using boost::serialization::make_nvp;
  using boost::serialization::base_object;
  ar & make_nvp("base", base_object<Base>(*this) );
  ar & make_nvp("value", mValue);
}

// --------------------------------------------------------------------------------------------------------------------

template
void DerivedOne::serialize(boost::archive::xml_oarchive & ar, unsigned int version);
template
void DerivedOne::serialize(boost::archive::xml_iarchive & ar, unsigned int version);

template
void DerivedOne::serialize(boost::archive::binary_oarchive & ar, unsigned int version);
template
void DerivedOne::serialize(boost::archive::binary_iarchive & ar, unsigned int version);

#if 0
template
void DerivedTwo::serialize(boost::archive::xml_oarchive & ar, unsigned int version);
template
void DerivedTwo::serialize(boost::archive::xml_iarchive & ar, unsigned int version);

template
void DerivedTwo::serialize(boost::archive::binary_oarchive & ar, unsigned int version);
template
void DerivedTwo::serialize(boost::archive::binary_iarchive & ar, unsigned int version);
#endif
  
// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------
BOOST_CLASS_EXPORT_IMPLEMENT(demo::DerivedOne)
BOOST_CLASS_EXPORT_IMPLEMENT(demo::DerivedTwo)
// ====================================================================================================================
