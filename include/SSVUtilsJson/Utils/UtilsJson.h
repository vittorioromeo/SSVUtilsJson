// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILSJSON
#define SSVUJ_UTILSJSON

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <SSVUtils/SSVUtils.h>
#include <SSVJsonCpp/SSVJsonCpp.h>
#include "SSVUtilsJson/Utils/Internal/Helper.h"
#include "SSVUtilsJson/Utils/Internal/Typedefs.h"

namespace ssvuj
{
	inline static unsigned int size(const Value& mArray) { return mArray.size(); }
	inline static unsigned int size(const Value& mRoot, const std::string& mValue) { return mRoot[mValue].size(); }

	inline static bool has(const Value& mRoot, const std::string& mValue) { return mRoot.isMember(mValue); }

	template<typename T> inline static void set(Value& mRoot, const std::string& mValue, T mValueToSet) { mRoot[mValue] = mValueToSet; }

	template<typename T> inline static T as(const Value& mRoot) { return Internal::AsHelper<T>::as(mRoot); }
	template<typename T> inline static T as(const Value& mRoot, const std::string& mValue) { return as<T>(mRoot[mValue]); }
	template<typename T> inline static T as(const Value& mArray, unsigned int mIndex) { return as<T>(mArray[mIndex]); }
	template<typename T> inline static T as(const Value& mRoot, const std::string& mValue, T mDefault) { return mRoot.isMember(mValue) ? as<T>(mRoot, mValue) : mDefault; }
	template<typename T> inline static T as(const Value& mArray, unsigned int mIndex, T mDefault) { return mArray.isValidIndex(mIndex) ? as<T>(mArray, mIndex) : mDefault; }

	inline static Value getRootFromString(const std::string& mString)
	{
		Value result; Json::Reader reader;
		if(!reader.parse(mString, result, false)) ssvu::log(reader.getFormatedErrorMessages() + "\n" + "From: [" + mString + "]", "ssvuj::getRootFromString");
		return result;
	}
	inline static Value getRootFromFile(const std::string& mPath)
	{
		Value result; Json::Reader reader;
		if(!reader.parse(ssvu::FileSystem::getFileContents(mPath), result, false)) ssvu::log(reader.getFormatedErrorMessages() + "\n" + "From: [" + mPath + "]", "ssvuj::getRootFromString");
		return result;
	}
	inline static void writeRootToString(const Value& mRoot, std::string& mString)
	{
		std::ostringstream o;
		Json::StyledStreamWriter writer;
		writer.write(o, mRoot);
		o.flush(); mString = o.str();
	}
	inline static void writeRootToFile(const Value& mRoot, const std::string& mPath)
	{
		std::ofstream o{mPath};
		Json::StyledStreamWriter writer;
		writer.write(o, mRoot);
		o.flush(); o.close();
	}
}

#endif
