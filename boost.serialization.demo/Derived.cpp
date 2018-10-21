//
//  Derived.cpp
//  boost.serialization.demo
//

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include "Derived.h"

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>

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

#if 0
template
void DerivedOne::serialize(boost::archive::xml_oarchive & ar, unsigned int version);
template
void DerivedOne::serialize(boost::archive::xml_iarchive & ar, unsigned int version);

template
void DerivedOne::serialize(boost::archive::binary_oarchive & ar, unsigned int version);
template
void DerivedOne::serialize(boost::archive::binary_iarchive & ar, unsigned int version);

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
// register classes otherwise "unregistered class" exception:
// "unregistered class - derived class not registered or exported"
BOOST_CLASS_EXPORT_IMPLEMENT(demo::DerivedOne)
BOOST_CLASS_EXPORT_IMPLEMENT(demo::DerivedTwo)
BOOST_CLASS_EXPORT_IMPLEMENT(demo::DerivedThree)
BOOST_CLASS_EXPORT_IMPLEMENT(demo::DerivedFour)
// ====================================================================================================================
