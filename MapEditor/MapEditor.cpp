#include "stdafx.h"
#include "ForwardDeclaration.h"
#include "Universe.h"
/*
FILTERKEYS InitKeySettings()
	//http://irrlicht.sourceforge.net/forum/viewtopic.php?f=1&t=10637
{
	// a couple of structures to hold the original and updated filterkey info
	//
	FILTERKEYS original_FilterKeys, irr_FilterKeys;

	// save the user's original filterkey settings
	//
	ZeroMemory(&original_FilterKeys, sizeof(FILTERKEYS));
	original_FilterKeys.cbSize = sizeof(FILTERKEYS);
	SystemParametersInfo(SPI_GETFILTERKEYS, sizeof(FILTERKEYS), &original_FilterKeys, 0);

	// set the delay values so we get 'instant' response on held keys
	//
	ZeroMemory(&irr_FilterKeys, sizeof(FILTERKEYS));
	irr_FilterKeys.cbSize = sizeof(FILTERKEYS);
	irr_FilterKeys.iDelayMSec = 1;
	irr_FilterKeys.iWaitMSec = 1;
	irr_FilterKeys.iRepeatMSec = 1;
	irr_FilterKeys.iBounceMSec = 0;
	irr_FilterKeys.dwFlags = FKF_FILTERKEYSON;
	SystemParametersInfo(SPI_SETFILTERKEYS,   sizeof(FILTERKEYS), &irr_FilterKeys, 0);
	return original_FilterKeys;
}

void ResetKeySettings(FILTERKEYS original_FilterKeys)
	//http://irrlicht.sourceforge.net/forum/viewtopic.php?f=1&t=10637
{
	// restore keyfilter settings
	//
	SystemParametersInfo(SPI_SETFILTERKEYS,   sizeof(FILTERKEYS), &original_FilterKeys, 0);
}
*/
int main(int argc, char* argv[])
{
	//FILTERKEYS originalFilterKeys = InitKeySettings();

	setlocale(LC_CTYPE, "Russian_Russia.1251");

	Universe* universe = universe = new Universe();
	while (!universe->Menu())
		if (universe->Run())
			break;

	//ResetKeySettings(originalFilterKeys);

	return 0;
}
