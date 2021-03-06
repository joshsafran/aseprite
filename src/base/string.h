// ASEPRITE base library
// Copyright (C) 2001-2012  David Capello
//
// This source file is distributed under a BSD-like license, please
// read LICENSE.txt for more information.

#ifndef BASE_STRING_H_INCLUDED
#define BASE_STRING_H_INCLUDED

#include <string>

namespace base {

  typedef std::string string;

  string string_to_lower(const string& original);
  string string_to_upper(const string& original);

}

#endif
