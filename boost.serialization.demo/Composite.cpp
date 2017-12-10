//
//  Composite.cpp
//  boost.serialization.demo
//
//  Created by Abhijit Sovakar on 10.12.17.
//  Copyright © 2017 Abhijit Sovakar. All rights reserved.
//

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
    mObjects.emplace_back( new DerivedOne );
  } while( --ones );
  do
  {
    mObjects.emplace_back( new DerivedTwo);
  } while (--twos );
}

void Composite::addObserver( Base * observer )
{
  mObservers.push_back(observer);
}

void Composite::dump( std::ostream & os )
{
  using boost::range::for_each;
  os << "objects:\n";
  for_each(mObjects, [&os] ( auto const & object ) { os << "  " << object.get() << "\n"; } );
  os << "observers:\n";
  for_each(mObservers, [&os] ( auto const & object ) { os << "  " << object << "\n"; } );
}

// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------
BOOST_CLASS_EXPORT_IMPLEMENT(demo::Composite)
// ====================================================================================================================
