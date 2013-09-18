// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_UTILS_IO
#define SSVUJ_UTILS_IO

#include <fstream>
#include <sstream>
#include "SSVUtilsJson/Utils/UtilsJson.h"
#include "SSVUtilsJson/Utils/DefaultConverters.h"

namespace ssvuj
{
	namespace Internal
	{
		inline static void logReadError(const Reader& mReader, const std::string& mFrom)
		{
			ssvu::lo("ssvuj::logReadError") << mReader.getFormattedErrorMessages() << std::endl << "From: [" << mFrom << "]" << std::endl;
		}
		inline static bool tryParse(Obj& mObj, Reader& mReader, const std::string& mSrc)
		{
			if(mReader.parse(mSrc, mObj, false)) return true;
			logReadError(mReader, mSrc); return false;
		}
	}

	inline static Obj readFromString(const std::string& mString)	{ Obj result; Reader reader; Internal::tryParse(result, reader, mString); return result; }
	inline static Obj readFromFile(const Path& mPath)				{ Obj result; Reader reader; Internal::tryParse(result, reader, ssvu::FileSystem::getFileContents(mPath)); return result; }

	template<typename T> inline static void writeToStream(const Obj& mObj, T& mStream)	{ Writer writer; writer.write(mStream, mObj); mStream.flush(); }
	inline static void writeToString(const Obj& mObj, std::string& mString)				{ std::ostringstream o; writeToStream(mObj, o); mString = o.str(); }
	inline static void writeToFile(const Obj& mObj, const Path& mPath)					{ std::ofstream o{mPath}; writeToStream(mObj, o); o.close(); }
	inline static std::string getWriteToString(const Obj& mObj)							{ std::string result; writeToString(mObj, result); return result; }
}

#endif
