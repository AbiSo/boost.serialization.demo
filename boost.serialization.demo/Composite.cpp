//
//  Composite.cpp
//  boost.serialization.demo
//

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include "Composite.h"
#include "Derived.h"

#include <boost/range/algorithm/for_each.hpp>

#include <iostream>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

Composite::Composite(size_t ones, size_t twos)
{
  do
  {
    mObjects.emplace_back( new DerivedOne(static_cast<int>(ones)) );
  } while( --ones );
  do
  {
    mObjects.emplace_back( new DerivedTwo(utm(32,'N',5.5,50.05)));
  } while (--twos );
  
  mObjects.emplace_back( new DerivedThree("hello") );
  
}

void Composite::addObserver( Base * observer )
{
  mObservers.push_back(observer);
}

void Composite::dump( std::ostream & os )
{
  using boost::range::for_each;
  os << "composite:\n";
  os << "  objects:\n";
  for_each(mObjects, [&os] ( auto && object ) { os << "    " << object.get() << " ["; object->dump(os) << "]\n"; } );
  os << "  observers:\n";
  for_each(mObservers, [&os] ( auto && object ) { os << "    " << object  << " ["; object->dump(os) << "]\n"; } );
}

template<typename Archive>
void Composite::serialize(Archive & ar, [[maybe_unused]] unsigned int version)
{
  // make sure the archive knows the derived object types if the derived::serialize variations were
  // not pre-instantiated.
  //ar.register_type( static_cast< DerivedOne* >(nullptr) );
  //ar.register_type( static_cast< DerivedTwo* >(nullptr) );
  
  // serialize the objects
  ar & boost::serialization::make_nvp("Objects", mObjects);
  
  // serializte the observers
  ar & boost::serialization::make_nvp("Observers", mObservers);
}

// --------------------------------------------------------------------------------------------------------------------

template
void Composite::serialize(boost::archive::xml_oarchive & ar, unsigned int version);
template
void Composite::serialize(boost::archive::xml_iarchive & ar, unsigned int version);

template
void Composite::serialize(boost::archive::binary_oarchive & ar, unsigned int version);
template
void Composite::serialize(boost::archive::binary_iarchive & ar, unsigned int version);

// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------
BOOST_CLASS_EXPORT_IMPLEMENT(demo::Composite)
// ====================================================================================================================
