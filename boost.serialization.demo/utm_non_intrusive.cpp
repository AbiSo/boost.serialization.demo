//
//  utm1.cpp
//  boost.serialization.demo
//
//  Created by Abhijit Sovakar on 03.11.18.
//  Copyright © 2018 Abhijit Sovakar. All rights reserved.
//

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include "utm_non_intrusive.h"
#include "utm_primitive.h"

#include <iostream>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

std::ostream & operator << ( std::ostream & os, utm_non_intrusive const & v )
{
  os << v.zone() << v.band() << ':' << v.easting() << ':' << v.northing();
  return os;
}

std::istream & operator >> ( std::istream & is, utm_non_intrusive & v )
{
  unsigned int zone = 0;
  char         band = ' ';
  double       e    = 0.;
  double       n    = 0.;
  char   colon;
  if ( (is >> zone >> band >> colon >> e >> colon >> n).good() )
  {
    v = utm_non_intrusive(zone,band,e,n);
  }
  return is;
}

// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------
namespace boost::serialization {
// --------------------------------------------------------------------------------------------------------------------

#if !defined(DEMO_UTM1_HDR_INLINED)
template <typename Archive>
void serialize( Archive & ar, demo::utm_non_intrusive & u, unsigned int version [[maybe_unused]] )
{
  using boost::serialization::make_nvp;
  auto zone    = u.zone();
  auto band    = u.band();
  auto easting = u.easting();
  auto northing= u.northing();
  
  ar & make_nvp("zone",zone)
     & make_nvp("band",band)
     & make_nvp("easting", easting)
     & make_nvp("northing", northing);
  
  if ( Archive::is_loading::value )
    u = demo::utm_non_intrusive(zone,band,easting,northing);
}
#endif

#if defined(NDEBUG)
template
void serialize(boost::archive::binary_oarchive & ar, demo::utm_non_intrusive &, unsigned int);
#endif
// --------------------------------------------------------------------------------------------------------------------
} // boost::serialization
// --------------------------------------------------------------------------------------------------------------------
BOOST_CLASS_EXPORT_IMPLEMENT(demo::utm_non_intrusive)
// ====================================================================================================================
