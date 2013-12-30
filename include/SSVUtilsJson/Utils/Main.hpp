// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_BASIC
#define SSVUJ_BASIC

#include "SSVUtilsJson/Global/Common.hpp"
#include "SSVUtilsJson/Utils/TypeChecker.hpp"

namespace ssvuj
{
	/// @brief Gets a JSON Obj from another JSON Obj.
	/// @param mObj Source JSON Obj.
	inline Obj& getObj(Obj& mObj) noexcept				{ return mObj; }
	inline const Obj& getObj(const Obj& mObj) noexcept	{ return mObj; }

	/// @brief Gets a JSON Obj from another JSON Obj.
	/// @param mObj Source JSON Obj.
	/// @param mKey Key of the child.
	inline Obj& getObj(Obj& mObj, const Key& mKey) noexcept				{ return mObj[mKey]; }
	inline const Obj& getObj(const Obj& mObj, const Key& mKey) noexcept	{ return mObj[mKey]; }

	/// @brief Gets a JSON Obj from another JSON Obj.
	/// @param mArray Source JSON Obj array.
	/// @param mIdx Index of the child.
	inline Obj& getObj(Obj& mArray, Idx mIdx) noexcept				{ return mArray[mIdx]; }
	inline const Obj& getObj(const Obj& mArray, Idx mIdx) noexcept	{ return mArray[mIdx]; }

	/// @brief Gets the size of a JSON Obj.
	/// @param mObj Target JSON Obj.
	inline std::size_t getObjSize(const Obj& mObj) noexcept { return mObj.size(); }

	/// @brief Gets the size of a JSON Obj.
	/// @param mObj Source Obj.
	/// @param mKey Key of the target child Obj.
	inline std::size_t getObjSize(const Obj& mObj, const Key& mKey) noexcept { return getObjSize(getObj(mObj, mKey)); }

	/// @brief Gets the size of a JSON Obj.
	/// @param mObj Source Obj.
	/// @param mIdx Index of the target child Obj.
	inline std::size_t getObjSize(const Obj& mArray, Idx mIdx) noexcept { return getObjSize(getObj(mArray, mIdx)); }

	/// @brief Checks whether a JSON Obj has a certain member.
	/// @param mObj Obj to check.
	/// @param mKey Key of the child.
	inline bool hasObj(const Obj& mObj, const Key& mKey) noexcept { return mObj.isMember(mKey); }

	/// @brief Checks whether a JSON Obj array has a certain member.
	/// @param mObj Obj to check.
	/// @param mIdx Index of the child.
	inline bool hasObj(const Obj& mArray, Idx mIdx) noexcept { return getObjSize(mArray) > mIdx; }

	/// @brief Checks if a JSON Obj is an array.
	/// @param mObj Obj to check.
	inline bool isObjArray(const Obj& mObj) noexcept { return mObj.isArray(); }

	/// @brief Checks if a JSON Obj is an Obj.
	/// @param mObj Obj to check.
	inline bool isObj(const Obj& mObj) noexcept { return mObj.isObject(); }

	/// @brief Checks the type of a JSON Obj's value.
	/// @param mObj Obj to check.
	template<typename T> inline bool isObjType(const Obj& mObj) noexcept { return Internal::isObjType<T>(mObj); }

	/// @brief Sets a JSON Obj to a certain value.
	/// @param mObj Target Obj.
	/// @param mValue Value to set.
	template<typename T> inline void arch(Obj& mObj, const T& mValue) { Converter<T>::toObj(mObj, mValue); }

	/// @brief Sets a JSON Obj to a certain value.
	/// @param mObj Source Obj.
	/// @param mKey Key of the target child Obj.
	/// @param mValue Value to set.
	template<typename T> inline void arch(Obj& mObj, const Key& mKey, const T& mValue) { arch(getObj(mObj, mKey), mValue); }

	/// @brief Sets a JSON Obj to a certain value.
	/// @param mObj Source Obj array.
	/// @param mIdx Index of the target child Obj.
	/// @param mValue Value to set.
	template<typename T> inline void arch(Obj& mArray, Idx mIdx, const T& mValue) { arch(getObj(mArray, mIdx), mValue); }

	/// @brief Sets a value from a JSON Obj.
	/// @details By default, this does not call the value's constructor.
	/// @param mObj Source Obj.
	/// @param mValue Value to be set.
	template<typename T> inline void extr(const Obj& mObj, T& mValue) { Converter<T>::fromObj(mObj, mValue); }

	/// @brief Sets a value from a JSON Obj.
	/// @details By default, this does not call the value's constructor.
	/// @param mObj Source Obj.
	/// @param mKey Key of the target child Obj.
	/// @param mValue Value to be set.
	template<typename T> inline void extr(const Obj& mObj, const Key& mKey, T& mValue) { extr(getObj(mObj, mKey), mValue); }

	/// @brief Sets a value from a JSON Obj.
	/// @details By default, this does not call the value's constructor.
	/// @param mObj Source Obj array.
	/// @param mIdx Index of the target child Obj.
	/// @param mValue Value to be set.
	template<typename T> inline void extr(const Obj& mArray, Idx mIdx, T& mValue) { extr(getObj(mArray, mIdx), mValue); }

	/// @brief Converts and return an instance of a JSON Obj's value.
	/// @param mObj Obj to convert.
	template<typename T> inline T getExtr(const Obj& mObj) { T result; extr(mObj, result); return result; }

	/// @brief Converts and return an instance of a JSON Obj's value.
	/// @param mObj Parent Obj.
	/// @param mKey Key of the child Obj to convert.
	template<typename T> inline T getExtr(const Obj& mObj, const Key& mKey) { return getExtr<T>(getObj(mObj, mKey)); }

	/// @brief Converts and return an instance of a JSON Obj's value.
	/// @param mObj Parent Obj array.
	/// @param mIdx Index of the child Obj to convert.
	template<typename T> inline T getExtr(const Obj& mArray, Idx mIdx) { return getExtr<T>(getObj(mArray, mIdx)); }

	/// @brief Converts and return an instance of a JSON Obj's value.
	/// @param mObj Parent Obj.
	/// @param mKey Key of the child Obj to convert.
	/// @param mDefault Default value to use, in case the Obj hasn't got the desired value.
	template<typename T> inline T getExtr(const Obj& mObj, const Key& mKey, const T& mDefault) { return hasObj(mObj, mKey) ? getExtr<T>(mObj, mKey) : mDefault; }

	/// @brief Converts and return an instance of a JSON Obj's value.
	/// @param mObj Parent Obj array.
	/// @param mIdx Index of the child Obj to convert.
	/// @param mDefault Default value to use, in case the Obj hasn't got the desired value.
	template<typename T> inline T getExtr(const Obj& mArray, Idx mIdx, const T& mDefault) { return hasObj(mArray, mIdx) ? getExtr<T>(mArray, mIdx) : mDefault; }

	// TODO: docs
	template<typename T> inline Obj getArch(const T& mValue)	{ Obj result; arch(result, mValue); return result; }
	inline Key getKey(const Iterator& mItr) noexcept			{ return getExtr<Key>(mItr.key()); }
	inline Key getKey(const ConstIterator& mItr) noexcept		{ return getExtr<Key>(mItr.key()); }

	// Iterator support
	inline Iterator begin(Obj& mObj) noexcept				{ return mObj.begin(); }
	inline Iterator end(Obj& mObj) noexcept					{ return mObj.end(); }
	inline ConstIterator begin(const Obj& mObj) noexcept	{ return mObj.begin(); }
	inline ConstIterator end(const Obj& mObj) noexcept		{ return mObj.end(); }

	namespace Internal
	{
		template<Idx TIdx, typename TArg> inline void extrArrayHelper(const Obj& mArray, TArg& mArg) { extr(mArray, TIdx, mArg); }
		template<Idx TIdx, typename TArg, typename... TArgs> inline void extrArrayHelper(const Obj& mArray, TArg& mArg, TArgs&... mArgs)
		{
			extrArrayHelper<TIdx>(mArray, mArg); extrArrayHelper<TIdx + 1>(mArray, std::forward<TArgs&>(mArgs)...);
		}

		template<Idx TIdx, typename TArg> inline void archArrayHelper(Obj& mArray, const TArg& mArg) { arch(mArray, TIdx, mArg); }
		template<Idx TIdx, typename TArg, typename... TArgs> inline void archArrayHelper(Obj& mArray, const TArg& mArg, const TArgs&... mArgs)
		{
			archArrayHelper<TIdx>(mArray, mArg); archArrayHelper<TIdx + 1>(mArray, std::forward<const TArgs&>(mArgs)...);
		}

		template<typename TArg> inline void extrObjHelper(const Obj& mObj, const Key& mKey, TArg& mArg) { extr(mObj, mKey, mArg); }
		template<typename TArg, typename... TArgs> inline void extrObjHelper(const Obj& mObj, const Key& mKey, TArg& mArg, TArgs&... mArgs)
		{
			extrObjHelper(mObj, mKey, mArg); extrObjHelper(mObj, std::forward<TArgs&>(mArgs)...);
		}

		template<typename TArg> inline void archObjHelper(Obj& mObj, const Key& mKey, const TArg& mArg) { arch(mObj, mKey, mArg); }
		template<typename TArg, typename... TArgs> inline void archObjHelper(Obj& mObj, const Key& mKey, TArg&& mArg, const TArgs&... mArgs)
		{
			archObjHelper(mObj, mKey, mArg); archObjHelper(mObj, std::forward<const TArgs&>(mArgs)...);
		}
	}

	// extrArray and archArray serialize some values to a json array
	template<typename... TArgs> inline void extrArray(const Obj& mArray, TArgs&... mArgs)	{ Internal::extrArrayHelper<0>(mArray, std::forward<TArgs&>(mArgs)...); }
	template<typename... TArgs> inline void archArray(Obj& mArray, const TArgs&... mArgs)	{ Internal::archArrayHelper<0>(mArray, std::forward<const TArgs&>(mArgs)...); }
	template<typename... TArgs> inline Obj getArchArray(const TArgs&... mArgs)				{ Obj result; archArray(result, std::forward<const TArgs&>(mArgs)...); return result; }

	// extrObj and archObj serialize some keys/values to an obj
	template<typename... TArgs> inline void extrObj(const Obj& mObj, TArgs&... mArgs)	{ Internal::extrObjHelper(mObj, std::forward<TArgs&>(mArgs)...); }
	template<typename... TArgs> inline void archObj(Obj& mObj, const TArgs&... mArgs)	{ Internal::archObjHelper(mObj, std::forward<const TArgs&>(mArgs)...); }
	template<typename... TArgs> inline Obj getArchObj(const TArgs&... mArgs)			{ Obj result; archObj(result, std::forward<const TArgs&>(mArgs)...); return result; }

	// Dispatchers
	template<typename T> inline void convert(const Obj& mObj, T& mValue)	{ extr(mObj, mValue); }
	template<typename T> inline void convert(Obj& mObj, const T& mValue)	{ arch(mObj, mValue); }

	template<typename... TArgs> inline void convertArray(const Obj& mObj, TArgs&... mArgs)	{ extrArray(mObj, std::forward<TArgs&>(mArgs)...); }
	template<typename... TArgs> inline void convertArray(Obj& mObj, const TArgs&... mArgs)	{ archArray(mObj, std::forward<const TArgs&>(mArgs)...); }

	template<typename... TArgs> inline void convertObj(const Obj& mObj, TArgs&... mArgs)	{ extrObj(mObj, std::forward<TArgs&>(mArgs)...); }
	template<typename... TArgs> inline void convertObj(Obj& mObj, const TArgs&... mArgs)	{ archObj(mObj, std::forward<const TArgs&>(mArgs)...); }
}

#endif
