// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SSVUtils/SSVUtils.h>
#include "SSVUtilsJson/Utils/UtilsJson.h"
#include "SSVUtilsJson/Utils/Internal/Typedefs.h"

using namespace std;
using namespace ssvu;
using namespace ssvu::FileSystem;

namespace ssvuj
{
	Document getRootFromString(const string& mString)
	{
		Document result; result.Parse<0>(mString.c_str());
		if(result.HasParseError()) log(toStr(result.GetParseError()) + "\n" + "From: [" + mString + "]", "ssvuj::getRootFromString");
		return result;
	}
	Document getRootFromFile(const string& mPath)
	{
		Document result; result.Parse<0>(getFileContents(mPath).c_str());
		if(result.HasParseError()) log(toStr(result.GetParseError()) + "\n" + "From: [" + mPath + "]", "ssvuj::getRootFromString");
		return result;
	}
}

