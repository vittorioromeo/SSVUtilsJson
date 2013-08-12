// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_LINKEDVALUE
#define SSVUJ_LINKEDVALUE

#include <vector>
#include "SSVUtilsJson/Utils/UtilsJson.h"
#include "SSVUtilsJson/Global/Typedefs.h"

namespace ssvuj
{
	namespace Internal
	{
		class LinkedValueBase
		{
			protected:
				std::string name;

			public:
				LinkedValueBase(const std::string& mLinkedName) : name{mLinkedName} { }
				virtual ~LinkedValueBase() { }

				virtual void syncFrom(const Obj& mRoot) = 0;
				virtual void syncTo(Obj& mRoot) const = 0;
		};
	}

	template<typename T> class LinkedValue : public Internal::LinkedValueBase
	{
		private:
			T value;

		public:
			LinkedValue(const std::string& mLinkedName) : Internal::LinkedValueBase{mLinkedName} { }

			inline operator T() { return value; }
			inline LinkedValue& operator=(const T& mValue) { value = mValue; return *this; }

			inline void syncFrom(const Obj& mObj) override { value = ssvuj::as<T>(mObj, name); }
			inline void syncTo(Obj& mObj) const override { set(mObj, name, value); }
	};

	class LinkedValueManager
	{
		private:
			using Container = std::vector<ssvu::Uptr<Internal::LinkedValueBase>>;
			Obj& obj;
			Container values;

		public:
			LinkedValueManager(Obj& mObj) : obj(mObj) { }

			template<typename T> inline LinkedValue<T>& create(const std::string& mName) { auto result(new LinkedValue<T>{mName}); values.emplace_back(result); return *result; }

			inline void syncFromObj()	{ for(auto& lv : values) lv->syncFrom(obj); }
			inline void syncToObj()		{ for(const auto& lv : values) lv->syncTo(obj); }

			inline const Container& getValues() { return values; }
	};
}

#endif
