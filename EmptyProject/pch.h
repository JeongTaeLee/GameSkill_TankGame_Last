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
#include <fstream>
#include <random>

using Vector4 = D3DXVECTOR4;
using Vector3 = D3DXVECTOR3;
using Vector2 = D3DXVECTOR2;
using Matrix = D3DXMATRIX;
using Quaternion = D3DXQUATERNION;

using RefV3 = const Vector3 &;
using RefStr = const wstring &;

#ifdef DEBUG
#define DEBUG_LOG(s) cout << s << endl
#define DEBUG_LOGW(s)  wcout << s << endl

#define DEBUG_LOG_V3(s) cout << s.x << ", "	<< s.y << ", "	<< s.z << endl;
#define DEBUG_LOG_V2(s) cout << s.x << ", "	<< s.y << endl;

#else
#define DEBUG_LOG(s)

#define DEBUG_LOG(s) cout << s << endl
#define DEBUG_LOGW(s)  wcout << s << endl

#define DEBUG_LOG_V3(s) cout << s.x << ", "	<< s.y << ", "	<< s.z << endl;
#define DEBUG_LOG_V2(s) cout << s.x << ", "	<< s.y << endl;

#endif

#define g_device DXUTGetD3D9Device()

struct texture
{
	LPDIRECT3DTEXTURE9 lpTex = nullptr;
	D3DXIMAGE_INFO info;

	texture(LPDIRECT3DTEXTURE9 _lpTex, D3DXIMAGE_INFO _info)
		:lpTex(_lpTex), info(_info)
	{}
	~texture()
	{
		SAFE_RELEASE(lpTex);
	}
};

#define Et DXUTGetElapsedTime()


#include "SceneManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "CameraManger.h"
#include "MapManager.h"

#include "MeshLoader.h"
#include "Func.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Renderer.h"
#include "ShaderRenderer.h"	
#include "UIRenderer.h"
#include "Animater.h"
#include "RigidBody.h"
#include "PixelCollider.h"