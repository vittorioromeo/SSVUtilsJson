// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVUJ_LINKEDVALUE
#define SSVUJ_LINKEDVALUE

#include <vector>
#include "SSVUtilsJson/Global/Common.hpp"
#include "SSVUtilsJson/Utils/Utils.hpp"

namespace ssvuj
{
	namespace Internal
	{
		class LinkedValueBase
		{
			protected:
				std::string name;

			public:
				LinkedValueBase(std::string mLinkedName) : name{std::move(mLinkedName)} { }
				virtual ~LinkedValueBase() { }

				virtual void syncFrom(const Obj& mRoot) = 0;
				virtual void syncTo(Obj& mRoot) const = 0;
		};
	}

	template<typename T> class LinkedValue final : public Internal::LinkedValueBase
	{
		private:
			T value;

		public:
			LinkedValue(std::string mLinkedName) : Internal::LinkedValueBase{std::move(mLinkedName)} { }

			inline operator T() const noexcept { return value; }
			inline LinkedValue& operator=(const T& mValue) { value = mValue; return *this; }

			inline void syncFrom(const Obj& mObj) override	{ extr(mObj, name, value); }
			inline void syncTo(Obj& mObj) const override	{ arch(mObj, name, value); }
	};

	class LinkedValueManager
	{
		private:
			using Container = std::vector<ssvu::Uptr<Internal::LinkedValueBase>>;
			Obj& obj;
			Container values;

		public:
			LinkedValueManager(Obj& mObj) : obj(mObj) { }

			template<typename T> inline LinkedValue<T>& create(std::string mName) { auto result(new LinkedValue<T>{std::move(mName)}); values.emplace_back(result); return *result; }

			inline void syncFromObj()		{ for(auto& lv : values) lv->syncFrom(obj); }
			inline void syncToObj()	const	{ for(const auto& lv : values) lv->syncTo(obj); }

			inline const Container& getValues() const noexcept { return values; }
	};
}

#endif
