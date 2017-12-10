//
//  utm.cpp
//  boost.serialization.demo
//
//  Created by Abhijit Sovakar on 10.12.17.
//  Copyright © 2017 Abhijit Sovakar. All rights reserved.
//

#include "utm.h"

#include <iostream>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

std::ostream & operator << ( std::ostream & os, utm const & v )
{
  os << v.zone() << v.band() << ':' << v.easting() << ':' << v.northing();
  return os;
}

std::istream & operator >> ( std::istream & is, utm & v )
{
  unsigned int zone = 0;
  char         band = ' ';
  double       e = 0.;
  double       n = 0.;
  char   colon;
  if ( (is >> zone >> band >> colon >> e >> colon >> n).good() )
  {
    v = utm(zone,band,e,n);
  }
  return is;
}

// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------
// ====================================================================================================================
