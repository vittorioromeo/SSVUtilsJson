// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILSJSON
#define SSVUJ_UTILSJSON

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <SSVUtils/SSVUtils.h>
#include <SSVJsonCpp/SSVJsonCpp.h>
#include "SSVUtilsJson/Utils/Internal/Helper.h"
#include "SSVUtilsJson/Utils/Internal/Typedefs.h"

namespace rapidjson
{
	template<typename T> typename GenericValue<T>::ValueIterator begin(GenericValue<T>& mRoot) { return mRoot.Begin(); }
	template<typename T> typename GenericValue<T>::ConstValueIterator begin(const GenericValue<T>& mRoot) { return mRoot.Begin(); }

	template<typename T> typename GenericValue<T>::ValueIterator end(GenericValue<T>& mRoot) { return mRoot.End(); }
	template<typename T> typename GenericValue<T>::ConstValueIterator end(const GenericValue<T>& mRoot) { return mRoot.End(); }

	template<typename T> typename GenericValue<T>::MemberIterator mbegin(GenericValue<T>& mRoot) { return mRoot.MemberBegin(); }
	template<typename T> typename GenericValue<T>::ConstMemberIterator mbegin(const GenericValue<T>& mRoot) { return mRoot.MemberBegin(); }

	template<typename T> typename GenericValue<T>::MemberIterator mend(GenericValue<T>& mRoot) { return mRoot.MemberEnd(); }
	template<typename T> typename GenericValue<T>::ConstMemberIterator mend(const GenericValue<T>& mRoot) { return mRoot.MemberEnd(); }
}

namespace ssvuj
{
	inline static unsigned int size(const Value& mArray) { return mArray.Size(); }
	inline static unsigned int size(const Value& mRoot, const std::string& mValue) { return mRoot[mValue.c_str()].Size(); }

	inline static bool has(const Value& mRoot, const std::string& mValue) { return mRoot.HasMember(mValue.c_str()); }

	template<typename T> inline static void set(Value& mRoot, const std::string& mValue, T mValueToSet) { mRoot[mValue.c_str()] = mValueToSet; }

	template<typename T> inline static T as(const rapidjson::Value& mRoot) { return Internal::AsHelper<T>::as(mRoot); }
	template<typename T> inline static T as(const rapidjson::Value& mRoot, const std::string& mValue) { return as<T>(mRoot[mValue.c_str()]); }
	template<typename T> inline static T as(const rapidjson::Value& mArray, unsigned int mIndex) { return as<T>(mArray[mIndex]); }
	template<typename T> inline static T as(const rapidjson::Value& mRoot, const std::string& mValue, T mDefault) { return mRoot.HasMember(mValue.c_str()) ? as<T>(mRoot, mValue) : mDefault; }
	template<typename T> inline static T as(const rapidjson::Value& mArray, unsigned int mIndex, T mDefault) { return mArray.Size() > mIndex ? as<T>(mArray, mIndex) : mDefault; }

	inline static Value getRootFromString(const std::string& mString)
	{

	}
	inline static Value getRootFromFile(const std::string& mPath)
	{

	}
	inline static void writeRootToString(const Value& mRoot, std::string& mString)
	{

	}
	inline static void writeRootToFile(const Value& mRoot, const std::string& mPath)
	{

	}
}

#endif
