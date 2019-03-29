#pragma once

void LoadTexs(RefStr key, RefStr path, int min, int max);
void LoadTexs(vector<texture*> & veTex, RefStr key, int min, int max);


void LoadMeshs(RefStr key, RefStr path, int min, int max);
void LoadMeshs(vector<Mesh*> & veTex, RefStr key, int min, int max);

template <class T>
float GetLength(const T & start, const T & end)
{
	return 0.f;
}

template<>
inline float GetLength(const Vector3 & start, const Vector3 & end)
{
	return D3DXVec3Length(&(end - start));
}

template<>
inline float GetLength(const Vector2 & start, const Vector2 & end)
{
	return D3DXVec2Length(&(end - start));
}

void GetLookAt(Quaternion &qRot, const Vector3 & vDir);
void GetLookAtS(Quaternion & qRot, const Vector3 & vDir, float _fS);
