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

#include <boost/serialization/vector.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/iterator_range_core.hpp>

#include <iostream>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

Composite::Composite(size_t ones, size_t twos, size_t threes, size_t fours)
{
  do
  {
    mObjects.emplace_back( new DerivedOne(static_cast<int>(ones)) );
  } while( --ones );
  do
  {
    mObjects.emplace_back( new DerivedTwo(utm_primitive(32,'N',5.5 + twos,50.05-twos)));
  } while (--twos );
  std::vector<const char*> digit{"zero", "uno", "dos", "tres" };
  do
  {
    mObjects.emplace_back( new DerivedThree( digit[threes % 4]) );
  } while( --threes );
  do
  {
    mObjects.emplace_back( new DerivedFour(static_cast<int>(fours)));
  } while (--fours);
}

void Composite::addObserver( Base * observer )
{
  mObservers.push_back(observer);
}

template<typename C>
auto make_range( C & range, size_t count )
{
  auto beg = range.begin();
  auto end = std::next(beg, std::min(count,range.size()));
  return boost::make_iterator_range(beg,end);
}
  
void Composite::dump( std::ostream & os )
{
  using boost::range::for_each;
  os << "composite:\n";
  os << "  objects #" << mObjects.size() << ":\n";
  for_each(make_range(mObjects,10), [&os] ( auto && object ) { os << "    " << object.get() << " ["; object->dump(os) << "]\n"; } );
  if ( mObjects.size() > 10 )
    os << "    ..." << mObjects.size() - 10 << " more..." << std::endl;
  os << "  observers #" << mObservers.size() << ":\n";
  for_each(make_range(mObservers,10), [&os] ( auto && object ) { os << "    " << object  << " ["; object->dump(os) << "]\n"; } );
  if ( mObservers.size() > 10 )
    os << "    ..." << mObservers.size() - 10 << " more..." << std::endl;
  os << "  version 1: " << mVersionOne << std::endl;
}

template<typename Archive>
void Composite::serialize(Archive & ar, [[maybe_unused]] const unsigned int version)
{
  // make sure the archive knows the derived object types if the derived::serialize variations were
  // not pre-instantiated.
  //ar.register_type( static_cast< DerivedOne* >(nullptr) );
  //ar.register_type( static_cast< DerivedTwo* >(nullptr) );
  
  // serialize the objects
  ar & boost::serialization::make_nvp("Objects", mObjects);
  
  // does not serialize shared objects
  // ar & boost::serialization::make_nvp("SharedObjects", mSharedObjects);
  
  // serializte the observers
  ar & boost::serialization::make_nvp("Observers", mObservers);
  
  // version one
  if ( version == 1 )
  {
    ar & boost::serialization::make_nvp("VersionOne", const_cast<bool&>(mVersionOne) );
  }
}

// --------------------------------------------------------------------------------------------------------------------
#if 0
template
void Composite::serialize(boost::archive::xml_oarchive & ar, unsigned int version);
template
void Composite::serialize(boost::archive::xml_iarchive & ar, unsigned int version);

template
void Composite::serialize(boost::archive::binary_oarchive & ar, unsigned int version);
template
void Composite::serialize(boost::archive::binary_iarchive & ar, unsigned int version);
#endif
// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------
BOOST_CLASS_EXPORT_IMPLEMENT(demo::Composite)
// ====================================================================================================================
