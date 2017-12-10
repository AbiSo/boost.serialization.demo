//
//  Derived.hpp
//  boost.serialization.demo
//
//  Created by Abhijit Sovakar on 10.12.17.
//  Copyright © 2017 Abhijit Sovakar. All rights reserved.
//

#ifndef DERIVED_H
#define DERIVED_H

#include "Base.h"
#include "utm.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/base_object.hpp>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

template<typename Tag, typename V>
class Derived : public Base
{
public:
  Derived() = default;
  ~Derived() = default;
  Derived( Derived const & ) = default;
  Derived & operator = (Derived const &) = default;
private:
  V mValue{};
private:
  friend class boost::serialization::access;
  
  // the required serialization hook
  template <typename Archive>
  void serialize( Archive & ar, unsigned int version );
};

struct One {};
struct Two {};

using DerivedOne = Derived<One,int>;
using DerivedTwo = Derived<Two,utm>;

// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------

BOOST_CLASS_VERSION( demo::DerivedOne, 0 )
BOOST_CLASS_VERSION( demo::DerivedTwo, 0 )

BOOST_CLASS_EXPORT_KEY(demo::DerivedOne)
BOOST_CLASS_EXPORT_KEY(demo::DerivedTwo)

// --------------------------------------------------------------------------------------------------------------------
#endif /* DERIVED_H */
// ====================================================================================================================
