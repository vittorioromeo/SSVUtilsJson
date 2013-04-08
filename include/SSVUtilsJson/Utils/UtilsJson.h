// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILSJSON
#define SSVS_UTILSJSON

#include <vector>
#include <string>
#include <jsoncpp/json.h>
#include <jsoncpp/reader.h>
#include <SSVUtils/SSVUtils.h>

namespace ssvuj
{
	template<typename T> T as(const Json::Value& mRoot);
	template<typename T> T getValue(const Json::Value& mRoot, const std::string& mValue) { return as<T>(mRoot[mValue]); }
	template<typename T> T getValue(const Json::Value& mArray, unsigned int mIndex) { return as<T>(mArray[mIndex]); }
	template<typename T> T getValueOrDefault(const Json::Value& mRoot, const std::string& mValue, T mDefault) { return mRoot.isMember(mValue) ? getValue<T>(mRoot, mValue) : mDefault; }
	template<typename T> T getValueOrDefault(const Json::Value& mArray, unsigned int mIndex, T mDefault) { return mArray.isValidIndex(mIndex) ? getValue<T>(mArray, mIndex) : mDefault; }

	template<typename T> T asContainer(const Json::Value& mRoot)
	{
		typedef typename T::value_type Item;
		typedef ssvu::Traits::Container<T, Item> ContainerTraits;

		T result;
		for(unsigned int i{0}; i < mRoot.size(); ++i) ContainerTraits::add(result, getValue<Item>(mRoot, i));
		return result;
	}
	template<typename T> T getContainer(const Json::Value& mRoot, const std::string& mValue) { return asContainer<T>(mRoot[mValue]); }
	template<typename T> T getContainer(const Json::Value& mArray, unsigned int mIndex) { return asContainer<T>(mArray[mIndex]); }
	template<typename T> T getContainerOrDefault(const Json::Value& mRoot, const std::string& mValue, T mDefault) { return mRoot.isMember(mValue) ? getContainer<T>(mRoot, mValue) : mDefault; }
	template<typename T> T getContainerOrDefault(const Json::Value& mArray, unsigned int mIndex, T mDefault) { return mArray.isValidIndex(mIndex) ? getContainer<T>(mArray, mIndex) : mDefault; }

	Json::Value getRootFromString(const std::string& mString);
	Json::Value getRootFromFile(const std::string& mPath);
}

#endif
