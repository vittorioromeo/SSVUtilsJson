// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILSJSON
#define SSVUJ_UTILSJSON

#include <vector>
#include <map>
#include <fstream>
#include <sstream>
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
		template<> struct Converter<char>
		{
			using T = char;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = static_cast<T>(mObj.asInt()); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ mObj = mValue; }
		};
		template<> struct Converter<unsigned char>
		{
			using T = unsigned char;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = static_cast<T>(mObj.asInt()); }
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
		template<typename TItem> struct Converter<std::map<Key, TItem>>
		{
			using T = std::map<Key, TItem>;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ for(auto itr(mObj.begin()); itr != mObj.end(); ++itr) mValue[itr.key()] = getFromObj<TItem>(*itr); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ for(const auto& p : mValue) mObj[p.first] = p.second; }
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


	// Basic json obj manipulation
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


	// Serialization helpers
	namespace Internal
	{
		template<Idx TIdx, typename TArg> inline static void extractHelper(const Obj& mArray, TArg& mArg) { mArg = as<TArg>(mArray, TIdx); }
		template<Idx TIdx, typename TArg, typename... TArgs> inline static void extractHelper(const Obj& mArray, TArg& mArg, TArgs&... mArgs)
		{
			mArg = as<TArg>(mArray, TIdx); extractHelper<TIdx + 1>(mArray, std::forward<TArgs&>(mArgs)...);
		}

		template<Idx TIdx, typename TArg> inline static void archiveHelper(Obj& mArray, const TArg& mArg) { set(mArray, TIdx, mArg); }
		template<Idx TIdx, typename TArg, typename... TArgs> inline static void archiveHelper(Obj& mArray, const TArg& mArg, const TArgs&... mArgs)
		{
			set(mArray, TIdx, mArg); archiveHelper<TIdx + 1>(mArray, std::forward<const TArgs&>(mArgs)...);
		}

		template<typename TArg> inline static void extractMapHelper(const Obj& mObj, const Key& mKey, TArg& mArg) { mArg = as<TArg>(mObj, mKey); }
		template<typename TArg, typename... TArgs> inline static void extractMapHelper(const Obj& mObj, const Key& mKey, TArg& mArg, TArgs&... mArgs)
		{
			mArg = as<TArg>(mObj, mKey); extractMapHelper(mObj, std::forward<TArgs&>(mArgs)...);
		}

		template<typename TArg> inline static void archiveMapHelper(Obj& mObj, const Key& mKey, const TArg& mArg) { set(mObj, mKey, mArg); }
		template<typename TArg, typename... TArgs> inline static void archiveMapHelper(Obj& mObj, const Key& mKey, TArg&& mArg, const TArgs&... mArgs)
		{
			set(mObj, mKey, mArg); archiveMapHelper(mObj, std::forward<const TArgs&>(mArgs)...);
		}
	}

	template<typename... TArgs> inline static void extract(const Obj& mArray, TArgs&... mArgs)	{ Internal::extractHelper<0>(mArray, std::forward<TArgs&>(mArgs)...); }
	template<typename... TArgs> inline static void archive(Obj& mArray, const TArgs&... mArgs)	{ Internal::archiveHelper<0>(mArray, std::forward<const TArgs&>(mArgs)...); }
	template<typename... TArgs> inline static Obj getArchived(const TArgs&... mArgs)			{ Obj result; archive(result, std::forward<const TArgs&>(mArgs)...); return result; }

	template<typename... TArgs> inline static void extractMap(const Obj& mObj, TArgs&... mArgs)	{ Internal::extractMapHelper(mObj, std::forward<TArgs&>(mArgs)...); }
	template<typename... TArgs> inline static void archiveMap(Obj& mObj, const TArgs&... mArgs)	{ Internal::archiveMapHelper(mObj, std::forward<const TArgs&>(mArgs)...); }


	// Input/output
	inline static Obj readFromString(const std::string& mString)	{ Obj result; Reader reader; Internal::tryParse(result, reader, mString); return result; }
	inline static Obj readFromFile(const Path& mPath)				{ Obj result; Reader reader; Internal::tryParse(result, reader, ssvu::FileSystem::getFileContents(mPath)); return result; }

	template<typename T> inline static void writeToStream(const Obj& mObj, T& mStream)	{ Writer writer; writer.write(mStream, mObj); mStream.flush(); }
	inline static void writeToString(const Obj& mObj, std::string& mString)				{ std::ostringstream o; writeToStream(mObj, o); mString = o.str(); }
	inline static void writeToFile(const Obj& mObj, const Path& mPath)					{ std::ofstream o{mPath}; writeToStream(mObj, o); o.close(); }
	inline static std::string getWriteToString(const Obj& mObj)							{ std::string result; writeToString(mObj, result); return result; }
}

#endif
