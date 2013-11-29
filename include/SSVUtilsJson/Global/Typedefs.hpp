// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_GLOBAL_TYPEDEFS
#define SSVUJ_GLOBAL_TYPEDEFS

#include <string>
#include <SSVUtils/FileSystem/FileSystem.hpp>
#include "SSVUtilsJson/JsonCpp/JsonCpp.hpp"

namespace ssvuj
{
	using Obj = Json::Value;
	using Key = std::string;
	using Idx = unsigned int;
	using Writer = Json::StyledStreamWriter;
	using Reader = Json::Reader;
	using Path = ssvufs::Path;
	using Iterator = typename Json::Value::iterator;
	using ConstIterator = typename Json::Value::const_iterator;
}

#endif
