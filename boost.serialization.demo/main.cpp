//
//  main.cpp
//  boost.serialization.demo
//
//  Created by Abhijit Sovakar on 09.12.17.
//  Copyright © 2017 Abhijit Sovakar. All rights reserved.
//

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/version.hpp>
#include <boost/format.hpp>

#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/access.hpp>
#include <boost/optional.hpp>
#include <boost/program_options.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "mockup.h"

using std::pair;
using std::make_pair;
using std::string;
using std::cout;
using std::cerr;
using std::clog;

using boost::optional;
using boost::format;

using optional_arg = optional<string>;

pair<optional_arg,optional_arg> args(int argc, const char *argv[])
{
  namespace po = boost::program_options;
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "product help message")
    ("in,i", po::value<string>(), "read archive from file")
    ("out,o", po::value<string>(),  "write archive to this file")
  ;
  
  po::variables_map vm;

  try
  {
    po::store(po::parse_command_line(argc,argv,desc), vm);
    po::notify(vm);
    
    if (vm.count("help"))
    {
      cout << "\n";
      cout << desc << "\n";
      std::exit(EXIT_SUCCESS);
    }
  }
  catch( std::exception & x )
  {
    cerr << "error: " << x.what() << "\n";
    cerr << "\n";
    cerr << desc << "\n";
    std::exit(EXIT_FAILURE);
  }
  
  optional_arg in;
  optional_arg out;
  
  if ( vm.count("in") )
    in = vm["in"].as<string>();
  if ( vm.count("out") )
    out = vm["out"].as<string>();
  return {in,out};
}

void read_archive( string filename )
try
{
  std::ifstream ifile(filename);
  boost::archive::xml_iarchive ia(ifile);
}
catch(std::exception & x)
{
  cerr << "error: " << x.what() << "\n";
}

void write_archive( string filename )
try
{
  std::ofstream ofile(filename);
  boost::archive::xml_oarchive oa(ofile);
}
catch(std::exception & x)
{
  cerr << "error: " << x.what() << "\n";
}

int main(int argc, const char * argv[])
{
  auto [in,out] = args(argc,argv);

  // general info
  format msg("%1$-16s : %2%");
  cout << msg % "c++" % __cplusplus << "\n";
  cout << msg % "boost" % BOOST_VERSION << "\n";
  cout << msg % "in" % in.get_value_or("")  << "\n";
  cout << msg % "out" % out.get_value_or("") << "\n";
  
  // serialize
  if ( in ) read_archive( in.value() );
  if ( out ) write_archive( out.value() );
}
