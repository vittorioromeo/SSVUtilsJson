// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILSJSON
#define SSVUJ_UTILSJSON

#include <vector>
#include <string>
#include <SSVJsonCpp/SSVJsonCpp.h>
#include "SSVUtilsJson/Utils/Internal/Helper.h"

namespace ssvuj
{
	unsigned int size(const Json::Value& mArray) { return mArray.size(); }
	unsigned int size(const Json::Value& mRoot, const std::string& mValue) { return mRoot[mValue].size(); }

	bool has(const Json::Value& mRoot, const std::string& mValue) { return mRoot.isMember(mValue); }

	template<typename T> void set(Json::Value& mRoot, const std::string& mValue, T mValueToSet) { mRoot[mValue] = mValueToSet; }

	template<typename T> T as(const Json::Value& mRoot) { return Internal::AsHelper<T>::as(mRoot); }
	template<typename T> T as(const Json::Value& mRoot, const std::string& mValue) { return as<T>(mRoot[mValue]); }
	template<typename T> T as(const Json::Value& mArray, unsigned int mIndex) { return as<T>(mArray[mIndex]); }
	template<typename T> T as(const Json::Value& mRoot, const std::string& mValue, T mDefault) { return mRoot.isMember(mValue) ? as<T>(mRoot, mValue) : mDefault; }
	template<typename T> T as(const Json::Value& mArray, unsigned int mIndex, T mDefault) { return mArray.isValidIndex(mIndex) ? as<T>(mArray, mIndex) : mDefault; }

	Json::Value getRootFromString(const std::string& mString);
	Json::Value getRootFromFile(const std::string& mPath);
}

#endif
