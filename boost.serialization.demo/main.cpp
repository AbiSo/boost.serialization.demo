//
//  main.cpp
//  boost.serialization.demo
//

// ---------------------- first archive headers
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
// ---------------------- my
#include "Composite.h"
#include "Derived.h"
#include "utm.h"
#include "utm1.h"
#include "utm2.h"
#include "utm3.h"
// ---------------------- boost
#include <boost/version.hpp>
#include <boost/format.hpp>
#include <boost/optional.hpp>
#include <boost/program_options.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/timer/timer.hpp>
// ---------------------- C++/STL
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <utility>

// some short cuts
using std::pair;
using std::make_pair;
using std::string;
using std::cout;
using std::cerr;
using std::clog;

using boost::format;

struct Options
{
  string Output;
  string Input;
  size_t Count{10};
  bool   WithoutHeader{false};
  bool   Binary{false};
};

Options args(int argc, const char *argv[])
{
  Options rv;

  namespace po = boost::program_options;
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "this help message")
    ("in,i", po::value(&rv.Input), "read archive from file")
    ("out,o", po::value(&rv.Output),  "write archive to this file")
    ("no-header,s", "omit archive header information")
    ("binary,b", "use binary archive instead of xml archive")
    ("count", po::value(&rv.Count), "min. number of elements")
    ;
  

  try
  {
    po::variables_map vm;
    po::store(po::parse_command_line(argc,argv,desc), vm);
    po::notify(vm);
    
    if (vm.count("help"))
    {
      cout << "\n";
      cout << desc << "\n";
      std::exit(EXIT_SUCCESS);
    }
    
    rv.WithoutHeader = vm.count("no-header") > 0;
    rv.Binary        = vm.count("binary") > 0;

  }
  catch( std::exception & x )
  {
    cerr << "error: " << x.what() << "\n";
    cerr << "\n";
    cerr << desc << "\n";
    std::exit(EXIT_FAILURE);
  }
  
  return rv;
}

template< typename Archive>
void read_archive( std::istream & in, unsigned int flags)
{
  using boost::serialization::make_nvp;
  std::unique_ptr<demo::DerivedThree> observer;
  std::unique_ptr<demo::DerivedFive> stalker;
  demo::Composite object;

  demo::utm  utm_primitive;
  demo::utm1 utm_non_intrusive;
  demo::utm2 utm_serialize;
  demo::utm3 utm_split;

  {
    boost::timer::auto_cpu_timer t;
    Archive ia(in,flags);
    ia >> make_nvp("observer", observer);
    ia >> make_nvp("object", object );
    ia >> make_nvp("stalker", stalker);
    
    ia >> make_nvp("utm_primitive", utm_primitive);
    ia >> make_nvp("utm_non_intrusive", utm_non_intrusive);
    ia >> make_nvp("utm_serialize", utm_serialize);
    ia >> make_nvp("utm_split", utm_split);
  }

  std::cout << "observer         : " << observer.get() << " ["; observer->dump(std::cout) << "]\n";
  std::cout << "stalker          : " << stalker.get() << " ["; stalker->dump(std::cout) << "]\n";
  object.dump(std::cout);
  std::cout << "utm primitive    : " << utm_primitive << std::endl;
  std::cout << "utm non-intrusive: " << utm_non_intrusive << std::endl;
  std::cout << "utm serialize    : " << utm_serialize << std::endl;
  std::cout << "utm splt serial. : " << utm_split << std::endl;
}

void read_archive( string filename, unsigned int flags, bool binary )
try
{
  std::cout << "# read archive from file " << filename << "\n";
  std::ios::openmode mode = binary ? (std::ios::in|std::ios::binary) : std::ios::in;
  std::ifstream ifile(filename,mode);
  if (binary)
    read_archive<boost::archive::binary_iarchive>(ifile, flags );
  else
    read_archive<boost::archive::xml_iarchive>(ifile, flags );
}
catch(std::exception & x)
{
  cerr << "read error: " << filename << ": " << x.what() << "\n";
}

template< typename Archive>
void write_archive( std::ostream & out, unsigned int flags, size_t count)
{
  using boost::serialization::make_nvp;
  
  auto observer = std::make_unique<demo::DerivedThree>("observer");
  auto stalker = std::make_unique<demo::DerivedFive>(demo::utm2(1,'A',321,123));

  auto one   = std::max(static_cast<size_t>(1), static_cast<size_t>(count * 1 / 10) );
  auto two   = std::max(static_cast<size_t>(1), static_cast<size_t>(count * 2 / 10) );
  auto three = std::max(static_cast<size_t>(2), static_cast<size_t>(count * 3 / 10) );
  auto four  = std::max(static_cast<size_t>(3), static_cast<size_t>(count * 4 / 10) );
  
  demo::Composite object(one,two,three,four);
  object.addObserver(observer.get());
  object.addObserver(stalker.get());
  
  demo::utm  utm_primitive(1,'A',1,2);
  demo::utm1 utm_non_intrusive(3,'B',5,8);
  demo::utm2 utm_serialize(13,'C',21,34);
  demo::utm3 utm_split(55,'D',89,144);

  {
    boost::timer::auto_cpu_timer t;
    Archive oa(out,flags);
    oa << make_nvp("observer", observer);
    oa << make_nvp("object", object);
    oa << make_nvp("stalker", stalker);
    oa << make_nvp("utm_primitive", utm_primitive);
    oa << make_nvp("utm_non_intrusive", utm_non_intrusive);
    oa << make_nvp("utm_serialize", utm_serialize);
    oa << make_nvp("utm_split", utm_split);
  }
  
  std::cout << "observer         : " << observer.get() << " ["; observer->dump(std::cout) << "]\n";
  std::cout << "stalker          : " << stalker.get() << " ["; stalker->dump(std::cout) << "]\n";
  object.dump(std::cout);
  std::cout << "utm primitive    : " << utm_primitive << std::endl;
  std::cout << "utm non-intrusive: " << utm_non_intrusive << std::endl;
  std::cout << "utm serialize    : " << utm_serialize << std::endl;
  std::cout << "utm splt serial. : " << utm_split << std::endl;
}

void write_archive( string filename, unsigned int flags, bool binary, size_t count )
try
{
  std::cout << "# write archive to file " << filename << "\n";
  std::ios::openmode mode = binary ? (std::ios::out|std::ios::binary) : std::ios::out;
  std::ofstream ofile(filename,mode);
  if (binary)
    write_archive<boost::archive::binary_oarchive>(ofile, flags, count );
  else
    write_archive<boost::archive::xml_oarchive>(ofile, flags, count );
}
catch(std::exception & x)
{
  cerr << "write error: " << filename << ": " << x.what() << "\n";
  throw;
}

int main(int argc, const char * argv[])
try
{
  Options opt = args(argc,argv);

  // general info
  format msg("%1$-18s: %2%");
  cout << msg % "compiler" % BOOST_COMPILER << "\n";
  cout << msg % "c++" % __cplusplus << "\n";
  cout << msg % "boost" % BOOST_VERSION << "\n";
  cout << msg % "in" % opt.Input  << "\n";
  cout << msg % "out" % opt.Output << "\n";
  cout << std::boolalpha;
  cout << msg % "no header" % "" << opt.WithoutHeader << "\n";
  cout << msg % "binary archive" % "" << opt.Binary << "\n";
  cout << msg % "composite version" % demo::CompositeVersion << "\n";
  // serialize
  unsigned int flags{0};
  if ( opt.WithoutHeader )
    flags |= boost::archive::no_header;
  
  if ( !opt.Output.empty() ) write_archive( opt.Output, flags, opt.Binary, opt.Count );
  if ( !opt.Input.empty() ) read_archive( opt.Input, flags, opt.Binary );
}
catch( boost::archive::archive_exception & )
{
  return EXIT_FAILURE;
}
catch( std::exception & x)
{
  cerr << "error: " << x.what() << "\n";
  return EXIT_FAILURE;
}
