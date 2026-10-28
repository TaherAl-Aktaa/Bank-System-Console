#pragma once
#include<iostream>
#include"clsUser.h"

using namespace std;

clsUser CurrentUser = clsUser::find("");

bool LoggedIn = false;

int EncryptionKey = 10;