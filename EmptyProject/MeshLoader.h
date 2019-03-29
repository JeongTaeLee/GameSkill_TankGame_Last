#pragma once
struct CacheEntry
{
	UINT index;
	CacheEntry* pNext;
};


struct Material
{
	wstring strName;

	texture* lpDiffuseMap = nullptr;
	texture * lpSpecularMap = nullptr;
};

struct Mesh
{
	LPD3DXMESH mesh = nullptr;

	vector<Material*> veMat;
	
	texture * GetDiffuse(int index) { return veMat[index]->lpDiffuseMap; }
	texture * GetSpecular(int index) { return veMat[index]->lpSpecularMap; }


	virtual ~Mesh()
	{
		SAFE_RELEASE(mesh);

		for (auto Iter : veMat)
			SAFE_DELETE(Iter);

		veMat.clear();
	}
};

class MeshLoader
{
public:
	CGrowableArray <CacheEntry*> m_VertexCache;   // Hashtable cache for locating duplicate vertices
	CGrowableArray <VERTEX> m_Vertices;      // Filled and copied to the vertex buffer
	CGrowableArray <DWORD> m_Indices;       // Filled and copied to the index buffer
	CGrowableArray <DWORD> m_Attributes;    // Filled and copied to the attribute buffer

	HRESULT LoadGeometryFromOBJ(Mesh * lpMesh, wstring strFilename);
	void    InitMaterial(Mesh * lpMesh, wstring path, Material* pMaterial);

	DWORD   AddVertex(UINT hash, VERTEX* pVertex);
	void    DeleteCache();
public:
	MeshLoader();
	virtual ~MeshLoader();


	HRESULT Create(Mesh * lpMesh, const WCHAR* strFilename);
	void    Destroy();
};

