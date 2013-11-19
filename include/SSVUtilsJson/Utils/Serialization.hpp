// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILS_SERIALIZATION
#define SSVUJ_UTILS_SERIALIZATION

#include "SSVUtilsJson/Global/Typedefs.hpp"
#include "SSVUtilsJson/Utils/DefaultConverters.hpp"
#include "SSVUtilsJson/Utils/UtilsJson.hpp"

namespace ssvuj
{
	namespace Internal
	{
		template<Idx TIdx, typename TArg> inline void extrArrayHelper(const Obj& mArray, TArg& mArg) { mArg = as<TArg>(mArray, TIdx); }
		template<Idx TIdx, typename TArg, typename... TArgs> inline void extrArrayHelper(const Obj& mArray, TArg& mArg, TArgs&... mArgs)
		{
			extrArrayHelper<TIdx>(mArray, mArg); extrArrayHelper<TIdx + 1>(mArray, std::forward<TArgs&>(mArgs)...);
		}

		template<Idx TIdx, typename TArg> inline void archArrayHelper(Obj& mArray, const TArg& mArg) { set(mArray, TIdx, mArg); }
		template<Idx TIdx, typename TArg, typename... TArgs> inline void archArrayHelper(Obj& mArray, const TArg& mArg, const TArgs&... mArgs)
		{
			archArrayHelper<TIdx>(mArray, mArg); archArrayHelper<TIdx + 1>(mArray, std::forward<const TArgs&>(mArgs)...);
		}

		template<typename TArg> inline void extrObjHelper(const Obj& mObj, const Key& mKey, TArg& mArg) { mArg = as<TArg>(mObj, mKey); }
		template<typename TArg, typename... TArgs> inline void extrObjHelper(const Obj& mObj, const Key& mKey, TArg& mArg, TArgs&... mArgs)
		{
			extrObjHelper(mObj, mKey, mArg); extrObjHelper(mObj, std::forward<TArgs&>(mArgs)...);
		}

		template<typename TArg> inline void archObjHelper(Obj& mObj, const Key& mKey, const TArg& mArg) { set(mObj, mKey, mArg); }
		template<typename TArg, typename... TArgs> inline void archObjHelper(Obj& mObj, const Key& mKey, TArg&& mArg, const TArgs&... mArgs)
		{
			archObjHelper(mObj, mKey, mArg); archObjHelper(mObj, std::forward<const TArgs&>(mArgs)...);
		}
	}

	// extr and arch serialize a value to a single obj
	template<typename T> inline void extr(const Obj& mObj, T& mValue)	{ mValue = as<T>(mObj); }
	template<typename T> inline void arch(Obj& mObj, const T& mValue)	{ set<T>(mObj, mValue); }
	template<typename TEnum, typename TUnderlying> inline void extrEnum(const Obj& mObj, TEnum& mValue)	{ mValue = TEnum(as<TUnderlying>(mObj)); }
	template<typename TEnum, typename TUnderlying> inline void archEnum(Obj& mObj, const TEnum& mValue)	{ set<TUnderlying>(mObj, TUnderlying(mValue)); }
	template<typename T> inline T getExtr(const Obj& mObj)				{ T result; extr(mObj, result); return result; }
	template<typename T> inline Obj getArch(const T& mValue)			{ Obj result; arch(result, mValue); return result; }

	// extrArray and archArray serialize some values to a json array
	template<typename... TArgs> inline void extrArray(const Obj& mArray, TArgs&... mArgs)	{ Internal::extrArrayHelper<0>(mArray, std::forward<TArgs&>(mArgs)...); }
	template<typename... TArgs> inline void archArray(Obj& mArray, const TArgs&... mArgs)	{ Internal::archArrayHelper<0>(mArray, std::forward<const TArgs&>(mArgs)...); }
	template<typename... TArgs> inline Obj getArchArray(const TArgs&... mArgs)				{ Obj result; archArray(result, std::forward<const TArgs&>(mArgs)...); return result; }

	// extrObj and archObj serialize some keys/values to an obj
	template<typename... TArgs> inline void extrObj(const Obj& mObj, TArgs&... mArgs)	{ Internal::extrObjHelper(mObj, std::forward<TArgs&>(mArgs)...); }
	template<typename... TArgs> inline void archObj(Obj& mObj, const TArgs&... mArgs)	{ Internal::archObjHelper(mObj, std::forward<const TArgs&>(mArgs)...); }
	template<typename... TArgs> inline Obj getArchObj(const TArgs&... mArgs)			{ Obj result; archObj(result, std::forward<const TArgs&>(mArgs)...); return result; }
}

#endif