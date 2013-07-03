// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILSJSON
#define SSVUJ_UTILSJSON

#include <vector>
#include <string>
#include <SSVUtils/SSVUtils.h>
#include <SSVJsonCpp/SSVJsonCpp.h>
#include "SSVUtilsJson/Utils/Internal/Helper.h"

namespace ssvuj
{
	inline static unsigned int size(const Json::Value& mArray) { return mArray.size(); }
	inline static unsigned int size(const Json::Value& mRoot, const std::string& mValue) { return mRoot[mValue].size(); }

	inline static bool has(const Json::Value& mRoot, const std::string& mValue) { return mRoot.isMember(mValue); }

	template<typename T> inline static void set(Json::Value& mRoot, const std::string& mValue, T mValueToSet) { mRoot[mValue] = mValueToSet; }

	template<typename T> inline static T as(const Json::Value& mRoot) { return Internal::AsHelper<T>::as(mRoot); }
	template<typename T> inline static T as(const Json::Value& mRoot, const std::string& mValue) { return as<T>(mRoot[mValue]); }
	template<typename T> inline static T as(const Json::Value& mArray, unsigned int mIndex) { return as<T>(mArray[mIndex]); }
	template<typename T> inline static T as(const Json::Value& mRoot, const std::string& mValue, T mDefault) { return mRoot.isMember(mValue) ? as<T>(mRoot, mValue) : mDefault; }
	template<typename T> inline static T as(const Json::Value& mArray, unsigned int mIndex, T mDefault) { return mArray.isValidIndex(mIndex) ? as<T>(mArray, mIndex) : mDefault; }

	inline static Json::Value getRootFromString(const std::string& mString)
	{
		Json::Value result; Json::Reader reader;
		if(!reader.parse(mString, result, false)) ssvu::log(reader.getFormatedErrorMessages() + "\n" + "From: [" + mString + "]", "ssvuj::getRootFromString");
		return result;
	}
	inline static Json::Value getRootFromFile(const std::string& mPath)
	{
		Json::Value result; Json::Reader reader;
		if(!reader.parse(ssvu::FileSystem::getFileContents(mPath), result, false)) ssvu::log(reader.getFormatedErrorMessages() + "\n" + "From: [" + mPath + "]", "ssvuj::getRootFromString");
		return result;
	}
}

#endif
