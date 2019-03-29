#include "DXUT.h"
#include "MeshLoader.h"


HRESULT MeshLoader::LoadGeometryFromOBJ(Mesh * lpMesh, wstring  strFilename)
{
	wstring mtlpath;
	wstring mtlname;

	CGrowableArray <D3DXVECTOR3> Positions;
	CGrowableArray <D3DXVECTOR2> TexCoords;
	CGrowableArray <D3DXVECTOR3> Normals;

	DWORD dwCurSubset = 0;

	// File inpu
	wstring strCommand;
	wifstream InFile(strFilename);

	if (!InFile)
		return DXTRACE_ERR(L"wifstream::open", E_FAIL);

	while(!InFile.eof())
	{
		InFile >> strCommand;
		if (!InFile)
			break;

		if (0 == wcscmp(strCommand.c_str(), L"v"))
		{
			// Vertex Position
			float x, y, z;
			InFile >> x >> y >> z;
			Positions.Add(D3DXVECTOR3(x, y, z));
		}
		else if (0 == wcscmp(strCommand.c_str(), L"vt"))
		{
			// Vertex TexCoord
			float u, v;
			InFile >> u >> v;
			TexCoords.Add(D3DXVECTOR2(u, 1.f - v));
		}
		else if (0 == wcscmp(strCommand.c_str(), L"vn"))
		{
			// Vertex Normal
			float x, y, z;
			InFile >> x >> y >> z;
			Normals.Add(D3DXVECTOR3(x, y, z));
		}
		else if (0 == wcscmp(strCommand.c_str(), L"f"))
		{
			// Face
			UINT iPosition, iTexCoord, iNormal;
			VERTEX vertex;

			for (UINT iFace = 0; iFace < 3; iFace++)
			{
				ZeroMemory(&vertex, sizeof(VERTEX));

				// OBJ format uses 1-based arrays
				InFile >> iPosition;
				vertex.position = Positions[iPosition - 1];

				if ('/' == InFile.peek())
				{
					InFile.ignore();

					if ('/' != InFile.peek())
					{
						// Optional texture coordinate
						InFile >> iTexCoord;
						vertex.uv = TexCoords[iTexCoord - 1];
					}

					if ('/' == InFile.peek())
					{
						InFile.ignore();

						// Optional vertex normal
						InFile >> iNormal;
						vertex.normal = Normals[iNormal - 1];
					}
				}

				// If a duplicate vertex doesn't exist, add this vertex to the Vertices
				// list. Store the index in the Indices array. The Vertices and Indices
				// lists will eventually become the Vertex Buffer and Index Buffer for
				// the mesh.
				DWORD index = AddVertex(iPosition, &vertex);

				m_Indices.Add(index);
			}
			m_Attributes.Add(dwCurSubset);
		}
		else if (0 == wcscmp(strCommand.c_str(), L"mtllib"))
		{
			InFile >> mtlpath;

			int index = strFilename.rfind(L"/");
			mtlpath = strFilename.substr(0, index + 1) + mtlpath;
		}
		else if (0 == wcscmp(strCommand.c_str(), L"usemtl"))
		{
			// Material
			WCHAR strName[MAX_PATH] = { 0 };
			InFile >> strName;

			bool bFound = false;
			for (int iMaterial = 0; iMaterial < lpMesh->veMat.size(); iMaterial++)
			{
				Material* pCurMaterial = lpMesh->veMat[iMaterial];
				if (0 == wcscmp(pCurMaterial->strName.c_str(), strName))
				{
					bFound = true;
					dwCurSubset = iMaterial;
					break;
				}
			}

			if (!bFound)
			{
				Material * pMaterial = new Material();
				pMaterial->strName = strName;
			

				dwCurSubset = lpMesh->veMat.size();
				
				InitMaterial(lpMesh, mtlpath, pMaterial);

				lpMesh->veMat.push_back(pMaterial);
			}
		}
	}

	// Cleanup
	InFile.close();

	Positions.RemoveAll();
	TexCoords.RemoveAll();
	Normals.RemoveAll();


	return S_OK;
}

void MeshLoader::InitMaterial(Mesh * lpMesh, wstring path, Material * pMaterial)
{
	wifstream InFile(path);
	if (!InFile)
	{
		DEBUG_LOGW("Failed Load Material : " << path);
		return;
	}

	bool bFound = false;

	while(!InFile.eof())
	{
		wstring strCommand;
		InFile >> strCommand;
		if (!InFile)
			break;

		if (0 == wcscmp(strCommand.c_str(), L"newmtl") && !bFound)
		{
			InFile >> strCommand;

			if (0 == wcscmp(strCommand.c_str(), pMaterial->strName.c_str()))
				bFound = true;
		}

		else if (0 == wcscmp(strCommand.c_str(), L"newmtl") && bFound)
			break;
		else if (0 == wcscmp(strCommand.c_str(), L"map_Kd") && bFound)
		{
			InFile >> strCommand;

			int index = path.rfind(L"/");
			wstring imagePath = path.substr(0, index + 1) + strCommand;
		
			index = imagePath.rfind(L".");
			imagePath = imagePath.substr(0, index + 1) + L"png";

			pMaterial->lpDiffuseMap = RESOURCE->AddTex(imagePath, imagePath);
		}
		else if (0 == wcscmp(strCommand.c_str(), L"map_Ks") && bFound)
		{
			InFile >> strCommand;

			int index = path.rfind(L"/");
			wstring imagePath = path.substr(0, index + 1) + strCommand;

			index = imagePath.rfind(L".");
			imagePath = imagePath.substr(index + 1) + L"png";

			pMaterial->lpSpecularMap = RESOURCE->AddTex(imagePath, imagePath);
		}
	}
	InFile.close();
}



DWORD MeshLoader::AddVertex(UINT hash, VERTEX * pVertex)
{
	// If this vertex doesn't already exist in the Vertices list, create a new entry.
		// Add the index of the vertex to the Indices list.
	bool bFoundInList = false;
	DWORD index = 0;

	// Since it's very slow to check every element in the vertex list, a hashtable stores
	// vertex indices according to the vertex position's index as reported by the OBJ file
	if ((UINT)m_VertexCache.GetSize() > hash)
	{
		CacheEntry* pEntry = m_VertexCache.GetAt(hash);
		while (pEntry != NULL)
		{
			VERTEX* pCacheVertex = m_Vertices.GetData() + pEntry->index;

			// If this vertex is identical to the vertex already in the list, simply
			// point the index buffer to the existing vertex
			if (0 == memcmp(pVertex, pCacheVertex, sizeof(VERTEX)))
			{
				bFoundInList = true;
				index = pEntry->index;
				break;
			}

			pEntry = pEntry->pNext;
		}
	}

	// Vertex was not found in the list. Create a new entry, both within the Vertices list
	// and also within the hashtable cache
	if (!bFoundInList)
	{
		// Add to the Vertices list
		index = m_Vertices.GetSize();
		m_Vertices.Add(*pVertex);

		// Add this to the hashtable
		CacheEntry* pNewEntry = new CacheEntry;
		if (pNewEntry == NULL)
			return (DWORD)-1;

		pNewEntry->index = index;
		pNewEntry->pNext = NULL;

		// Grow the cache if needed
		while ((UINT)m_VertexCache.GetSize() <= hash)
		{
			m_VertexCache.Add(NULL);
		}

		// Add to the end of the linked list
		CacheEntry* pCurEntry = m_VertexCache.GetAt(hash);
		if (pCurEntry == NULL)
		{
			// This is the head element
			m_VertexCache.SetAt(hash, pNewEntry);
		}
		else
		{
			// Find the tail
			while (pCurEntry->pNext != NULL)
			{
				pCurEntry = pCurEntry->pNext;
			}

			pCurEntry->pNext = pNewEntry;
		}
	}

	return index;
}

void MeshLoader::DeleteCache()
{
	// Iterate through all the elements in the cache and subsequent linked lists
	for (int i = 0; i < m_VertexCache.GetSize(); i++)
	{
		CacheEntry* pEntry = m_VertexCache.GetAt(i);
		while (pEntry != NULL)
		{
			CacheEntry* pNext = pEntry->pNext;
			SAFE_DELETE(pEntry);
			pEntry = pNext;
		}
	}

	m_VertexCache.RemoveAll();
}

MeshLoader::MeshLoader()
{
}


MeshLoader::~MeshLoader()
{
}

HRESULT MeshLoader::Create(Mesh * lpMesh, const WCHAR * strFilename)
{
	HRESULT hr;

	// Start clean
	Destroy();

	// Create the encapsulated mesh
	LoadGeometryFromOBJ(lpMesh, strFilename);
	
	D3DXCreateMeshFVF(m_Indices.GetSize() / 3, m_Vertices.GetSize(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT, MYFVF,
		g_device, &lpMesh->mesh);

	// Copy the vertex data
	VERTEX* pVertex;
	lpMesh->mesh->LockVertexBuffer(0, (void**)&pVertex);
	memcpy(pVertex, m_Vertices.GetData(), m_Vertices.GetSize() * sizeof(VERTEX));
	lpMesh->mesh->UnlockVertexBuffer();
	m_Vertices.RemoveAll();

	// Copy the index data
	DWORD* pIndex;
	lpMesh->mesh->LockIndexBuffer(0, (void**)&pIndex);
	memcpy(pIndex, m_Indices.GetData(), m_Indices.GetSize() * sizeof(DWORD));
	lpMesh->mesh->UnlockIndexBuffer();
	m_Indices.RemoveAll();

	// Copy the attribute data
	DWORD* pSubset;
	lpMesh->mesh->LockAttributeBuffer(0, &pSubset);
	memcpy(pSubset, m_Attributes.GetData(), m_Attributes.GetSize() * sizeof(DWORD));
	lpMesh->mesh->UnlockAttributeBuffer();
	m_Attributes.RemoveAll();

	DeleteCache();

	return S_OK;
}

void MeshLoader::Destroy()
{
	m_Vertices.RemoveAll();
	m_Indices.RemoveAll();
	m_Attributes.RemoveAll();
}
