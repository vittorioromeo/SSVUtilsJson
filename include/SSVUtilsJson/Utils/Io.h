// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILS_IO
#define SSVUJ_UTILS_IO

#include <fstream>
#include <sstream>
#include <SSVUtils/Log/Log.h>
#include "SSVUtilsJson/Utils/UtilsJson.h"
#include "SSVUtilsJson/Utils/DefaultConverters.h"

namespace ssvuj
{
	namespace Internal
	{
		inline bool tryParse(Obj& mObj, Reader& mReader, const std::string& mSrc)
		{
			if(mReader.parse(mSrc, mObj, false)) return true;
			ssvu::lo("ssvuj::logReadError") << mReader.getFormattedErrorMessages() << "\nFrom: [" << mSrc << "]" << std::endl;
			return false;
		}
	}

	inline Obj readFromString(const std::string& mStr)	{ Obj result; Reader reader; Internal::tryParse(result, reader, mStr); return result; }
	inline Obj readFromFile(const Path& mPath)			{ Obj result; Reader reader; Internal::tryParse(result, reader, ssvu::FileSystem::getFileContents(mPath)); return result; }

	template<typename T> inline void writeToStream(const Obj& mObj, T& mStream)	{ Writer writer; writer.write(mStream, mObj); mStream.flush(); }
	inline void writeToString(const Obj& mObj, std::string& mStr)				{ std::ostringstream o; writeToStream(mObj, o); mStr = o.str(); }
	inline void writeToFile(const Obj& mObj, const Path& mPath)					{ std::ofstream o{mPath}; writeToStream(mObj, o); o.close(); }
	inline std::string getWriteToString(const Obj& mObj)						{ std::string result; writeToString(mObj, result); return result; }
}

#endif
