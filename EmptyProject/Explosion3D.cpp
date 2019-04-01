#include "DXUT.h"
#include "Explosion3D.h"


Explosion3D::Explosion3D()
{
}


Explosion3D::~Explosion3D()
{
}

void Explosion3D::Set3DExplosion(RefV3 vPos, RefV3 vScale, RefStr keys, int min, int max, float fS)
{
	transform->vPos = vPos;
	transform->vScale = vScale;

	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");

	AC(Animater);
	lpAnimater->Add(L"Effect", keys, min, max, [&]() { bDestroy = true; });
	lpAnimater->Chanage(L"Effect", fS);	
}
