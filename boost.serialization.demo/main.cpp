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
// ---------------------- my
#include "demo.h"
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
};

Options args(int argc, const char *argv[])
{
  Options rv;

  namespace po = boost::program_options;
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "produce help message")
    ("in,i", po::value<string>(&rv.Input)->implicit_value("test.xml"), "read archive from file")
    ("out,o", po::value<string>(&rv.Output)->implicit_value("test.xml"),  "write archive to this file")
    ("no-header", "omit archive header information")
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

void read_archive( string filename, unsigned int flags )
try
{
  std::ifstream ifile(filename);
  boost::archive::xml_iarchive ia(ifile, flags );
}
catch(std::exception & x)
{
  cerr << "read error: " << filename << ": " << x.what() << "\n";
}

void write_archive( string filename, unsigned int flags )
try
{
  std::ofstream ofile(filename);
  boost::archive::xml_oarchive oa(ofile, flags );
}
catch(std::exception & x)
{
  cerr << "write error: " << filename << ": " << x.what() << "\n";
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
  
  // serialize
  unsigned int flags{0};
  if ( opt.WithoutHeader )
    flags |= boost::archive::no_header;
  
  if ( !opt.Output.empty() ) write_archive( opt.Output, flags );
  if ( !opt.Input.empty() ) read_archive( opt.Input, flags );
}
catch( std::exception & x)
{
  cerr << "error: " << x.what() << "\n";
  return EXIT_FAILURE;
}
