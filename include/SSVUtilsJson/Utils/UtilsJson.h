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
		template<typename T> struct FromJson		{ inline static T conv(const Obj& mObj); };
		template<> struct FromJson<Obj>				{ inline static Obj conv(const Obj& mObj)			{ return mObj; } };
		template<> struct FromJson<int>				{ inline static int conv(const Obj& mObj)			{ return mObj.asInt(); } };
		template<> struct FromJson<long>			{ inline static long conv(const Obj& mObj)			{ return mObj.asLargestInt(); } };
		template<> struct FromJson<float>			{ inline static float conv(const Obj& mObj)			{ return mObj.asFloat(); } };
		template<> struct FromJson<double>			{ inline static double conv(const Obj& mObj)		{ return mObj.asDouble(); } };
		template<> struct FromJson<bool>			{ inline static bool conv(const Obj& mObj)			{ return mObj.asBool(); } };
		template<> struct FromJson<std::string>		{ inline static std::string conv(const Obj& mObj)	{ return mObj.asString(); } };
		template<> struct FromJson<char const*>		{ inline static char const* conv(const Obj& mObj)	{ return mObj.asCString(); } };
		template<> struct FromJson<unsigned int>	{ inline static unsigned int conv(const Obj& mObj)	{ return mObj.asUInt(); } };
		template<> struct FromJson<unsigned long>	{ inline static unsigned long conv(const Obj& mObj)	{ return mObj.asLargestUInt(); } };
		template<typename T> struct FromJson<std::vector<T>>
		{
			inline static std::vector<T> conv(const Obj& mObj)
			{
				std::vector<T> result;
				for(auto i(0u); i < mObj.size(); ++i) result.push_back(FromJson<T>::conv(mObj[i]));
				return result;
			}
		};

		template<typename T> struct ToJson			{ inline static Obj conv(const T& mValue) { return mValue; } };
		template<typename T> struct ToJson<std::vector<T>>
		{
			inline static Obj conv(const std::vector<T>& mValue)
			{
				Obj result;
				for(auto i(0u); i < mValue.size(); ++i) result[i] = ToJson<T>::conv(mValue[i]);
				return result;
			}
		};

		inline static void logReadError(const Reader& mReader, const std::string& mFrom)
		{
			ssvu::lo << ssvu::lt("ssvuj::logReadError") << mReader.getFormatedErrorMessages() << std::endl << "From: [" << mFrom << "]" << std::endl;
		}

		inline static bool tryParse(Obj& mObj, Reader& mReader, const std::string& mSrc)
		{
			if(mReader.parse(mSrc, mObj, false)) return true;
			logReadError(mReader, mSrc);
			return false;
		}
	}

	inline static unsigned int size(const Obj& mArray)					{ return mArray.size(); }
	inline static unsigned int size(const Obj& mObj, const Key& mKey)	{ return mObj[mKey].size(); }

	inline static bool has(const Obj& mObj, const Key& mKey) { return mObj.isMember(mKey); }
	inline static bool hasIndex(const Obj& mObj, Idx mIndex) { return size(mObj) > mIndex; }

	template<typename T> inline static void set(Obj& mObj, const T& mValue)						{ mObj = Internal::ToJson<T>::conv(mValue); }
	template<typename T> inline static void set(Obj& mObj, const Key& mKey, const T& mValue)	{ set(mObj[mKey], mValue); }
	template<typename T> inline static void set(Obj& mObj, Idx mIndex, const T& mValue)			{ set(mObj[mIndex], mValue); }

	template<typename T> inline static T as(const Obj& mObj)										{ return Internal::FromJson<T>::conv(mObj); }
	template<typename T> inline static T as(const Obj& mObj, const Key& mKey)						{ return as<T>(mObj[mKey]); }
	template<typename T> inline static T as(const Obj& mObj, Idx mIndex)							{ return as<T>(mObj[mIndex]); }
	template<typename T> inline static T as(const Obj& mObj, const Key& mKey, const T& mDefault)	{ return has(mObj, mKey) ? as<T>(mObj, mKey) : mDefault; }
	template<typename T> inline static T as(const Obj& mObj, Idx mIndex, const T& mDefault)			{ return hasIndex(mObj, mIndex) ? as<T>(mObj, mIndex) : mDefault; }

	inline static Obj readFromString(const std::string& mString)						{ Obj result; Reader reader; Internal::tryParse(result, reader, mString); return result; }
	inline static Obj readFromFile(const std::string& mPath)							{ Obj result; Reader reader; Internal::tryParse(result, reader, ssvu::FileSystem::getFileContents(mPath)); return result; }

	template<typename T> inline static void writeToStream(const Obj& mObj, T& mStream)	{ Writer writer; writer.write(mStream, mObj); mStream.flush(); }
	inline static void writeToString(const Obj& mObj, std::string& mString)				{ std::ostringstream o; writeToStream(mObj, o); mString = o.str(); }
	inline static void writeToFile(const Obj& mObj, const std::string& mPath)			{ std::ofstream o{mPath}; writeToStream(mObj, o); o.close(); }
	inline static std::string getWriteToString(const Obj& mObj)							{ std::string result; writeToString(mObj, result); return result; }
}

#endif
