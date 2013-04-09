// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILSJSON
#define SSVS_UTILSJSON

#include <vector>
#include <string>
#include <jsoncpp/json.h>
#include <jsoncpp/reader.h>

namespace ssvuj
{
	template<typename T> T as(const Json::Value& mRoot);
	template<typename T> T as(const Json::Value& mRoot, const std::string& mValue) { return as<T>(mRoot[mValue]); }
	template<typename T> T as(const Json::Value& mArray, unsigned int mIndex) { return as<T>(mArray[mIndex]); }
	template<typename T> T asOrDefault(const Json::Value& mRoot, const std::string& mValue, T mDefault) { return mRoot.isMember(mValue) ? as<T>(mRoot, mValue) : mDefault; }
	template<typename T> T asOrDefault(const Json::Value& mArray, unsigned int mIndex, T mDefault) { return mArray.isValidIndex(mIndex) ? as<T>(mArray, mIndex) : mDefault; }

	template<typename T> std::vector<T> asVector(const Json::Value& mRoot)
	{
		std::vector<T> result;
		for(unsigned int i{0}; i < mRoot.size(); ++i) result.push_back(as<T>(mRoot, i));
		return result;
	}
	template<typename T> std::vector<T> asVector(const Json::Value& mRoot, const std::string& mValue) { return asVector<T>(mRoot[mValue]); }
	template<typename T> std::vector<T> asVector(const Json::Value& mArray, unsigned int mIndex) { return asVector<T>(mArray[mIndex]); }
	template<typename T> std::vector<T> asVectorOrDefault(const Json::Value& mRoot, const std::string& mValue, std::vector<T> mDefault) { return mRoot.isMember(mValue) ? asVector<T>(mRoot, mValue) : mDefault; }
	template<typename T> std::vector<T> asVectorOrDefault(const Json::Value& mArray, unsigned int mIndex, std::vector<T> mDefault) { return mArray.isValidIndex(mIndex) ? asVector<T>(mArray, mIndex) : mDefault; }

	Json::Value getRootFromString(const std::string& mString);
	Json::Value getRootFromFile(const std::string& mPath);
}

#endif
