// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILSJSON
#define SSVS_UTILSJSON

#include <vector>
#include <string>
#include <jsoncpp/json.h>
#include <jsoncpp/reader.h>
#include "SSVUtilsJson/Utils/Helper.h"

namespace ssvuj
{
	template<typename T> T as(const Json::Value& mRoot) { return AsHelper<T>::as(mRoot); }
	template<typename T> T as(const Json::Value& mRoot, const std::string& mValue) { return as<T>(mRoot[mValue]); }
	template<typename T> T as(const Json::Value& mArray, unsigned int mIndex) { return as<T>(mArray[mIndex]); }
	template<typename T> T as(const Json::Value& mRoot, const std::string& mValue, T mDefault) { return mRoot.isMember(mValue) ? as<T>(mRoot, mValue) : mDefault; }
	template<typename T> T as(const Json::Value& mArray, unsigned int mIndex, T mDefault) { return mArray.isValidIndex(mIndex) ? as<T>(mArray, mIndex) : mDefault; }

	Json::Value getRootFromString(const std::string& mString);
	Json::Value getRootFromFile(const std::string& mPath);
}

#endif
