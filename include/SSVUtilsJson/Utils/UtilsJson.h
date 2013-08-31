// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILSJSON
#define SSVUJ_UTILSJSON

#include "SSVUtilsJson/Global/Typedefs.h"
#include "SSVUtilsJson/Utils/DefaultConverters.h"

namespace ssvuj
{
	inline static unsigned int size(const Obj& mArray)					{ return mArray.size(); }
	inline static unsigned int size(const Obj& mObj, const Key& mKey)	{ return mObj[mKey].size(); }

	inline static bool has(const Obj& mObj, const Key& mKey)	{ return mObj.isMember(mKey); }
	inline static bool has(const Obj& mObj, Idx mIndex)			{ return size(mObj) > mIndex; }

	template<typename T> inline static void set(Obj& mObj, const T& mValue)						{ Internal::Converter<T>::toObj(mObj, mValue); }
	template<typename T> inline static void set(Obj& mObj, const Key& mKey, const T& mValue)	{ set(mObj[mKey], mValue); }
	template<typename T> inline static void set(Obj& mObj, Idx mIndex, const T& mValue)			{ set(mObj[mIndex], mValue); }

	template<typename T> inline static T as(const Obj& mObj)										{ return Internal::getFromObj<T>(mObj); }
	template<typename T> inline static T as(const Obj& mObj, const Key& mKey)						{ return as<T>(mObj[mKey]); }
	template<typename T> inline static T as(const Obj& mArray, Idx mIndex)							{ return as<T>(mArray[mIndex]); }
	template<typename T> inline static T as(const Obj& mObj, const Key& mKey, const T& mDefault)	{ return has(mObj, mKey) ? as<T>(mObj, mKey) : mDefault; }
	template<typename T> inline static T as(const Obj& mArray, Idx mIndex, const T& mDefault)		{ return has(mArray, mIndex) ? as<T>(mArray, mIndex) : mDefault; }
}

#endif

// TODO: non-member start/begin for ssvuj::Obj; key getting util; isArray or isObj
