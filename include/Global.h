#pragma once
#include "clsUser.h"

// empty user object. no user is logged in yet. 
// this variable will be updated after login to hold the logged in user data and permissions.
clsUser CurrentUser = clsUser::FindUser("", ""); 
