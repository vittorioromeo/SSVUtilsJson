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
	template<typename T> T getValueOrDefault(const Json::Value& mRoot, const std::string& mValue, T mDefault) { return mRoot.isMember(mValue) ? getValue<T>(mRoot, mValue) : mDefault; }
	template<typename T> T getArrayValue(const Json::Value& mArray, int mIndex) { return as<T>(mArray[mIndex]); }

	template<typename TContainer> TContainer asContainer(const Json::Value& mRoot)
	{
		typedef typename TContainer::value_type Item;
		typedef ssvu::Traits::Container<TContainer, Item> ContainerTraits;

		TContainer result; Json::Value array(mRoot);
		for(unsigned int i{0}; i < array.size(); ++i) ContainerTraits::add(result, getArrayValue<Item>(array, i));
		return result;
	}

	Json::Value getRootFromString(const std::string& mString);
	Json::Value getRootFromFile(const std::string& mPath);
}

#endif
