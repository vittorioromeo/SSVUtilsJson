// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILSJSON
#define SSVS_UTILSJSON

#include <vector>
#include <string>
#include <json/json.h>
#include <json/reader.h>

namespace ssvuj
{
	template<typename T> T getValue(const Json::Value& mRoot, const std::string& mValue);
	template<typename T> T getValueOrDefault(const Json::Value& mRoot, const std::string& mValue, T mDefault) { return mRoot.isMember(mValue) ? getValue<T>(mRoot, mValue) : mDefault; }
	template<typename T> T getArrayValue(const Json::Value& mArray, int mIndex);
	template<typename T> std::vector<T> getArray(const Json::Value& mRoot, const std::string& mValue)
	{
		std::vector<T> result;
		Json::Value array(mRoot[mValue]);
		for(unsigned int i{0}; i < array.size(); ++i) result.push_back(getArrayValue<T>(array, i));
		return result;
	}
	template<typename T> std::vector<T> getArrayOrDefault(const Json::Value& mRoot, const std::string& mValue, std::vector<T> mDefault)
	{
		if(!mRoot.isMember(mValue)) return mDefault;
		return getArray<T>(mRoot, mValue);
	}
	Json::Value getRootFromString(const std::string& mString);
	Json::Value getRootFromFile(const std::string& mPath);
}

#endif
