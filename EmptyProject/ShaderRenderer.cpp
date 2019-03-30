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
		if (begin)
			begin();
	
		g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		lpEffect->SetMatrix(D3DXHANDLE("gWorldMatrix"), &transform->matWorld);
		lpEffect->SetMatrix(D3DXHANDLE("gViewMatrix"), &CAMERA->matView);
		lpEffect->SetMatrix(D3DXHANDLE("gProjMatrix"), &CAMERA->matProj);

		lpEffect->SetVector(D3DXHANDLE("gCameraPos"), &Vector4(CAMERA->lpNowCamera->vPos, 1.f));
		lpEffect->SetVector(D3DXHANDLE("gLightPos"), &Vector4(3000.f, 5000.f, 0.f, 1.f));
	
		UINT pass = 0;
		lpEffect->Begin(&pass, 0);
	
		for (int j = 0; j < pass; ++j)
		{
			lpEffect->BeginPass(pass);
			for (int i = 0; i < lpMesh->GetNumMaterials(); ++i)
			{
				if (lpMesh->GetMaterial(i)->lpDiffuse)
					lpEffect->SetTexture(D3DXHANDLE("gDiffuseMap"), lpMesh->GetMaterial(i)->lpDiffuse->lpTex);
				if (lpMesh->GetMaterial(i)->lpSpecular)
					lpEffect->SetTexture(D3DXHANDLE("gSpecualrMap"), lpMesh->GetMaterial(i)->lpSpecular->lpTex);
				else
				{
					if (lpMesh->GetMaterial(i)->lpDiffuse)
						lpEffect->SetTexture(D3DXHANDLE("gDiffuseMap"), lpMesh->GetMaterial(i)->lpDiffuse->lpTex);
				}

				lpMesh->GetMesh()->DrawSubset(i);
	
				g_device->SetTexture(0, nullptr);
			}
			lpEffect->EndPass();
		}
	
		lpEffect->End();
	
		if (end)
			end();
	}
}
