#pragma once
class MainGame
{
public:
	LPDIRECT3DTEXTURE9 mouse;
public:
	MainGame();
	virtual ~MainGame();

	void Init();
	void Release();
	void Update();
	void Render();

};

