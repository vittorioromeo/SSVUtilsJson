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
			inline static void toObj(Obj& mObj, const T& mValue) { mObj = mValue; }
		};
		template<typename T> struct CDefaultToObj { inline static void toObj(Obj& mObj, const T& mValue) { mObj = mValue; } };

		template<> struct Converter<Obj> : CDefaultToObj<Obj>						{ using T = Obj;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj; } };
		template<> struct Converter<char> : CDefaultToObj<char>						{ using T = char;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = static_cast<T>(mObj.asInt()); } };
		template<> struct Converter<unsigned char> : CDefaultToObj<unsigned char>	{ using T = unsigned char;	inline static void fromObj(T& mValue, const Obj& mObj) { mValue = static_cast<T>(mObj.asInt()); } };
		template<> struct Converter<int> : CDefaultToObj<int>						{ using T = int;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asInt(); } };
		template<> struct Converter<float> : CDefaultToObj<float>					{ using T = float;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asFloat(); } };
		template<> struct Converter<double> : CDefaultToObj<double>					{ using T = double;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asDouble(); } };
		template<> struct Converter<bool> : CDefaultToObj<bool>						{ using T = bool;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asBool(); } };
		template<> struct Converter<std::string> : CDefaultToObj<std::string>		{ using T = std::string;	inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asString(); } };
		template<> struct Converter<const char*> : CDefaultToObj<const char*>		{ using T = const char*;	inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asCString(); } };

		template<> struct Converter<long>
		{
			using T = long;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asLargestInt(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = static_cast<Json::Value::Int64>(mValue); }
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
		template<typename TKey, typename TValue, template<typename, typename, typename...> class TMap> struct Converter<TMap<TKey, TValue>>
		{
			using T = TMap<TKey, TValue>;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ for(auto itr(mObj.begin()); itr != mObj.end(); ++itr) mValue[itr.key().asString()] = getFromObj<TValue>(*itr); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ for(const auto& p : mValue) mObj[ssvu::toStr(p.first)] = getToObj<TValue>(p.second); }
		};
	}
}

#endif
