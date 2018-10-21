//
//  Composite.hpp
//  boost.serialization.demo
//

#ifndef COMPOSITE_H
#define COMPOSITE_H

//#include <boost/serialization/version.hpp>
//#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

#include <memory>
#include <vector>

// --------------------------------------------------------------------------------------------------------------------
namespace demo {
// --------------------------------------------------------------------------------------------------------------------

constexpr const int CompositeVersion = 0;
  
class Base;

class Composite
{
public:
  Composite() = default;
  ~Composite() = default;
  Composite( size_t ones, size_t twos, size_t threes, size_t fours );
  Composite( Composite const & ) = delete;
  Composite & operator = ( Composite const & ) = delete;
  void addObserver( Base * observer );
  void dump( std::ostream & os );
private:
  std::vector< std::unique_ptr<Base> > mObjects;
  std::vector< Base* > mObservers;
  bool const mVersionOne{CompositeVersion==1}; // 0 vs. 1
private:
  friend class boost::serialization::access;
  template <typename Archive>
  void serialize(Archive & ar, unsigned int version);
};

// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------

BOOST_CLASS_VERSION( demo::Composite, demo::CompositeVersion )
BOOST_CLASS_EXPORT_KEY(demo::Composite)

// --------------------------------------------------------------------------------------------------------------------
#endif /* COMPOSITE_H */
// ====================================================================================================================
