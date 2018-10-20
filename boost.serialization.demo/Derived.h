//
//  Derived.hpp
//  boost.serialization.demo
//

#ifndef DERIVED_H
#define DERIVED_H

#include "Base.h"
#include "utm.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/base_object.hpp>

#include <iostream>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

template<typename Tag, typename V>
class Derived : public Base
{
public:
  Derived() = default;
  Derived( V v ) : mValue(v) {}
  ~Derived() = default;
  Derived( Derived const & ) = default;
  Derived & operator = (Derived const &) = default;
  
  std::ostream & dump( std::ostream & out ) const override
  {
    out << "value: " << mValue;
    return out;
  }
  
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
struct Three {};
  
using DerivedOne   = Derived<One,int>;
using DerivedTwo   = Derived<Two,utm>;
using DerivedThree = Derived<Three,std::string>;

// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------

BOOST_CLASS_VERSION( demo::DerivedOne, 0 )
BOOST_CLASS_VERSION( demo::DerivedTwo, 0 )
BOOST_CLASS_VERSION( demo::DerivedThree, 0 )

BOOST_CLASS_EXPORT_KEY(demo::DerivedOne)
BOOST_CLASS_EXPORT_KEY(demo::DerivedTwo)
BOOST_CLASS_EXPORT_KEY(demo::DerivedThree)

// --------------------------------------------------------------------------------------------------------------------
#endif /* DERIVED_H */
// ====================================================================================================================
