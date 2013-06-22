// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_LINKEDVALUE
#define SSVUJ_LINKEDVALUE

#include <vector>
#include <string>
#include "SSVUtilsJson/Utils/UtilsJson.h"

namespace ssvuj
{
	class LinkedValueBase
	{
		protected:
			std::string linkedName;

		public:
			LinkedValueBase(const std::string& mLinkedName) : linkedName{mLinkedName} { }

			virtual void syncFrom(const Json::Value& mRoot) = 0;
			virtual void syncTo(Json::Value& mRoot) = 0;
	};

	template<typename T> class LinkedValue : public LinkedValueBase
	{
		private:
			T value;

		public:
			LinkedValue(const std::string& mLinkedName) : LinkedValueBase{mLinkedName} { }

			inline operator T() { return value; }
			inline LinkedValue& operator=(T mValue) { value = mValue; return *this; }

			void syncFrom(const Json::Value& mRoot) override { value = ssvuj::as<T>(mRoot, linkedName); }
			void syncTo(Json::Value& mRoot) override { mRoot[linkedName] = value; }
	};
}

#endif
