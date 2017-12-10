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

#include <boost/serialization/access.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/base_object.hpp>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

template<typename Tag>
class Derived : public Base
{
public:
  Derived() = default;
  ~Derived() = default;
  Derived( Derived const & ) = default;
  Derived & operator = (Derived const &) = default;
  
private:
  friend class boost::serialization::access;
  
  // the required serialization hook
  template <typename Archive>
  void serialize( Archive & ar, unsigned int version [[maybe_unused]] )
  {
    using boost::serialization::make_nvp;
    using boost::serialization::base_object;
    ar & make_nvp("base", base_object<Base>(*this) );
  }
};

struct One {};
struct Two {};

using DerivedOne = Derived<One>;
using DerivedTwo = Derived<Two>;

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
