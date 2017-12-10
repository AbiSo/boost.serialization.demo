//
//  demo.h
//  boost.serialization.demo
//
//  Created by Abhijit Sovakar on 09.12.17.
//  Copyright © 2017 Abhijit Sovakar. All rights reserved.
//

#pragma once
#ifndef DEMO_H
#define DEMO_H

#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/export.hpp>

#include <memory>
#include <vector>
#include <iosfwd>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

class Base
{
public:
  Base() = default;
  virtual ~Base() = 0;
  Base( Base const & ) = default;
  Base & operator = ( Base const & ) = default;
private:
  // let boost serialization see your class
  friend class boost::serialization::access;
  
  // the required serialization hook
  template <typename Archive>
  void serialize( Archive & ar [[maybe_unused]], unsigned int version [[maybe_unused]] )
  {
  }
};

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

class Composite
{
public:
  Composite() = default;
  ~Composite() = default;
  Composite( size_t ones, size_t twos );
  Composite( Composite const & ) = delete;
  Composite & operator = ( Composite const & ) = delete;
  void addObserver( Base * observer );
  void dump( std::ostream & os );
private:
  std::vector< std::unique_ptr<Base> > mObjects;
  std::vector< Base* > mObservers;
private:
  friend class boost::serialization::access;
  template <typename Archive>
  void serialize(Archive & ar, unsigned int version [[maybe_unused]])
  {
    // make sure the archive knows the derived object types.
    ar.register_type( static_cast< DerivedOne* >(nullptr) );
    ar.register_type( static_cast< DerivedTwo* >(nullptr) );
    
    // serialize the objects
    ar & boost::serialization::make_nvp("Objects", mObjects);
    
    // serializte the observers
    ar & boost::serialization::make_nvp("Observers", mObservers);
  }
};
  
// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------
BOOST_SERIALIZATION_ASSUME_ABSTRACT(demo::Base)
BOOST_CLASS_VERSION( demo::Base, 0 )

BOOST_CLASS_VERSION( demo::DerivedOne, 0 )
BOOST_CLASS_VERSION( demo::DerivedTwo, 0 )
BOOST_CLASS_VERSION( demo::Composite, 0 )

// --------------------------------------------------------------------------------------------------------------------
#endif /* DEMO_H */
// ====================================================================================================================
