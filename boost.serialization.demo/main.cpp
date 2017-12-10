//
//  main.cpp
//  boost.serialization.demo
//
//  Created by Abhijit Sovakar on 09.12.17.
//  Copyright © 2017 Abhijit Sovakar. All rights reserved.
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
// ---------------------- boost
#include <boost/version.hpp>
#include <boost/format.hpp>
#include <boost/optional.hpp>
#include <boost/program_options.hpp>
// ---------------------- C++/STL
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

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
  bool   WithoutHeader;
  bool   Binary;
};

Options args(int argc, const char *argv[])
{
  Options rv;

  namespace po = boost::program_options;
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "produce help message")
    ("in,i", po::value<string>(&rv.Input), "read archive from file")
    ("out,o", po::value<string>(&rv.Output),  "write archive to this file")
    ("no-header,s", "omit archive header information")
    ("binary,b", "use binary archive instead of xml archive")
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
  std::unique_ptr<demo::DerivedOne> observer;
  demo::Composite object;
  demo::utm       utm;
  
  Archive ia(in,flags);
  ia >> make_nvp("observer", observer);
  ia >> make_nvp("obbject", object );
  ia >> make_nvp("utm", utm);
  
  std::cout << "observer: " << observer.get() << "\n";
  object.dump(std::cout);
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
void write_archive( std::ostream & out, unsigned int flags)
{
  using boost::serialization::make_nvp;
  
  auto observer = std::make_unique<demo::DerivedOne>();
  demo::Composite object(2,1);
  object.addObserver(observer.get());
  demo::utm utm(31,'U',321.123,123.321);
  
  Archive oa(out,flags);
  oa << make_nvp("observer", observer);
  oa << make_nvp("object", object);
  oa << make_nvp("utm", utm);
  
  std::cout << "observer: " << observer.get() << "\n";
  object.dump(std::cout);
}

void write_archive( string filename, unsigned int flags, bool binary )
try
{
  std::cout << "# write archive to file " << filename << "\n";
  std::ios::openmode mode = binary ? (std::ios::out|std::ios::binary) : std::ios::out;
  std::ofstream ofile(filename,mode);
  if (binary)
    write_archive<boost::archive::binary_oarchive>(ofile, flags );
  else
    write_archive<boost::archive::xml_oarchive>(ofile, flags );
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
  format msg("%1$-16s : %2%");
  cout << msg % "c++" % __cplusplus << "\n";
  cout << msg % "boost" % BOOST_VERSION << "\n";
  cout << msg % "in" % opt.Input  << "\n";
  cout << msg % "out" % opt.Output << "\n";
  cout << msg % "no header" % opt.WithoutHeader << "\n";
  cout << msg % "binary archive" % opt.Binary << "\n";

  // serialize
  unsigned int flags{0};
  if ( opt.WithoutHeader )
    flags |= boost::archive::no_header;
  
  if ( !opt.Output.empty() ) write_archive( opt.Output, flags, opt.Binary );
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
