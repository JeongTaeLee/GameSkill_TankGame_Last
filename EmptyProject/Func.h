#pragma once

void LoadTexs(RefStr key, RefStr path, int min, int max);
void LoadTexs(vector<texture*> & veTex, RefStr key, int min, int max);


void LoadMeshs(RefStr key, RefStr path, int min, int max);
void LoadMeshs(vector<CMeshLoader*> & veTex, RefStr key, int min, int max);

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

template<typename T>
T inline GetRandomNumber(T mn, T mx)
{
	if (mn >= mx)
		return T();

	std::random_device rn;
	std::mt19937_64 rnd(rn());

	std::uniform_int_distribution<T> range(mn, mx);

	return range(rnd);
}


template< >
float inline GetRandomNumber < float >(float mn, float mx)
{
	if (mn >= mx)
		return 0.f;

	std::random_device rn;
	std::mt19937_64 rnd(rn());

	std::uniform_real_distribution<float> range(mn, mx);

	return range(rnd);
}

template< >
Vector3 inline GetRandomNumber < Vector3 >(Vector3 mn, Vector3 mx)
{
	std::random_device rn;
	std::mt19937_64 rnd(rn());

	Vector3 result = Vector3(0.f, 0.f, 0.f);

	if (mn.x < mx.x)
	{
		std::uniform_real_distribution<float> range(mn.x, mx.x);

		result.x = range(rnd);
	}
	if (mn.y < mx.y)
	{
		std::uniform_real_distribution<float> range(mn.y, mx.y);

		result.y = range(rnd);
	}
	if (mn.z < mx.z)
	{
		std::uniform_real_distribution<float> range(mn.z, mx.z);

		result.z = range(rnd);
	}

	return result;
}
void GetLookAt(Quaternion &qRot, const Vector3 & vDir);
void GetLookAtS(Quaternion & qRot, const Vector3 & vDir, float _fS);
