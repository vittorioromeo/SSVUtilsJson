// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILS_DEFAULTCONVERTERS
#define SSVUJ_UTILS_DEFAULTCONVERTERS

#include <vector>
#include <map>
#include <unordered_map>
#include "SSVUtilsJson/Global/Typedefs.h"

namespace ssvuj
{
	namespace Internal
	{
		template<typename T> struct Converter;
		template<typename T> inline static T getFromObj(const Obj& mObj) { T result; Converter<T>::fromObj(result, mObj); return result; }
		template<typename T> inline static Obj getToObj(const T& mValue) { Obj result; Converter<T>::toObj(result, mValue); return result; }

		template<typename T> struct Converter
		{
			inline static void fromObj(T& mValue, const Obj& mObj);
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<Obj>
		{
			using T = Obj;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj; }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<char>
		{
			using T = char;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = static_cast<T>(mObj.asInt()); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<unsigned char>
		{
			using T = unsigned char;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = static_cast<T>(mObj.asInt()); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<int>
		{
			using T = int;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asInt(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<long>
		{
			using T = long;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asLargestInt(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = static_cast<Json::Value::Int64>(mValue); }
		};
		template<> struct Converter<float>
		{
			using T = float;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asFloat(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<double>
		{
			using T = double;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asDouble(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<bool>
		{
			using T = bool;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asBool(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<std::string>
		{
			using T = std::string;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asString(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<const char*>
		{
			using T = const char*;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asCString(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<unsigned int>
		{
			using T = unsigned int;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asUInt(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = static_cast<Json::Value::UInt>(mValue); }
		};
		template<> struct Converter<unsigned long>
		{
			using T = unsigned long;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asLargestUInt(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = static_cast<Json::Value::UInt64>(mValue); }
		};
		template<typename TItem> struct Converter<std::vector<TItem>>
		{
			using T = std::vector<TItem>;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ for(auto i(0u); i < mObj.size(); ++i) mValue.push_back(getFromObj<TItem>(mObj[i])); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ for(auto i(0u); i < mValue.size(); ++i) mObj[i] = getToObj<TItem>(mValue[i]); }
		};
		template<typename TKey, typename TValue> struct Converter<std::map<TKey, TValue>>
		{
			using T = std::map<TKey, TValue>;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ for(auto itr(mObj.begin()); itr != mObj.end(); ++itr) mValue[itr.key().asString()] = getFromObj<TValue>(*itr); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ for(const auto& p : mValue) mObj[ssvu::toStr(p.first)] = getToObj<TValue>(p.second); }
		};
		template<typename TKey, typename TValue> struct Converter<std::unordered_map<TKey, TValue>>
		{
			using T = std::unordered_map<TKey, TValue>;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ for(auto itr(mObj.begin()); itr != mObj.end(); ++itr) mValue[itr.key().asString()] = getFromObj<TValue>(*itr); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ for(const auto& p : mValue) mObj[ssvu::toStr(p.first)] = getToObj<TValue>(p.second); }
		};
	}
}

#endif
