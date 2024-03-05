#pragma once

#include <windows.h>
#include <tchar.h>
#include <iostream>

#include <fstream>
#include <ctime>
#include <mutex>

#include <stdio.h>
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include <Psapi.h>
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "Psapi.lib")

#define BOOL_TEXT(x) (x ? "true" : "false")
