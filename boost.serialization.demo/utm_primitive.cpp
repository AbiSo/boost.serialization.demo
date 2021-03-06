//
//  utm.cpp
//  boost.serialization.demo
//

#include "utm_primitive.h"

#include <iostream>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

std::ostream & operator << ( std::ostream & os, utm_primitive const & v )
{
  os << v.zone() << v.band() << ':' << v.easting() << ':' << v.northing();
  return os;
}

std::istream & operator >> ( std::istream & is, utm_primitive & v )
{
  unsigned int zone = 0;
  char         band = ' ';
  double       e    = 0.;
  double       n    = 0.;
  char   colon;
  if ( (is >> zone >> band >> colon >> e >> colon >> n).good() )
  {
    v = utm_primitive(zone,band,e,n);
  }
  return is;
}

// --------------------------------------------------------------------------------------------------------------------
} // demo
// ====================================================================================================================
