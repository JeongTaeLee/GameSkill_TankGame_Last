#include "DXUT.h"
#include "BBRenderer.h"


BBRenderer::BBRenderer()
{
}


BBRenderer::~BBRenderer()
{
}

void BBRenderer::Init()
{
	OBJECT->AddBBRenderer(this);

	gameObject->lpBBRenderer = this;
}

void BBRenderer::Release()
{
	OBJECT->DeleteBBRenderer(this);

	if (gameObject->lpBBRenderer == this)
		gameObject->lpBBRenderer = nullptr;
}

void BBRenderer::Render()
{
	if (lpEffectTex)
	{
		
		BillBoarding(transform->matWorld, transform->vPos, transform->vScale);
		g_device->SetTransform(D3DTS_WORLD, &transform->matWorld);

		g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		/*
		g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		g_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		g_device->SetRenderState(D3DRS_ZENABLE, false);
		*/

		g_device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		g_device->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
		g_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		g_device->SetTexture(0, lpEffectTex->lpTex);		
		RESOURCE->lpMesh->DrawSubset(0);
		g_device->SetTexture(0, nullptr);
		
		g_device->SetRenderState(D3DRS_ALPHATESTENABLE, false);

		/*
		g_device->SetRenderState(D3DRS_ZENABLE, true);
		g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		*/
	}
}
