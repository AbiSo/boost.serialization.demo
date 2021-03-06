//
//  utm.hpp
//  boost.serialization.demo
//

#ifndef UTM_PRIMITIVE_H
#define UTM_PRIMITIVE_H

#include <iosfwd>

#include <boost/serialization/version.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/is_bitwise_serializable.hpp>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

// treat object as primitive type
class utm_primitive
{
public:
  utm_primitive() = default;
  utm_primitive( unsigned int zone, char band, double easting, double northing )
    : mZone(zone), mBand(band), mEasting(easting), mNorthing(northing)
  {}
  
  unsigned int zone() const { return mZone; }
  char         band() const { return mBand; }
  double       easting() const { return mEasting; }
  double       northing() const { return mNorthing; }
  
private:
  unsigned int mZone{32};
  char         mBand{'N'};
  double       mEasting{1.0};
  double       mNorthing{0.1};
};

// required for serialization of "primitive types"
std::ostream & operator << ( std::ostream & os, utm_primitive const & v );

// required for serialization of "primitive types"
std::istream & operator >> ( std::istream & is, utm_primitive & v );

// --------------------------------------------------------------------------------------------------------------------
}
// --------------------------------------------------------------------------------------------------------------------

// rendered obsolete for "primitive" type - no class versioning - always 0
BOOST_CLASS_VERSION(demo::utm_primitive,0);

// elminate serialization overhead at the cost of
// never being able to increase the version.
BOOST_CLASS_IMPLEMENTATION(demo::utm_primitive, boost::serialization::primitive_type);

// bitwise serialize in binary archives
// pre-condition: the type
// - is a POD data type
// - contains no pointer members which are not versioned and not tracked.
BOOST_IS_BITWISE_SERIALIZABLE(demo::utm_primitive)

// --------------------------------------------------------------------------------------------------------------------
#endif /* UTM_PRIMITIVE_H */
// ====================================================================================================================
