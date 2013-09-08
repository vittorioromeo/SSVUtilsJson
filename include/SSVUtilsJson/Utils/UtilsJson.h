// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILSJSON
#define SSVUJ_UTILSJSON

#include "SSVUtilsJson/Global/Typedefs.h"
#include "SSVUtilsJson/Utils/DefaultConverters.h"

namespace ssvuj
{
	inline static Obj& get(Obj& mObj, const Key& mKey)				{ return mObj[mKey]; }
	inline static Obj& get(Obj& mArray, Idx mIndex)					{ return mArray[mIndex]; }
	inline static const Obj& get(const Obj& mObj, const Key& mKey)	{ return mObj[mKey]; }
	inline static const Obj& get(const Obj& mArray, Idx mIndex)		{ return mArray[mIndex]; }

	inline static unsigned int size(const Obj& mArray)					{ return mArray.size(); }
	inline static unsigned int size(const Obj& mObj, const Key& mKey)	{ return get(mObj, mKey).size(); }

	inline static bool has(const Obj& mObj, const Key& mKey)	{ return mObj.isMember(mKey); }
	inline static bool has(const Obj& mArray, Idx mIndex)		{ return size(mArray) > mIndex; }

	template<typename T> inline static void set(Obj& mObj, const T& mValue)						{ Internal::Converter<T>::toObj(mObj, mValue); }
	template<typename T> inline static void set(Obj& mObj, const Key& mKey, const T& mValue)	{ set(get(mObj, mKey), mValue); }
	template<typename T> inline static void set(Obj& mArray, Idx mIndex, const T& mValue)		{ set(get(mArray, mIndex), mValue); }


	template<typename T> inline static T as(const Obj& mObj)										{ return Internal::getFromObj<T>(mObj); }
	template<typename T> inline static T as(const Obj& mObj, const Key& mKey)						{ return as<T>(get(mObj, mKey)); }
	template<typename T> inline static T as(const Obj& mArray, Idx mIndex)							{ return as<T>(get(mArray, mIndex)); }
	template<typename T> inline static T as(const Obj& mObj, const Key& mKey, const T& mDefault)	{ return has(mObj, mKey) ? as<T>(mObj, mKey) : mDefault; }
	template<typename T> inline static T as(const Obj& mArray, Idx mIndex, const T& mDefault)		{ return has(mArray, mIndex) ? as<T>(mArray, mIndex) : mDefault; }

	inline static Iterator begin(Obj& mObj) noexcept			{ return mObj.begin(); }
	inline static Iterator end(Obj& mObj) noexcept				{ return mObj.end(); }
	inline static ConstIterator begin(const Obj& mObj) noexcept	{ return mObj.begin(); }
	inline static ConstIterator end(const Obj& mObj) noexcept	{ return mObj.end(); }

	inline static Key getKey(const Iterator& mItr)		{ return as<std::string>(mItr.key()); }
	inline static Key getKey(const ConstIterator& mItr)	{ return as<std::string>(mItr.key()); }
}

#endif

// TODO: isArray or isObj
