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
	template<typename T> struct Converter;
	namespace Internal
	{
		template<typename T> inline static T getFromObj(const Obj& mObj) { T result; Converter<T>::fromObj(result, mObj); return result; }
		template<typename T> inline static Obj getToObj(const T& mValue) { Obj result; Converter<T>::toObj(result, mValue); return result; }
		template<typename T> struct CDefaultToObj { inline static void toObj(Obj& mObj, const T& mValue) { mObj = mValue; } };
	}

	template<typename T> struct Converter
	{
		inline static void fromObj(T& mValue, const Obj& mObj);
		inline static void toObj(Obj& mObj, const T& mValue) { mObj = mValue; }
	};

	template<> struct Converter<Obj> : Internal::CDefaultToObj<Obj>						{ using T = Obj;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj; } };
	template<> struct Converter<char> :Internal:: CDefaultToObj<char>					{ using T = char;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = static_cast<T>(mObj.asInt()); } };
	template<> struct Converter<unsigned char> : Internal::CDefaultToObj<unsigned char>	{ using T = unsigned char;	inline static void fromObj(T& mValue, const Obj& mObj) { mValue = static_cast<T>(mObj.asInt()); } };
	template<> struct Converter<int> : Internal::CDefaultToObj<int>						{ using T = int;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asInt(); } };
	template<> struct Converter<float> : Internal::CDefaultToObj<float>					{ using T = float;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asFloat(); } };
	template<> struct Converter<double> : Internal::CDefaultToObj<double>				{ using T = double;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asDouble(); } };
	template<> struct Converter<bool> : Internal::CDefaultToObj<bool>					{ using T = bool;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asBool(); } };
	template<> struct Converter<std::string> : Internal::CDefaultToObj<std::string>		{ using T = std::string;	inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asString(); } };
	template<> struct Converter<const char*> : Internal::CDefaultToObj<const char*>		{ using T = const char*;	inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asCString(); } };

	template<> struct Converter<long>
	{
		using T = long;
		inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asLargestInt(); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = static_cast<Json::Int64>(mValue); }
	};
	template<> struct Converter<unsigned int>
	{
		using T = unsigned int;
		inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asUInt(); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = static_cast<Json::UInt>(mValue); }
	};
	template<> struct Converter<unsigned long>
	{
		using T = unsigned long;
		inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asLargestUInt(); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = static_cast<Json::UInt64>(mValue); }
	};
	template<typename TItem> struct Converter<std::vector<TItem>>
	{
		using T = std::vector<TItem>;
		inline static void fromObj(T& mValue, const Obj& mObj)	{ for(auto i(0u); i < mObj.size(); ++i) mValue.push_back(Internal::getFromObj<TItem>(mObj[i])); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ for(auto i(0u); i < mValue.size(); ++i) mObj[i] = Internal::getToObj<TItem>(mValue[i]); }
	};
	template<typename TKey, typename TValue, template<typename, typename, typename...> class TMap> struct Converter<TMap<TKey, TValue>>
	{
		using T = TMap<TKey, TValue>;
		inline static void fromObj(T& mValue, const Obj& mObj)
		{
			for(auto itr(mObj.begin()); itr != mObj.end(); ++itr)
				mValue[Internal::getFromObj<TKey>((*itr)[0])] = Internal::getFromObj<TValue>((*itr)[1]);
		}
		inline static void toObj(Obj& mObj, const T& mValue)
		{
			unsigned int idx{0};
			for(const auto& p : mValue)
			{
				mObj[idx][0] = Internal::getToObj<TKey>(p.first);
				mObj[idx][1] = Internal::getToObj<TValue>(p.second);
				++idx;
			}
		}
	};
	template<typename T1, typename T2> struct Converter<std::pair<T1, T2>>
	{
		using T = std::pair<T1, T2>;
		inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue.first = Internal::getFromObj<T1>(mObj[0]); mValue.second = Internal::getFromObj<T2>(mObj[1]); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ mObj[0] = Internal::getToObj<T1>(mValue.first); mObj[1] = Internal::getToObj<T2>(mValue.second); }
	};
}

#endif

// TODO: tuples? friendship? macros? docs
