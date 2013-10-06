// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILS_TYPECHECKER
#define SSVUJ_UTILS_TYPECHECKER

#include "SSVUtilsJson/Global/Typedefs.h"

namespace ssvuj
{
	namespace Internal
	{
		template<typename T> struct TypeChecker;
		template<typename T> inline static bool isObjType(const Obj& mObj) { return TypeChecker<T>::isObj(mObj); }

		template<> struct TypeChecker<Obj>				{ inline static bool isObj(const Obj& mObj) { return true; } };
		template<> struct TypeChecker<char> 			{ inline static bool isObj(const Obj& mObj) { return mObj.isInt(); } };
		template<> struct TypeChecker<unsigned char> 	{ inline static bool isObj(const Obj& mObj) { return mObj.isUInt(); } };
		template<> struct TypeChecker<int> 				{ inline static bool isObj(const Obj& mObj) { return mObj.isInt(); } };
		template<> struct TypeChecker<float>			{ inline static bool isObj(const Obj& mObj) { return mObj.isDouble(); } };
		template<> struct TypeChecker<double> 			{ inline static bool isObj(const Obj& mObj) { return mObj.isDouble(); } };
		template<> struct TypeChecker<bool>				{ inline static bool isObj(const Obj& mObj) { return mObj.isBool(); } };
		template<> struct TypeChecker<std::string>		{ inline static bool isObj(const Obj& mObj) { return mObj.isString(); } };
		template<> struct TypeChecker<const char*>		{ inline static bool isObj(const Obj& mObj) { return mObj.isString(); } };
		template<> struct TypeChecker<long>				{ inline static bool isObj(const Obj& mObj) { return mObj.isInt64(); } };
		template<> struct TypeChecker<unsigned int>		{ inline static bool isObj(const Obj& mObj) { return mObj.isUInt(); } };
		template<> struct TypeChecker<unsigned long>	{ inline static bool isObj(const Obj& mObj) { return mObj.isUInt64(); } };
	}
}

#endif
