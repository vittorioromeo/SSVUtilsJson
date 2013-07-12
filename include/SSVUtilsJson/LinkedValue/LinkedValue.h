// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_LINKEDVALUE
#define SSVUJ_LINKEDVALUE

#include <vector>
#include <string>
#include "SSVUtilsJson/Utils/UtilsJson.h"
#include "SSVUtilsJson/Utils/Internal/Typedefs.h"

namespace ssvuj
{
	class LinkedValueBase
	{
		protected:
			String linkedName;

		public:
			LinkedValueBase(const String& mLinkedName) : linkedName{mLinkedName} { }
			virtual ~LinkedValueBase() { }

			virtual void syncFrom(const Impl& mRoot) = 0;
			virtual void syncTo(Impl& mRoot) const = 0;
	};

	template<typename T> class LinkedValue : public LinkedValueBase
	{
		private:
			T value;

		public:
			LinkedValue(const String& mLinkedName) : LinkedValueBase{mLinkedName} { }
			~LinkedValue() { }

			inline operator T() { return value; }
			inline LinkedValue& operator=(T mValue) { value = mValue; return *this; }

			inline void syncFrom(const Impl& mRoot) override { value = ssvuj::as<T>(mRoot, linkedName); }
			inline void syncTo(Impl& mRoot) const override { set(mRoot, linkedName, value); }
	};

	class LinkedValueManager
	{
		private:
			Impl& linkedRoot;
			std::vector<Uptr<LinkedValueBase>> linkedValues;

		public:
			LinkedValueManager(Impl& mLinkedRoot) : linkedRoot(mLinkedRoot) { }

			template<typename T> LinkedValue<T>& create(const String& mLinkedName)
			{
				auto result(new LinkedValue<T>{mLinkedName});
				linkedValues.push_back(Uptr<LinkedValueBase>{result});
				return *result;
			}

			inline void syncFromRoot()	{ for(auto& lv : linkedValues) lv->syncFrom(linkedRoot); }
			inline void syncToRoot()	{ for(const auto& lv : linkedValues) lv->syncTo(linkedRoot); }

			inline const std::vector<Uptr<LinkedValueBase>>& getLinkedValues() { return linkedValues; }
	};
}

#endif
