// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_LINKEDVALUE
#define SSVUJ_LINKEDVALUE

#include <vector>
#include <string>
#include <SSVUtils/SSVUtils.h>
#include "SSVUtilsJson/Utils/UtilsJson.h"
#include "SSVUtilsJson/Utils/Internal/Typedefs.h"

namespace ssvuj
{
	class LinkedValueBase
	{
		protected:
			std::string linkedName;

		public:
			LinkedValueBase(const std::string& mLinkedName) : linkedName{mLinkedName} { }
			virtual ~LinkedValueBase() { }

			virtual void syncFrom(const Value& mRoot) = 0;
			virtual void syncTo(Value& mRoot) const = 0;
	};

	template<typename T> class LinkedValue : public LinkedValueBase
	{
		private:
			T value;

		public:
			LinkedValue(const std::string& mLinkedName) : LinkedValueBase{mLinkedName} { }
			~LinkedValue() { }

			inline operator T() { return value; }
			inline LinkedValue& operator=(T mValue) { value = mValue; return *this; }

			inline void syncFrom(const Value& mRoot) override { value = ssvuj::as<T>(mRoot, linkedName); }
			inline void syncTo(Value& mRoot) const override { mRoot[linkedName.c_str()] = value; }
	};

	class LinkedValueManager
	{
		private:
			Value& linkedRoot;
			ssvu::MemoryManager<LinkedValueBase> memoryManager;

		public:
			LinkedValueManager(Value& mLinkedRoot) : linkedRoot(mLinkedRoot) { }

			template<typename T> LinkedValue<T>& create(const std::string& mLinkedName) { return memoryManager.create<LinkedValue<T>>(mLinkedName); }

			inline void syncFromRoot() { for(auto& lv : memoryManager) lv->syncFrom(linkedRoot); }
			inline void syncToRoot() { for(const auto& lv : memoryManager) lv->syncTo(linkedRoot); }

			inline const std::vector<LinkedValueBase*>& getLinkedValues() { return memoryManager.getItems(); }
	};
}

#endif
