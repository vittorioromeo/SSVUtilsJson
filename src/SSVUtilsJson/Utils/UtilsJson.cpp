// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SSVUtils/SSVUtils.h>
#include "SSVUtilsJson/Utils/UtilsJson.h"

using namespace std;
using namespace Json;
using namespace ssvu;
using namespace ssvu::FileSystem;

namespace ssvuj
{
	template<> Value as(const Value& mRoot)			{ return mRoot; }
	template<> int as(const Value& mRoot)			{ return mRoot.asInt(); }
	template<> float as(const Value& mRoot)			{ return mRoot.asFloat(); }
	template<> double as(const Value& mRoot)		{ return mRoot.asDouble(); }
	template<> bool as(const Value& mRoot)			{ return mRoot.asBool(); }
	template<> string as(const Value& mRoot)		{ return mRoot.asString(); }
	template<> char const* as(const Value& mRoot)	{ return mRoot.asCString(); }

	Value getRootFromString(const string& mString)
	{
		Value result; Reader reader;
		if(!reader.parse(mString, result, false)) log(reader.getFormatedErrorMessages() + "\n" + "From: [" + mString + "]", "JSON Error");
		return result;
	}
	Value getRootFromFile(const string& mPath)
	{
		Value result; Reader reader;
		if(!reader.parse(getFileContents(mPath), result, false)) log(reader.getFormatedErrorMessages() + "\n" + "From: [" + mPath + "]", "JSON Error");
		return result;
	}
}

