// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILSJSON
#define SSVUJ_UTILSJSON

#include <vector>
#include <fstream>
#include <sstream>
#include <SSVUtils/SSVUtils.h>
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
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<Obj>
		{
			using T = Obj;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj; }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<int>
		{
			using T = int;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asInt(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<long>
		{
			using T = long;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asLargestInt(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = static_cast<Json::Value::Int64>(mValue); }
		};
		template<> struct Converter<float>
		{
			using T = float;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asFloat(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<double>
		{
			using T = double;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asDouble(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<bool>
		{
			using T = bool;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asBool(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<std::string>
		{
			using T = std::string;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asString(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<const char*>
		{
			using T = const char*;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = mObj.asCString(); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
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

		inline static void logReadError(const Reader& mReader, const std::string& mFrom)
		{
			ssvu::lo << ssvu::lt("ssvuj::logReadError") << mReader.getFormatedErrorMessages() << std::endl << "From: [" << mFrom << "]" << std::endl;
		}
		inline static bool tryParse(Obj& mObj, Reader& mReader, const std::string& mSrc)
		{
			if(mReader.parse(mSrc, mObj, false)) return true;
			logReadError(mReader, mSrc); return false;
		}
	}

	inline static unsigned int size(const Obj& mArray)					{ return mArray.size(); }
	inline static unsigned int size(const Obj& mObj, const Key& mKey)	{ return mObj[mKey].size(); }

	inline static bool has(const Obj& mObj, const Key& mKey) { return mObj.isMember(mKey); }
	inline static bool hasIndex(const Obj& mObj, Idx mIndex) { return size(mObj) > mIndex; }

	template<typename T> inline static void set(Obj& mObj, const T& mValue)						{ Internal::Converter<T>::toObj(mObj, mValue); }
	template<typename T> inline static void set(Obj& mObj, const Key& mKey, const T& mValue)	{ set(mObj[mKey], mValue); }
	template<typename T> inline static void set(Obj& mObj, Idx mIndex, const T& mValue)			{ set(mObj[mIndex], mValue); }

	template<typename T> inline static T as(const Obj& mObj)										{ return Internal::getFromObj<T>(mObj); }
	template<typename T> inline static T as(const Obj& mObj, const Key& mKey)						{ return as<T>(mObj[mKey]); }
	template<typename T> inline static T as(const Obj& mObj, Idx mIndex)							{ return as<T>(mObj[mIndex]); }
	template<typename T> inline static T as(const Obj& mObj, const Key& mKey, const T& mDefault)	{ return has(mObj, mKey) ? as<T>(mObj, mKey) : mDefault; }
	template<typename T> inline static T as(const Obj& mObj, Idx mIndex, const T& mDefault)			{ return hasIndex(mObj, mIndex) ? as<T>(mObj, mIndex) : mDefault; }

	inline static Obj readFromString(const std::string& mString)						{ Obj result; Reader reader; Internal::tryParse(result, reader, mString); return result; }
	inline static Obj readFromFile(const ssvu::FileSystem::Path& mPath)					{ Obj result; Reader reader; Internal::tryParse(result, reader, ssvu::FileSystem::getFileContents(mPath)); return result; }

	template<typename T> inline static void writeToStream(const Obj& mObj, T& mStream)		{ Writer writer; writer.write(mStream, mObj); mStream.flush(); }
	inline static void writeToString(const Obj& mObj, std::string& mString)					{ std::ostringstream o; writeToStream(mObj, o); mString = o.str(); }
	inline static void writeToFile(const Obj& mObj, const ssvu::FileSystem::Path& mPath)	{ std::ofstream o{mPath}; writeToStream(mObj, o); o.close(); }
	inline static std::string getWriteToString(const Obj& mObj)								{ std::string result; writeToString(mObj, result); return result; }
}

#endif
