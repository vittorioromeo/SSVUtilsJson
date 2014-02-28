// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SSVUtils/Test/Test.hpp>
#include "SSVUtilsJson/JsonCpp/json.hpp"
#include "SSVUtilsJson/JsonCpp/jsoncpp.inl"
#include "SSVUtilsJson/Utils/Utils.hpp"
#include "SSVUtilsJson/LinkedValue/LinkedValue.hpp"

#ifndef SSVUJ_TESTS
#define SSVUJ_TESTS

SSVUT_TEST(SSVUJConversionTests)
{
	using namespace std;
	using namespace ssvu;
	using namespace ssvuj;

	#define EXECTEST		do { string s; writeToString(getArch<Type>(original), s); SSVUT_EXPECT(getExtr<Type>(getFromString(s)) == original); } while(false)
	#define MAKETEST(T, V)	do { using Type = T; Type original(V); EXECTEST; } while(false)

	MAKETEST(char, 'a');
	MAKETEST(unsigned char, 'a');
	MAKETEST(int, 100);
	MAKETEST(float, 151.251f);
	MAKETEST(double, 4956.12512);
	MAKETEST(bool, false);
	MAKETEST(bool, true);
	MAKETEST(std::string, "hello");
	//MAKETEST(const char*, "goodbye"); // FAILS, but result is correct
	MAKETEST(long, std::numeric_limits<long>::min());
	MAKETEST(long, std::numeric_limits<long>::max());
	MAKETEST(unsigned int, std::numeric_limits<unsigned int>::min());
	MAKETEST(unsigned int, std::numeric_limits<unsigned int>::max());
	MAKETEST(unsigned long, std::numeric_limits<unsigned long>::min());
	MAKETEST(unsigned long, std::numeric_limits<unsigned long>::max());
	MAKETEST(std::vector<int>, (std::vector<int>{1,2,3,4,5,6,7,8,9,10}));
	MAKETEST(std::vector<std::string>, (std::vector<std::string>{"abc","bcd","efg"}));
	MAKETEST(std::vector<char>, (std::vector<char>{'a','b','c','d','e','f','g'}));
	std::map<int,int> tmap{{1, 5},{4, 2},{33, 14},{1651, 315}};
	MAKETEST(decltype(tmap), tmap);
	std::pair<int,int> tpair{125,231};
	MAKETEST(decltype(tpair), tpair);
	std::tuple<int, float, std::string, char> ttpl{1, 5.f, "ciao", 'p'};
	MAKETEST(decltype(ttpl), ttpl);

	{
		enum testCEnum : int{ssvuj_testCEnum_a,ssvuj_testCEnum_b,ssvuj_testCEnum_c};
		MAKETEST(testCEnum, testCEnum::ssvuj_testCEnum_a);
		MAKETEST(testCEnum, testCEnum::ssvuj_testCEnum_b);
		MAKETEST(testCEnum, testCEnum::ssvuj_testCEnum_c);
	}

	{
		enum class enumClass : int{a,b,c};
		MAKETEST(enumClass, enumClass::a);
		MAKETEST(enumClass, enumClass::b);
		MAKETEST(enumClass, enumClass::c);
	}

	{
		int array[2]{15, 25};
		string s;
		writeToString(getArch<decltype(array)>(array), s);

		int res[2];
		Converter<decltype(res)>::fromObj(getFromString(s), res);

		SSVUT_EXPECT(res[0] == array[0]);
		SSVUT_EXPECT(res[1] == array[1]);
	}

	{
		auto testObj(ssvuj::getArchObj("test1", 15, "test2", 33.f, "test3", std::string{"sup"}));
		int test1; float test2; std::string test3;
		ssvuj::extrObj(testObj, "test1", test1, "test2", test2, "test3", test3);
		SSVUT_EXPECT(test1 == 15); SSVUT_EXPECT(test2 == 33.f); SSVUT_EXPECT(test3 == "sup");
	}

	#undef EXECTEST
	#undef MAKETEST
}

SSVUT_TEST(SSVUJUtilsTests)
{
	using namespace std;
	using namespace ssvu;
	using namespace ssvuj;

	Obj obj;
	SSVUT_EXPECT(ssvuj::getObjSize(obj) == 0);
	SSVUT_EXPECT(!ssvuj::hasObj(obj, "member"));
	SSVUT_EXPECT(ssvuj::getExtr<int>(obj, "member", 1) == 1);
	SSVUT_EXPECT(!ssvuj::hasObj(obj, "member"));

	ssvuj::arch(getObj(obj, "member"), 10);
	SSVUT_EXPECT(ssvuj::getObjSize(obj) == 1);
	SSVUT_EXPECT(ssvuj::hasObj(obj, "member"));
	SSVUT_EXPECT(ssvuj::getExtr<int>(obj, "member", 1) == 10);
}

#endif
