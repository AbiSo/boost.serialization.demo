//
//  utm1.hpp
//  boost.serialization.demo
//
//  Created by Abhijit Sovakar on 03.11.18.
//  Copyright © 2018 Abhijit Sovakar. All rights reserved.
//

#ifndef UTM_NON_INTRUSIVE_H
#define UTM_NON_INTRUSIVE_H

#include <iosfwd>

#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/is_bitwise_serializable.hpp>
#include <boost/serialization/export.hpp>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

// non-intrusive serialization
class utm_non_intrusive
{
public:
  utm_non_intrusive() = default;
  utm_non_intrusive( unsigned int zone, char band, double easting, double northing )
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

std::ostream & operator << ( std::ostream & os, utm_non_intrusive const & v );

// --------------------------------------------------------------------------------------------------------------------
}
// --------------------------------------------------------------------------------------------------------------------

BOOST_CLASS_VERSION(demo::utm_non_intrusive,0)

// bitwise serialize in binary archives
// pre-condition: the type
// - is a POD data type
// - contains no pointer members which are not versioned and not tracked.
BOOST_IS_BITWISE_SERIALIZABLE(demo::utm_non_intrusive)

BOOST_CLASS_EXPORT_KEY(demo::utm_non_intrusive)

// --------------------------------------------------------------------------------------------------------------------
namespace boost::serialization {
// --------------------------------------------------------------------------------------------------------------------
#undef DEMO_UTM1_HDR_INLINED
#if !defined(DEMO_UTM1_HDR_INLINED)
template <typename Archive>
void serialize( Archive & ar, demo::utm_non_intrusive & u, unsigned int version);
#else
template <typename Archive>
void serialize( Archive & ar, demo::utm_non_intrusive & u, unsigned int version [[maybe_unused]])
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
  
// --------------------------------------------------------------------------------------------------------------------
}
// --------------------------------------------------------------------------------------------------------------------
#endif /* UTM_NON_INTRUSIVE_H */
// ====================================================================================================================
