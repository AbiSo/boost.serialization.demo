//
//  utm3.cpp
//  boost.serialization.demo
//
//  Created by Abhijit Sovakar on 03.11.18.
//  Copyright © 2018 Abhijit Sovakar. All rights reserved.
//

// allow compiler to pre-instantiate serialize templates for xml and binary archives
// in combination of BOOST_CLASS_EXPORT_IMPLEMENT
//
#define DEMO_PREINSTANTIATION_OF_MEMBER_TEMPLATE_SERIALIZE
#if defined(DEMO_PREINSTANTIATION_OF_MEMBER_TEMPLATE_SERIALIZE)
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#endif

#include "utm_split.h"
#include "utm_primitive.h"

#include <boost/serialization/nvp.hpp>

#include <iostream>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

template<typename Archive>
void utm_split::save( Archive & ar, unsigned int ) const
{
  using boost::serialization::make_nvp;
  ar & make_nvp("zone"    , mZone);
  ar & make_nvp("band"    , mBand);
  ar & make_nvp("easting" , mEasting);
  ar & make_nvp("northing", mNorthing);
}

template<typename Archive>
void utm_split::load( Archive & ar, unsigned int )
{
  using boost::serialization::make_nvp;
  ar & make_nvp("zone"    , mZone);
  ar & make_nvp("band"    , mBand);
  ar & make_nvp("easting" , mEasting);
  ar & make_nvp("northing", mNorthing);
}

std::ostream & operator << ( std::ostream & os, utm_split const & v )
{
  os << utm_primitive( v.zone(), v.band(), v.easting(), v.northing() );
  return os;
}
  
#if 0
template
void utm_split::save(boost::archive::xml_oarchive & ar, unsigned int version) const;
template
void utm_split::load(boost::archive::xml_iarchive & ar, unsigned int version);
#endif
#if defined(NDEBUG)
template
void utm_split::save(boost::archive::binary_oarchive & ar, unsigned int version) const;
template
void utm_split::load(boost::archive::binary_iarchive & ar, unsigned int version);
#endif

// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------
// requires include of supported archive types in case the member serialize is implemented in the sources
BOOST_CLASS_EXPORT_IMPLEMENT(demo::utm_split)
// ====================================================================================================================
