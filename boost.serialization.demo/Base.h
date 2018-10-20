//
//  Base.hpp
//  boost.serialization.demo
//

#ifndef BASE_H
#define BASE_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/export.hpp>

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
  //
  // might result in duplicated code and problems in deployment and upgrade procedures.
  template <typename Archive>
  void serialize( Archive & ar [[maybe_unused]], unsigned int version [[maybe_unused]] )
  {
  }
};

// --------------------------------------------------------------------------------------------------------------------
} // demo
// --------------------------------------------------------------------------------------------------------------------

BOOST_SERIALIZATION_ASSUME_ABSTRACT(demo::Base)
BOOST_CLASS_VERSION( demo::Base, 0 )
BOOST_CLASS_EXPORT_KEY(demo::Base)

// --------------------------------------------------------------------------------------------------------------------
#endif /* BASE_H */
// ====================================================================================================================
