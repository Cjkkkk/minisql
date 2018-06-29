#include <iostream>
#include <cstdlib>
#include <cstring>
#include "API.h"

#include "mc_driver.hpp"

int 
main( const int argc, const char **argv )
{
    MC::MC_Driver driver;
    API::init();
    std::cout << "minisql > ";
   /** check for the right # of arguments **/
   if(argc == 1){//  ./minisql
       driver.parse( std::cin );
   }
   else if( argc == 2 )// ./minisql -h
   {
      /** instantiate driver object **/
      /** example for piping input from terminal, i.e., using cat **/ 
      /** simple help menu **/
      if( std::strncmp( argv[ 1 ], "-h", 2 ) == 0 )
      {
         std::cout << "use no flag for pipe to std::cin\n";
         std::cout << "use -execfile [filename] to excute command from a file\n";
         std::cout << "use -h to get this menu\n";
         return( EXIT_SUCCESS );
      }
      /** example reading input from a file **/
      else
      {
         /** assume file, prod code, use stat to check **/
         std::cout << "unrecongized flag\n";
         return( EXIT_FAILURE );
      }
      driver.print( std::cout ) << "\n";
   }
   else if(argc == 3){// ./minisql -execfile filename
        if( std::strncmp( argv[ 1 ], "-execfile", 2 ) == 0 ){
            driver.parse( argv[ 2 ] );
        }
       API::save();
   }
   else
   {

      /** exit with failure condition **/
      std::cout <<"unrecongized command,you can use -h for help\n";
      return ( EXIT_FAILURE );
   }
   return( EXIT_SUCCESS );
}