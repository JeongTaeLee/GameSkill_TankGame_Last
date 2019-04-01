//--------------------------------------------------------------------------------------
// File: MeshLoader.h
//
// Wrapper class for ID3DXMesh interface. Handles loading mesh data from an .obj file
// and resource management for material textures.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#ifndef _MESHLOADER_H_
#define _MESHLOADER_H_
#pragma once

// Vertex format
struct VERTEX
{
    D3DXVECTOR3 position;
    D3DXVECTOR3 normal;
    D3DXVECTOR2 texcoord;
};


// Used for a hashtable vertex cache when creating the mesh from a .obj file
struct CacheEntry
{
    UINT index;
    CacheEntry* pNext;
};


// Material properties per mesh subset
struct Material
{
	wstring strName = L"None";

	texture * lpDiffuse = nullptr;
	texture * lpSpecular = nullptr;

};

class CMeshLoader
{
public:
            CMeshLoader();
            ~CMeshLoader();

    HRESULT Create(const WCHAR* strFilename, RefStr mtlFileName = L"None");
    void    Destroy();


    UINT    GetNumMaterials() const
    {
        return (*m_Materials).size();
    }
    Material* GetMaterial( UINT iMaterial )
    {
        return (*m_Materials)[iMaterial];
    }

    ID3DXMesh* GetMesh()
    {
        return m_pMesh;
    }

public:

    HRESULT LoadGeometryFromOBJ( const WCHAR* strFilename, RefStr mtlFileName);
   // HRESULT LoadMaterialsFromMTL(wstring  strFileName, wstring strMaterialName, Material * pMaterial);

    DWORD   AddVertex( UINT hash, VERTEX* pVertex );
    void    DeleteCache();

    ID3DXMesh* m_pMesh;         // Encapsulated D3DX Mesh

    CGrowableArray <CacheEntry*> m_VertexCache;   // Hashtable cache for locating duplicate vertices
    CGrowableArray <VERTEX> m_Vertices;      // Filled and copied to the vertex buffer
    CGrowableArray <DWORD> m_Indices;       // Filled and copied to the index buffer
    CGrowableArray <DWORD> m_Attributes;    // Filled and copied to the attribute buffer
    vector <Material*> *m_Materials = nullptr;     // Holds material properties per subset
};

#endif // _MESHLOADER_H_

