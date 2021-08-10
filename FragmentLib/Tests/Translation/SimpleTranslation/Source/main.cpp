#include <Fragment/Fragment.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using std::cin;
using namespace Fragment;

#ifdef _DEBUG
#pragma comment(lib, "FragmentLib_d.lib")
#else
#pragma comment(lib, "FragmentLib.lib")
#endif

StringA WelcomeMessage, RequestNumberMessage, NumberLowMessage, NumberHighMessage, 
	RightNumberMessage;
#define ENGLISH
int main(int argc, char **argv)
{
	CreateDefaultMemoryList();
	CTranslationInfo Translation(new ITranslationInfo);
#ifdef ENGLISH
#include "lang_en.h"
#elif defined(PORTUGUESE)
#include "lang_pt.h"
#endif
	WelcomeMessage = FRAGMENTLIB_FEED_TRANSLATION_BLOCK(Translation, TONATIVETEXT("WelcomeMsg"));
	RequestNumberMessage = 
		FRAGMENTLIB_FEED_TRANSLATION_BLOCK(Translation, TONATIVETEXT("RequestNumberMsg"));
	NumberLowMessage = 
		FRAGMENTLIB_FEED_TRANSLATION_BLOCK(Translation, TONATIVETEXT("NumberLowMsg"));
	NumberHighMessage = 
		FRAGMENTLIB_FEED_TRANSLATION_BLOCK(Translation, TONATIVETEXT("NumberHighMsg"));
	RightNumberMessage = 
		FRAGMENTLIB_FEED_TRANSLATION_BLOCK(Translation, TONATIVETEXT("RightNumberMsg"));
	printf("%s\n", WelcomeMessage.Get());
	unsigned long Number = (rand() % 30) + 1;
	unsigned long Match = 0;
	while(Match != Number)
	{
		printf("%s\n", RequestNumberMessage.Get());
		cin >> Match;
		if(Match < Number)
		{
			printf("%s\n", NumberLowMessage.Get());
		}
		else if(Match > Number)
		{
			printf("%s\n", NumberHighMessage.Get());
		}
		else
		{
			printf("%s\n", RightNumberMessage.Get());
		};
	};
	system("PAUSE");
	return 0;
};
