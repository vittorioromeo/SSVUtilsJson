// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILSJSON
#define SSVUJ_UTILSJSON

#include "SSVUtilsJson/Global/Typedefs.hpp"
#include "SSVUtilsJson/Utils/DefaultConverters.hpp"
#include "SSVUtilsJson/Utils/TypeChecker.hpp"

namespace ssvuj
{
	/// @brief Gets a JSON Obj from another JSON Obj.
	/// @param mObj Source JSON Obj.
	inline Obj& get(Obj& mObj) noexcept				{ return mObj; }
	inline const Obj& get(const Obj& mObj) noexcept	{ return mObj; }

	/// @brief Gets a JSON Obj from another JSON Obj.
	/// @param mObj Source JSON Obj.
	/// @param mKey Key of the child.
	inline Obj& get(Obj& mObj, const Key& mKey) noexcept				{ return mObj[mKey]; }
	inline const Obj& get(const Obj& mObj, const Key& mKey) noexcept	{ return mObj[mKey]; }

	/// @brief Gets a JSON Obj from another JSON Obj.
	/// @param mArray Source JSON Obj array.
	/// @param mIdx Index of the child.
	inline Obj& get(Obj& mArray, Idx mIdx) noexcept				{ return mArray[mIdx]; }
	inline const Obj& get(const Obj& mArray, Idx mIdx) noexcept	{ return mArray[mIdx]; }

	/// @brief Gets the size of a JSON Obj.
	/// @param mObj Source JSON Obj array.
	inline std::size_t size(const Obj& mArray) noexcept { return mArray.size(); }

	/// @brief Gets the size of a JSON Obj.
	/// @param mObj Source JSON Obj.
	/// @param mKey Key of the child Obj.
	inline std::size_t size(const Obj& mObj, const Key& mKey) noexcept { return get(mObj, mKey).size(); }

	/// @brief Checks whether a JSON Obj has a certain member.
	/// @param mObj Obj to check.
	/// @param mKey Key of the child.
	inline bool has(const Obj& mObj, const Key& mKey) noexcept { return mObj.isMember(mKey); }

	/// @brief Checks whether a JSON Obj array has a certain member.
	/// @param mObj Obj to check.
	/// @param mIdx Index of the child.
	inline bool has(const Obj& mArray, Idx mIdx) noexcept { return size(mArray) > mIdx; }

	/// @brief Sets a JSON Obj to a certain value.
	/// @param mObj Target Obj.
	/// @param mValue Value to set.
	template<typename T> inline void set(Obj& mObj, const T& mValue) { Converter<T>::toObj(mObj, mValue); }

	/// @brief Sets a JSON Obj to a certain value.
	/// @param mObj Source Obj.
	/// @param mKey Key of the target child Obj.
	/// @param mValue Value to set.
	template<typename T> inline void set(Obj& mObj, const Key& mKey, const T& mValue) { set(get(mObj, mKey), mValue); }

	/// @brief Sets a JSON Obj to a certain value.
	/// @param mObj Source Obj array.
	/// @param mIdx Index of the target child Obj.
	/// @param mValue Value to set.
	template<typename T> inline void set(Obj& mArray, Idx mIdx, const T& mValue) { set(get(mArray, mIdx), mValue); }

	/// @brief Checks the type of a JSON Obj's value.
	/// @param mObj Obj to check.
	template<typename T> inline bool is(const Obj& mObj) noexcept { return Internal::isObjType<T>(mObj); }

	/// @brief Converts and return an instance of a JSON Obj's value.
	/// @param mObj Obj to convert.
	template<typename T> inline T getAs(const Obj& mObj) { return Internal::getFromObj<T>(mObj); }

	/// @brief Converts and return an instance of a JSON Obj's value.
	/// @param mObj Parent Obj.
	/// @param mKey Key of the child Obj to convert.
	template<typename T> inline T getAs(const Obj& mObj, const Key& mKey) { return getAs<T>(get(mObj, mKey)); }

	/// @brief Converts and return an instance of a JSON Obj's value.
	/// @param mObj Parent Obj array.
	/// @param mIdx Index of the child Obj to convert.
	template<typename T> inline T getAs(const Obj& mArray, Idx mIdx) { return getAs<T>(get(mArray, mIdx)); }

	/// @brief Converts and return an instance of a JSON Obj's value.
	/// @param mObj Parent Obj.
	/// @param mKey Key of the child Obj to convert.
	/// @param mDefault Default value to use, in case the Obj hasn't got the desired value.
	template<typename T> inline T getAs(const Obj& mObj, const Key& mKey, const T& mDefault) { return has(mObj, mKey) ? getAs<T>(mObj, mKey) : mDefault; }

	/// @brief Converts and return an instance of a JSON Obj's value.
	/// @param mObj Parent Obj array.
	/// @param mIdx Index of the child Obj to convert.
	/// @param mDefault Default value to use, in case the Obj hasn't got the desired value.
	template<typename T> inline T getAs(const Obj& mArray, Idx mIdx, const T& mDefault) { return has(mArray, mIdx) ? getAs<T>(mArray, mIdx) : mDefault; }

	/// @brief Checks if a JSON Obj is an array.
	/// @param mObj Obj to check.
	inline bool isArray(const Obj& mObj) noexcept { return mObj.isArray(); }

	/// @brief Checks if a JSON Obj is an Obj.
	/// @param mObj Obj to check.
	inline bool isObj(const Obj& mObj) noexcept { return mObj.isObject(); }

	// Iterator support
	inline Iterator begin(Obj& mObj) noexcept				{ return mObj.begin(); }
	inline Iterator end(Obj& mObj) noexcept					{ return mObj.end(); }
	inline ConstIterator begin(const Obj& mObj) noexcept	{ return mObj.begin(); }
	inline ConstIterator end(const Obj& mObj) noexcept		{ return mObj.end(); }
	inline Key getKey(const Iterator& mItr) noexcept		{ return getAs<Key>(mItr.key()); }
	inline Key getKey(const ConstIterator& mItr) noexcept	{ return getAs<Key>(mItr.key()); }
}

#endif
