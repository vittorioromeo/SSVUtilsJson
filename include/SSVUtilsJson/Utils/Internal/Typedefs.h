// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_INTERNAL_TYPEDEFS
#define SSVUJ_INTERNAL_TYPEDEFS

#include <string>
#include <memory>
#include <SSVJsonCpp/SSVJsonCpp.h>

namespace ssvuj
{
	using Impl = Json::Value;
	using Value = Impl;
	using String = std::string;
	template<typename T> using Uptr = std::unique_ptr<T>;
}

#endif
