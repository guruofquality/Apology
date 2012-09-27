//
// Copyright 2011-2012 Josh Blum
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef INCLUDED_APOLOGY_CONFIG_HPP
#define INCLUDED_APOLOGY_CONFIG_HPP

// http://gcc.gnu.org/wiki/Visibility
// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define APOLOGY_HELPER_DLL_IMPORT __declspec(dllimport)
  #define APOLOGY_HELPER_DLL_EXPORT __declspec(dllexport)
  #define APOLOGY_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define APOLOGY_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define APOLOGY_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define APOLOGY_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define APOLOGY_HELPER_DLL_IMPORT
    #define APOLOGY_HELPER_DLL_EXPORT
    #define APOLOGY_HELPER_DLL_LOCAL
  #endif
#endif

// Now we use the generic helper definitions above to define APOLOGY_API and APOLOGY_LOCAL.
// APOLOGY_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// APOLOGY_LOCAL is used for non-api symbols.

#ifdef APOLOGY_DLL // defined if APOLOGY is compiled as a DLL
  #ifdef APOLOGY_DLL_EXPORTS // defined if we are building the APOLOGY DLL (instead of using it)
    #define APOLOGY_API APOLOGY_HELPER_DLL_EXPORT
  #else
    #define APOLOGY_API APOLOGY_HELPER_DLL_IMPORT
  #endif // APOLOGY_DLL_EXPORTS
  #define APOLOGY_LOCAL APOLOGY_HELPER_DLL_LOCAL
#else // APOLOGY_DLL is not defined: this means APOLOGY is a static lib.
  #define APOLOGY_API
  #define APOLOGY_LOCAL
#endif // APOLOGY_DLL

#include <ciso646>

#include <iostream>

#define APOLOGY_HERE() {std::cout << __FILE__ << ":" << __LINE__ << std::endl;}
#define APOLOGY_VAR(var) {std::cout << #var << " = " << (var) << std::endl;}

namespace Apology
{
    struct Base
    {
        //empty
    };
};

#endif /*INCLUDED_APOLOGY_CONFIG_HPP*/
