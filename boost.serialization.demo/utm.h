//
//  utm.hpp
//  boost.serialization.demo
//

#ifndef UTM_H
#define UTM_H

#include <iosfwd>

#include <boost/serialization/level.hpp>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

class utm
{
public:
  utm() = default;
  ~utm() = default;
  utm( const utm & ) = default;
  utm & operator = ( const utm & ) = default;
  utm( utm && ) = default;
  utm & operator = ( utm && ) = default;
  
  utm( unsigned int zone, char band, double easting, double northing )
  : mZone(zone), mBand(band), mEasting(easting), mNorthing(northing)
  {}
  
  unsigned int zone() const { return mZone; }
  char         band() const { return mBand; }
  double       easting() const { return mEasting; }
  double       northing() const { return mNorthing; }
  
private:
  unsigned int mZone{0};
  char         mBand{'?'};
  double       mEasting{0.0};
  double       mNorthing{0.0};
};

// required for serialization of "primitive types"
std::ostream & operator << ( std::ostream & os, utm const & v );

// required for serialization of "primitive types"
std::istream & operator >> ( std::istream & is, utm & v );

// --------------------------------------------------------------------------------------------------------------------
}
// --------------------------------------------------------------------------------------------------------------------

// elminate serialization overhead at the cost of
// never being able to increase the version.
BOOST_CLASS_IMPLEMENTATION(demo::utm, boost::serialization::primitive_type);

// --------------------------------------------------------------------------------------------------------------------
#endif /* utm_hpp */
// ====================================================================================================================
