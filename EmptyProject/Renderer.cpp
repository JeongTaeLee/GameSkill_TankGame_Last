#include "DXUT.h"
#include "Renderer.h"
#include "MeshLoader.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Init()
{
	gameObject->lpRenderer = this;

	OBJECT->AddRenderer(this);
}

void Renderer::Release()
{
	if (gameObject->lpRenderer == this)
		gameObject->lpRenderer = nullptr;
	OBJECT->DeleteRenderer(this);
}

void Renderer::Render()
{
	if (lpMesh)
	{
		g_device->SetTransform(D3DTS_WORLD, &transform->matWorld);

		if(begin)
			begin();

		g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);


		for (int i = 0; i < lpMesh->GetNumMaterials(); ++i)
		{
			if (lpMesh->GetMaterial(i)->lpDiffuse)
				g_device->SetTexture(0, lpMesh->GetMaterial(i)->lpDiffuse->lpTex);
			
			lpMesh->GetMesh()->DrawSubset(i);
			
			g_device->SetTexture(0, nullptr);
		}

		if(end)
			end();
	}
}
