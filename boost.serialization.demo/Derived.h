//
//  Derived.hpp
//  boost.serialization.demo
//

#ifndef DERIVED_H
#define DERIVED_H

#include "Base.h"
#include "utm.h"
#include "utm2.h"

#include <boost/format.hpp>
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
    out << boost::format("%1$-8s value: %2%") % Tag::name() % mValue;
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

struct One { static const char *name() { return "primus"; } };
struct Two { static const char *name() { return "secundus"; } };
struct Three { static const char *name() { return "tertius"; } };
struct Four { static const char *name() { return "quartus"; } };
struct Five { static const char *name() { return "quintus"; } };

using DerivedOne   = Derived<One,int>;
using DerivedTwo   = Derived<Two,utm>;
using DerivedThree = Derived<Three,std::string>;
using DerivedFour  = Derived<Four,int>;
using DerivedFive  = Derived<Five,utm2>;
  
  // --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------

BOOST_CLASS_VERSION( demo::DerivedOne, 0 )
BOOST_CLASS_VERSION( demo::DerivedTwo, 0 )
BOOST_CLASS_VERSION( demo::DerivedThree, 0 )
BOOST_CLASS_VERSION( demo::DerivedFour, 0 )
BOOST_CLASS_VERSION( demo::DerivedFive, 0 )

BOOST_CLASS_EXPORT_KEY(demo::DerivedOne)
BOOST_CLASS_EXPORT_KEY(demo::DerivedTwo)
BOOST_CLASS_EXPORT_KEY(demo::DerivedThree)
BOOST_CLASS_EXPORT_KEY(demo::DerivedFour)
BOOST_CLASS_EXPORT_KEY(demo::DerivedFive)

// --------------------------------------------------------------------------------------------------------------------
#endif /* DERIVED_H */
// ====================================================================================================================
