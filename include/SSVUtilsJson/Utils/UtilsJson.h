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
	inline static unsigned int size(const Impl& mArray) { return mArray.size(); }
	inline static unsigned int size(const Impl& mRoot, const String& mValue) { return mRoot[mValue].size(); }

	inline static bool has(const Impl& mRoot, const String& mValue) { return mRoot.isMember(mValue); }

	template<typename T> inline static void set(Impl& mRoot, const String& mValue, T mValueToSet) { mRoot[mValue] = mValueToSet; }

	template<typename T> inline static T as(const Impl& mRoot) { return Internal::AsHelper<T>::as(mRoot); }
	template<typename T> inline static T as(const Impl& mRoot, const String& mValue) { return as<T>(mRoot[mValue]); }
	template<typename T> inline static T as(const Impl& mArray, unsigned int mIndex) { return as<T>(mArray[mIndex]); }
	template<typename T> inline static T as(const Impl& mRoot, const String& mValue, T mDefault) { return has(mRoot, mValue) ? as<T>(mRoot, mValue) : mDefault; }
	template<typename T> inline static T as(const Impl& mArray, unsigned int mIndex, T mDefault) { return mArray.isValidIndex(mIndex) ? as<T>(mArray, mIndex) : mDefault; }

	inline static Impl getRootFromString(const String& mString)
	{
		Impl result; Json::Reader reader;
		if(!reader.parse(mString, result, false)) ssvu::log(reader.getFormatedErrorMessages() + "\n" + "From: [" + mString + "]", "ssvuj::getRootFromString");
		return result;
	}
	inline static Impl getRootFromFile(const String& mPath)
	{
		Impl result; Json::Reader reader;
		if(!reader.parse(ssvu::FileSystem::getFileContents(mPath), result, false)) ssvu::log(reader.getFormatedErrorMessages() + "\n" + "From: [" + mPath + "]", "ssvuj::getRootFromString");
		return result;
	}
	inline static void writeRootToString(const Impl& mRoot, String& mString)
	{
		std::ostringstream o;
		Json::StyledStreamWriter writer;
		writer.write(o, mRoot);
		o.flush(); mString = o.str();
	}
	inline static void writeRootToFile(const Impl& mRoot, const String& mPath)
	{
		std::ofstream o{mPath};
		Json::StyledStreamWriter writer;
		writer.write(o, mRoot);
		o.flush(); o.close();
	}

	Impl& getChild(Impl& mImpl, const std::string& mName) { return mImpl[mName]; }
	const Impl& getChildConst(const Impl& mImpl, const std::string& mName) { return mImpl[mName]; }

	Impl::iterator beginNonConst(Impl& mRoot)           { return mRoot.begin(); }
	Impl::iterator endNonConst(Impl& mRoot)             { return mRoot.end(); }
	Impl::const_iterator beginConst(const Impl& mRoot)  { return mRoot.begin(); }
	Impl::const_iterator endConst(const Impl& mRoot)    { return mRoot.end(); }

	class WrapperIterator;

	class Wrapper
	{
		private:
			Impl& impl;

		public:
			Wrapper(Impl& mImpl);

			Wrapper operator[](const std::string& mName);
			const Wrapper operator[](const std::string& mName) const;

			WrapperIterator begin();
			WrapperIterator end();
			//Impl::const_iterator begin() const  { return ssvuj::beginConst(impl); }
			//Impl::const_iterator end() const    { return ssvuj::endConst(impl); }
	};

	class WrapperIterator
	{
		private:
			Impl::iterator implIterator;

		public:
			WrapperIterator(Impl::iterator mImplIterator) : implIterator(mImplIterator) { }

			void operator++() { implIterator++; }
			Wrapper operator*() { return Wrapper(*implIterator); }
			Wrapper operator->() { return Wrapper(*implIterator); }

			bool operator==(const WrapperIterator& rhs) { return implIterator == rhs.implIterator; }
			bool operator!=(const WrapperIterator& rhs) { return implIterator != rhs.implIterator; }
	};


	Wrapper::Wrapper(Impl& mImpl) : impl(mImpl) { }

	Wrapper Wrapper::operator[](const std::string& mName) { return Wrapper(ssvuj::getChild(impl, mName)); }
	const Wrapper Wrapper::operator[](const std::string& mName) const { return Wrapper(ssvuj::getChild(impl, mName)); }

	WrapperIterator Wrapper::begin()              { return WrapperIterator(ssvuj::beginNonConst(impl)); }
	WrapperIterator Wrapper::end()                { return WrapperIterator(ssvuj::endNonConst(impl)); }




	typedef Wrapper Value;
}

#endif
