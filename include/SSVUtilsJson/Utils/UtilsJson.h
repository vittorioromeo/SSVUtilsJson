// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILSJSON
#define SSVUJ_UTILSJSON

#include <vector>
#include <string>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include "SSVUtilsJson/Utils/Internal/Helper.h"
#include "SSVUtilsJson/Utils/Internal/Typedefs.h"

namespace rapidjson
{
	Value::ConstValueIterator begin(const ssvuj::Value& mValue) { return mValue.Begin(); }
	Value::ConstValueIterator end(const ssvuj::Value& mValue) { return mValue.End(); }
}

namespace ssvuj
{
	bool has(const Value& mRoot, const std::string& mValue) { return mRoot.HasMember(mValue.c_str()); }

	SizeType size(const Value& mArray) { return mArray.Size(); }
	SizeType size(const Value& mRoot, const std::string& mValue) { return mRoot[mValue.c_str()].Size(); }

	template<typename T> void set(const Value& mRoot, const std::string& mValue, const T& mSet)	{ mRoot[mValue.c_str()] = mSet; }

	template<typename T> T as(const Value& mRoot)										{ return Internal::AsHelper<T>::as(mRoot); }
	template<typename T> T as(const Value& mRoot, const std::string& mValue)				{ return as<T>(mRoot[mValue.c_str()]); }
	template<typename T> T as(const Value& mArray, unsigned int mIndex)					{ return as<T>(mArray[mIndex]); }
	template<typename T> T as(const Value& mRoot, const std::string& mValue, T mDefault) { return mRoot.HasMember(mValue.c_str()) ? as<T>(mRoot, mValue) : mDefault; }
	template<typename T> T as(const Value& mArray, unsigned int mIndex, T mDefault)		{ return mArray.Size() > mIndex ? as<T>(mArray, mIndex) : mDefault; }

	Document getRootFromString(const std::string& mString);
	Document getRootFromFile(const std::string& mPath);
}

#endif
