//
//  utm2.cpp
//  boost.serialization.demo
//
//  Created by Abhijit Sovakar on 03.11.18.
//  Copyright © 2018 Abhijit Sovakar. All rights reserved.
//

// allow compiler to pre-instantiate serialize templates for xml and binary archives
// in combination of BOOST_CLASS_EXPORT_IMPLEMENT
//
#define DEMO_PRESINSTANTIATION_OF_MEMBER_TEMPLATE_SERIALIZE
#if defined(DEMO_PRESINSTANTIATION_OF_MEMBER_TEMPLATE_SERIALIZE)
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#endif

#include "utm_serialize.h"
#include "utm_primitive.h"

#include <boost/serialization/nvp.hpp>

#include <iostream>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

template<typename Archive>
void utm_serialize::serialize( Archive & ar, const unsigned int )
{
  using boost::serialization::make_nvp;
  ar & make_nvp("zone"    , mZone);
  ar & make_nvp("band"    , mBand);
  ar & make_nvp("easting" , mEasting);
  ar & make_nvp("northing", mNorthing);
}

std::ostream & operator << ( std::ostream & os, utm_serialize const & v )
{
  os << utm_primitive( v.zone(), v.band(), v.easting(), v.northing() );
  return os;
}
    

// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------
// requires include of supported archive types in case the member serialize is implemented in the sources
BOOST_CLASS_EXPORT_IMPLEMENT(demo::utm_serialize)
// ====================================================================================================================
