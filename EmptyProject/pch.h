#pragma once

enum
{
	WINDOWX = 1280,
	WINDOWY = 720,
};

using namespace std;

#include <iostream>
#include <functional>	
#include <thread>	
#include <vector>
#include <string>
#include <list>
#include <map>

using Vector4 = D3DXVECTOR4;
using Vector3 = D3DXVECTOR3;
using Vector2 = D3DXVECTOR2;
using Matrix = D3DXMATRIX;
using Quaternion = D3DXQUATERNION;

using RefV3 = const Vector3 &;
using RefStr = const wstring &;

#ifdef DEBUG
#define DEBUG_LOG(s) cout << s << endl

#define DEBUG_LOG_V3(s) cout << s.x << ", "	<< s.y << ", "	<< s.z << endl;
#define DEBUG_LOG_V2(s) cout << s.x << ", "	<< s.y << endl;

#else
#define DEBUG_LOG(s)
#endif

#include "SceneManager.h"
#include "InputManager.h"