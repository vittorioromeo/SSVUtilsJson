// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILS_BASICCONVERTERS
#define SSVUJ_UTILS_BASICCONVERTERS

#include <vector>
#include <map>
#include <unordered_map>
#include <tuple>
#include "SSVUtilsJson/Global/Common.hpp"

#define SSVUJ_CONVERTER_FRIEND() template<typename> friend struct ssvuj::Converter

#define SSVUJ_CNV_OBJ_AUTO(mValue, mVar) #mVar, mValue.mVar

#define SSVUJ_CNV_SIMPLE(mType, mObjName, mValueName) \
		struct Converter<mType> \
		{ \
			inline static void fromObj(const Obj& mObjName, mType& mValueName)	{ Converter<mType>::template impl<const Obj&, mType&>(mObjName, mValueName); } \
			inline static void toObj(Obj& mObjName, const mType& mValueName)	{ Converter<mType>::template impl<Obj&, const mType&>(mObjName, mValueName); } \
			template<typename TObj, typename TValue> inline static void impl(TObj mObjName, TValue mValueName)

#define SSVUJ_CNV_SIMPLE_END() }

namespace ssvuj
{
	// Convert enums
	template<typename T> struct Converter
	{
		inline static void fromObj(const Obj& mObj, T& mValue, ssvu::EnableIf<ssvu::isEnum<T>()>* = nullptr)
		{
			mValue = T(getExtr<ssvu::Underlying<T>>(mObj));
		}
		inline static void toObj(Obj& mObj, const T& mValue, ssvu::EnableIf<ssvu::isEnum<T>()>* = nullptr)
		{
			arch<ssvu::Underlying<T>>(mObj, ssvu::Underlying<T>(mValue));
		}
	};

	namespace Internal
	{
		template<std::size_t I, typename TTpl> using TplArg = typename std::tuple_element<I, ssvu::RemoveConst<ssvu::RemoveReference<TTpl>>>::type;

		template<std::size_t I = 0, typename... TArgs> inline ssvu::EnableIf<I == sizeof...(TArgs), void> toTpl(const Obj&, std::tuple<TArgs...>&) { }
		template<std::size_t I = 0, typename... TArgs> inline ssvu::EnableIf<I < sizeof...(TArgs), void> toTpl(const Obj& mObj, std::tuple<TArgs...>& mTpl)
		{
			Converter<TplArg<I, decltype(mTpl)>>::fromObj(mObj[Idx(I)], std::get<I>(mTpl)); toTpl<I + 1, TArgs...>(mObj, mTpl);
		}

		template<std::size_t I = 0, typename... TArgs> inline ssvu::EnableIf<I == sizeof...(TArgs), void> fromTpl(Obj&, const std::tuple<TArgs...>&) { }
		template<std::size_t I = 0, typename... TArgs> inline ssvu::EnableIf<I < sizeof...(TArgs), void> fromTpl(Obj& mObj, const std::tuple<TArgs...>& mTpl)
		{
			Converter<TplArg<I, decltype(mTpl)>>::toObj(mObj[Idx(I)], std::get<I>(mTpl)); fromTpl<I + 1, TArgs...>(mObj, mTpl);
		}
	}

	#define SSVUJ_CNV_FUNDAMENTAL(mType) \
		template<> struct Converter<mType> \
		{ \
			using T = mType; \
			inline static void toObj(Obj& mObj, const T& mValue) { mObj = mValue; } \
			inline static void fromObj(const Obj& mObj, T& mValue)

	SSVUJ_CNV_FUNDAMENTAL(Obj)				{ mValue = mObj;				}};
	SSVUJ_CNV_FUNDAMENTAL(char)				{ mValue = T(mObj.asInt());		}};
	SSVUJ_CNV_FUNDAMENTAL(unsigned char)	{ mValue = T(mObj.asInt());		}};
	SSVUJ_CNV_FUNDAMENTAL(int)				{ mValue = mObj.asInt();		}};
	SSVUJ_CNV_FUNDAMENTAL(float)			{ mValue = mObj.asFloat();		}};
	SSVUJ_CNV_FUNDAMENTAL(double)			{ mValue = mObj.asDouble();		}};
	SSVUJ_CNV_FUNDAMENTAL(bool)				{ mValue = mObj.asBool();		}};
	SSVUJ_CNV_FUNDAMENTAL(std::string)		{ mValue = mObj.asString();		}};
	SSVUJ_CNV_FUNDAMENTAL(const char*)		{ mValue = mObj.asCString();	}};

	#undef SSVUJ_CNV_FUNDAMENTAL

	template<> struct Converter<long>
	{
		using T = long;
		inline static void fromObj(const Obj& mObj, T& mValue)	{ mValue = mObj.asLargestInt(); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = Json::Int64(mValue); }
	};
	template<> struct Converter<unsigned int>
	{
		using T = unsigned int;
		inline static void fromObj(const Obj& mObj, T& mValue)	{ mValue = mObj.asUInt(); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = Json::UInt(mValue); }
	};
	template<> struct Converter<unsigned long>
	{
		using T = unsigned long;
		inline static void fromObj(const Obj& mObj, T& mValue)	{ mValue = mObj.asLargestUInt(); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = Json::UInt64(mValue); }
	};
	template<typename TItem> struct Converter<std::vector<TItem>>
	{
		using T = std::vector<TItem>;
		inline static void fromObj(const Obj& mObj, T& mValue)
		{
			const auto& size(getObjSize(mObj)); mValue.resize(size);
			for(auto i(0u); i < size; ++i) extr(mObj, i, mValue[i]);
		}
		inline static void toObj(Obj& mObj, const T& mValue) { for(auto i(0u); i < mValue.size(); ++i) arch(mObj, i, mValue[i]); }
	};
	template<typename TKey, typename TValue, template<typename, typename, typename...> class TMap> struct Converter<TMap<TKey, TValue>>
	{
		using T = TMap<TKey, TValue>;
		inline static void fromObj(const Obj& mObj, T& mValue)
		{
			for(auto& p : mObj)
			{
				const auto& valueKey(getExtr<TKey>(p, 0));
				extr(p, 1, mValue[valueKey]);
			}
		}
		inline static void toObj(Obj& mObj, const T& mValue)
		{
			Idx idx{0};
			for(const auto& p : mValue) arch<std::pair<TKey, TValue>>(getObj(mObj, idx++), p);
		}
	};

	template<typename T1, typename T2> struct Converter<std::pair<T1, T2>>
	{
		using T = std::pair<T1, T2>;
		inline static void fromObj(const Obj& mObj, T& mValue)
		{
			extr<Internal::TplArg<0, T>>(mObj, 0, std::get<0>(mValue));
			extr<Internal::TplArg<1, T>>(mObj, 1, std::get<1>(mValue));
		}
		inline static void toObj(Obj& mObj, const T& mValue)
		{
			arch<Internal::TplArg<0, T>>(mObj, 0, std::get<0>(mValue));
			arch<Internal::TplArg<1, T>>(mObj, 1, std::get<1>(mValue));
		}
	};

	template<typename... TArgs> struct Converter<std::tuple<TArgs...>>
	{
		using T = std::tuple<TArgs...>;
		inline static void fromObj(const Obj& mObj, T& mValue)	{ Internal::toTpl(mObj, mValue); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ Internal::fromTpl(mObj, mValue); }
	};

	template<typename TItem, std::size_t TN> struct Converter<TItem[TN]>
	{
		using T = TItem[TN];
		inline static void fromObj(const Obj& mObj, T& mValue)	{ for(auto i(0u); i < TN; ++i) extr(mObj, i, mValue[i]); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ for(auto i(0u); i < TN; ++i) arch(mObj, i, mValue[i]); }
	};
}

#endif
\
// TODO: docs
