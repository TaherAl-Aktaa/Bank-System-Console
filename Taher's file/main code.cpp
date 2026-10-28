#include<iostream>
#include"clsLoginScreen.h"
#include "clsMainMenue.h"

using namespace std;

int main()
{ 
	do
	{
		clsLoginScreen::showLoginScreen();
	} while (LoggedIn);

	return 0;
}