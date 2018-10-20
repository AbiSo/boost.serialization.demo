//
//  Composite.hpp
//  boost.serialization.demo
//

#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <boost/serialization/vector.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/export.hpp>

#include <memory>
#include <vector>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

class Base;
  
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
  void serialize(Archive & ar, unsigned int version);
};

// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------

BOOST_CLASS_VERSION( demo::Composite, 0 )
BOOST_CLASS_EXPORT_KEY(demo::Composite)

// --------------------------------------------------------------------------------------------------------------------
#endif /* COMPOSITE_H */
// ====================================================================================================================
