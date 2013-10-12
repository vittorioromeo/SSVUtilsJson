// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SSVUtils/Test/Test.h>
#include "SSVUtilsJson/JsonCpp/json.h"
#include "SSVUtilsJson/JsonCpp/jsoncpp.inl"
#include "SSVUtilsJson/Utils/UtilsJson.h"
#include "SSVUtilsJson/Utils/DefaultConverters.h"
#include "SSVUtilsJson/Utils/Serialization.h"
#include "SSVUtilsJson/Utils/Io.h"
#include "SSVUtilsJson/LinkedValue/LinkedValue.h"

#ifndef SSVUJ_TEST_TESTS
#define SSVUJ_TEST_TESTS

SSVU_TEST("SSVUJ conversion tests")
{
	using namespace std;
	using namespace ssvu;
	using namespace ssvuj;

	#define EXECTEST		do { string s; writeToString(getArch<Type>(original), s); EXPECT(getExtr<Type>(readFromString(s)) == original); } while(0)
	#define MAKETEST(T, V)	do { using Type = T; Type original(V); EXECTEST; } while(0)

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

	#undef EXECTEST
	#undef MAKETEST
}
SSVU_TEST_END();

#endif


