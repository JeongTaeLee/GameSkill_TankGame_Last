#include "DXUT.h"
#include "ShaderRenderer.h"


ShaderRenderer::ShaderRenderer()
{
}


ShaderRenderer::~ShaderRenderer()
{
}

void ShaderRenderer::Init()
{
	Renderer::Init();

	gameObject->lpShaderRenderer = this;
}

void ShaderRenderer::Release()
{
	Renderer::Release();
	
	if(gameObject->lpShaderRenderer == this)
		gameObject->lpShaderRenderer = nullptr;
}

void ShaderRenderer::Render()
{
	if (lpMesh && lpEffect)
	{
		g_device->SetTransform(D3DTS_WORLD, &transform->matWorld);

		if (begin)
			begin();

		g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);


		UINT pass = 0;
		lpEffect->Begin(&pass, 0);

		for (int j = 0; j < pass; ++j)
		{
			lpEffect->BeginPass(pass);
			for (int i = 0; i < lpMesh->veMat.size(); ++i)
			{
				if (lpMesh->veMat[i]->lpDiffuseMap)
					lpEffect->SetTexture(D3DXHANDLE("gDiffuseTexture"), lpMesh->veMat[i]->lpDiffuseMap->lpTex);
				if (lpMesh->veMat[i]->lpSpecularMap)
					lpEffect->SetTexture(D3DXHANDLE("gSpecularTexture"), lpMesh->veMat[i]->lpSpecularMap->lpTex);
				else
					lpEffect->SetTexture(D3DXHANDLE("gSpecularTexture"), lpMesh->veMat[i]->lpDiffuseMap->lpTex);

				lpEffect->CommitChanges();
				lpMesh->mesh->DrawSubset(i);
			}
			lpEffect->EndPass();
		}

		lpEffect->End();

		if (end)
			end();
	}
}
