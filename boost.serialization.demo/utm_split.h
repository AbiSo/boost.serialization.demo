//
//  utm3.hpp
//  boost.serialization.demo
//
//  Created by Abhijit Sovakar on 03.11.18.
//  Copyright © 2018 Abhijit Sovakar. All rights reserved.
//

#ifndef UTM_SPLIT_H
#define UTM_SPLIT_H

#include <iosfwd>

#include <boost/serialization/version.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/split_member.hpp>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

// splitting serialize into save/load
class utm_split
{
public:
  using coord = float;
  
  utm_split() = default;
  utm_split( unsigned int zone, char band, coord easting, coord northing )
  : mZone(zone), mBand(band), mEasting(easting), mNorthing(northing)
  {}
  
  unsigned int zone() const { return mZone; }
  char         band() const { return mBand; }
  coord        easting() const { return mEasting; }
  coord        northing() const { return mNorthing; }
  
private:
  unsigned int mZone{32};
  char         mBand{'N'};
  coord        mEasting{1};
  coord        mNorthing{2};
private:
  friend class boost::serialization::access;
  template<typename Archive>
  void save(Archive & ar, unsigned int version) const;
  template<typename Archive>
  void load(Archive & ar, unsigned int version);
  BOOST_SERIALIZATION_SPLIT_MEMBER()
};
  
std::ostream & operator << ( std::ostream & os, utm_split const & v );
  
// --------------------------------------------------------------------------------------------------------------------
}
// --------------------------------------------------------------------------------------------------------------------
BOOST_CLASS_VERSION(demo::utm_split,0)

// split BOOST_CLASS_EXPORT by
// 1. placing BOOST_CLASS_EXPORT_KEX in the header
// 2. placing BOOST_CLASS_EXPORT_IMPLEMENT in the sources along with including the desired archive types.
//    Make sure to include the archive types before any other serialization headers especially the export.hpp.
// as a result the serialization code will be in the compile unit that contains BOOST_CLASS_EXPORT_IMPLEMENT.
// This is particularly important for building shared-objects or DLLs, to maintain the one-definition-rule in c++.
BOOST_CLASS_EXPORT_KEY(demo::utm_split)
// --------------------------------------------------------------------------------------------------------------------
#endif
// ====================================================================================================================
