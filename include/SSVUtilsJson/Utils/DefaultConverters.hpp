// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILS_DEFAULTCONVERTERS
#define SSVUJ_UTILS_DEFAULTCONVERTERS

#include <vector>
#include <map>
#include <unordered_map>
#include <tuple>
#include "SSVUtilsJson/Global/Typedefs.hpp"

namespace ssvuj
{
	template<typename T> struct Converter
	{
		inline static void fromObj(T& mValue, const Obj& mObj);
		inline static void toObj(Obj& mObj, const T& mValue) { mObj = mValue; }
	};

	namespace Internal
	{
		template<typename T> inline T getFromObj(const Obj& mObj) { T result; Converter<T>::fromObj(result, mObj); return result; }
		template<typename T> inline Obj getToObj(const T& mValue) { Obj result; Converter<T>::toObj(result, mValue); return result; }
		template<typename T> struct CDefaultToObj { inline static void toObj(Obj& mObj, const T& mValue) { mObj = mValue; } };
	}

	#define SSVUJ_DEFINE_DTO_CONVERTER(mType) template<> struct Converter<mType> : Internal::CDefaultToObj<mType>

	SSVUJ_DEFINE_DTO_CONVERTER(Obj)				{ using T = Obj;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj; } };
	SSVUJ_DEFINE_DTO_CONVERTER(char)			{ using T = char;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = static_cast<T>(mObj.asInt()); } };
	SSVUJ_DEFINE_DTO_CONVERTER(unsigned char)	{ using T = unsigned char;	inline static void fromObj(T& mValue, const Obj& mObj) { mValue = static_cast<T>(mObj.asInt()); } };
	SSVUJ_DEFINE_DTO_CONVERTER(int)				{ using T = int;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asInt(); } };
	SSVUJ_DEFINE_DTO_CONVERTER(float)			{ using T = float;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asFloat(); } };
	SSVUJ_DEFINE_DTO_CONVERTER(double)			{ using T = double;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asDouble(); } };
	SSVUJ_DEFINE_DTO_CONVERTER(bool)			{ using T = bool;			inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asBool(); } };
	SSVUJ_DEFINE_DTO_CONVERTER(std::string)		{ using T = std::string;	inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asString(); } };
	SSVUJ_DEFINE_DTO_CONVERTER(const char*)		{ using T = const char*;	inline static void fromObj(T& mValue, const Obj& mObj) { mValue = mObj.asCString(); } };

	#undef SSVUJ_DEFINE_DTO_CONVERTER

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

	namespace Internal
	{
		template<std::size_t I = 0, typename... TArgs> inline ssvu::EnableIf<I == sizeof...(TArgs), void> setTpl(std::tuple<TArgs...>&, const Obj&) { }
		template<std::size_t I = 0, typename... TArgs> inline ssvu::EnableIf<I < sizeof...(TArgs), void> setTpl(std::tuple<TArgs...>& mTpl, const Obj& mObj)
		{
			std::get<I>(mTpl) = Internal::getFromObj<typename std::tuple_element<I, ssvu::RemoveReference<decltype(mTpl)>>::type>(mObj[Idx(I)]);
			setTpl<I + 1, TArgs...>(mTpl, mObj);
		}

		template<std::size_t I = 0, typename... TArgs> inline ssvu::EnableIf<I == sizeof...(TArgs), void> getFromTpl(Obj&, const std::tuple<TArgs...>&) { }
		template<std::size_t I = 0, typename... TArgs> inline ssvu::EnableIf<I < sizeof...(TArgs), void> getFromTpl(Obj& mObj, const std::tuple<TArgs...>& mTpl)
		{
			mObj[Idx(I)] = Internal::getToObj<ssvu::RemoveConst<typename std::tuple_element<I, ssvu::RemoveReference<decltype(mTpl)>>::type>>(std::get<I>(mTpl));
			getFromTpl<I + 1, TArgs...>(mObj, mTpl);
		}
	}

	template<typename... TArgs> struct Converter<std::tuple<TArgs...>>
	{
		using T = std::tuple<TArgs...>;
		inline static void fromObj(T& mValue, const Obj& mObj)	{ Internal::setTpl(mValue, mObj); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ Internal::getFromTpl(mObj, mValue); }
	};
}

#endif

// TODO: friendship? docs
