#pragma once
#include <stdio.h>
#include <math.h>
#include <DirectXMath.h>

namespace math {

class Vector2 :public DirectX::XMFLOAT2 {
public:
	Vector2() { x = 0.f, y = 0.f; };
	Vector2(const float &_x, const float &_y) { x = _x, y = _y; }

	//初期化
	//すべてゼロを入れる
	static Vector2 Initialize() { return Vector2(0, 0); }

	//各種オペレータ対応
	Vector2 operator+(const Vector2 &_vec) {
		return Vector2(x + _vec.x, y + _vec.y);
	}
	Vector2 operator-(const Vector2 &_vec) {
		return Vector2(x - _vec.x, y - _vec.y);
	}
	Vector2 operator*(const Vector2 &_vec) {
		return Vector2(x * _vec.x, y * _vec.y);
	}
	Vector2 operator/(const Vector2 &_vec) {
		return Vector2(x / _vec.x, y / _vec.y);
	}

};

class Vector3 :public DirectX::XMFLOAT3 {
public:
	Vector3() { x = 0.f, y = 0.f, z = 0.f; };
	Vector3(float _x, float _y) { x = _x, y = _y; z = z; }
	Vector3(float _x, float _y, float _z) { x = _x, y = _y; z = _z; }
	Vector3(Vector2 _vec2) { x = _vec2.x, y = _vec2.y; }

	//初期化
	//すべてゼロを入れる
	static Vector3 Initialize() { return Vector3(0, 0, 0); }
	static Vector3 Right() { return Vector3(1, 0, 0); }
	static Vector3 Up() { return Vector3(0, 1, 0); }
	static Vector3 Front() { return Vector3(0, 0, 1); }

	//各種オペレータ対応
	Vector3 operator+(const Vector3& _vec) {
		return Vector3(x + _vec.x, y + _vec.y, z + _vec.z);
	}
	Vector3 operator-(const Vector3& _vec) {
		return Vector3(x - _vec.x, y - _vec.y, z - _vec.z);
	}
	Vector3 operator*(const Vector3& _vec) {
		return Vector3(x * _vec.x, y * _vec.y, z * _vec.z);
	}
	Vector3 operator/(const Vector3& _vec) {
		return Vector3(x / _vec.x, y / _vec.y, z / _vec.z);
	}
	Vector3 operator*(const float& _vec) {
		return Vector3(x * _vec, y * _vec, z * _vec);
	}
	Vector3 operator/(const float& _vec) {
		return Vector3(x / _vec, y / _vec, z / _vec);
	}

	Vector3& operator=(const Vector3& _vec) {
		this->x = _vec.x; this->y = _vec.y; this->z = _vec.z; return *this;
	}

	Vector3& operator+=(const Vector3& _vec) {
		this->x += _vec.x;
		this->y += _vec.y;
		this->z += _vec.z;
		return *this;
	}
	Vector3& operator-=(const Vector3& _vec) {
		this->x -= _vec.x;
		this->y -= _vec.y;
		this->z -= _vec.z;
		return *this;
	}
	Vector3& operator*=(const Vector3& _vec) {
		this->x *= _vec.x;
		this->y *= _vec.y;
		this->z *= _vec.z;
		return *this;
	}
	Vector3& operator/=(const Vector3& _vec) {
		this->x /= _vec.x;
		this->y /= _vec.y;
		this->z /= _vec.z;
		return *this;
	}

	// ベクトル
	float GetLength() {
		DirectX::XMVECTOR vec;
		float ans;

		vec = DirectX::XMLoadFloat3(this);
		vec = DirectX::XMVector3Length(vec);

		DirectX::XMStoreFloat(&ans, vec);

		return ans;
	}

	// 内積
	static Vector3 Dot(const Vector3& _vec1, const Vector3& _vec2) {
		Vector3 ans;

		DirectX::XMStoreFloat3(&ans, DirectX::XMVector3Dot(XMLoadFloat3(&_vec1), DirectX::XMLoadFloat3(&_vec2)));

		return ans;
	}

	// 外積
	static Vector3 Cross(const Vector3& _vec1, const Vector3& _vec2) {
		Vector3 ans;

		DirectX::XMStoreFloat3(&ans, DirectX::XMVector3Cross(XMLoadFloat3(&_vec1), DirectX::XMLoadFloat3(&_vec2)));

		return ans;
	}

	Vector3 GetNormal() {
		Vector3 ans;

		DirectX::XMStoreFloat3(&ans, DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(this)));

		return ans;
	}
	float *GetPtr() { return &x; }

	static float Interval(const Vector3& _vec1, const Vector3& _vec2) {
		Vector3 vec1= _vec1, vec2= _vec2;
		const Vector3 diff = vec1 - vec2;
		float ansXY, ans;

		ansXY = sqrt(diff.x*diff.x + diff.y*diff.y);
		ans = sqrt(diff.z*diff.z + ansXY * ansXY);

		return ans;
	}
};

class Vector4 :public DirectX::XMFLOAT4 {
public:
	Vector4() { x = 0.f, y = 0.f, z = 0.f, w = 0.f; }
	Vector4(float _x, float _y) {
		x = _x, y = _y; z = z; ; w = w;
	}
	Vector4(float _x, float _y, float _z) { x = _x, y = _y; z = _z; ; w = w; }
	Vector4(float _x, float _y, float _z, float _w) { x = _x, y = _y; z = _z; w = _w; }
	Vector4(Vector3 _vec3) { x = _vec3.x, y = _vec3.y; z = _vec3.z; }

	static Vector4 Right() { return Vector4(1, 0, 0, 0); }
	static Vector4 Up() { return Vector4(0, 1, 0, 0); }
	static Vector4 Front() { return Vector4(0, 0, 1, 0); }

	//各種オペレータ対応
	Vector4 operator+(const Vector4 &_vec) {
		return Vector4(x + _vec.x, y + _vec.y, z + _vec.z, w + _vec.w);
	}
	Vector4 operator-(const Vector4 &_vec) {
		return Vector4(x - _vec.x, y - _vec.y, z - _vec.z, w - _vec.w);
	}
	Vector4 operator*(const Vector4 &_vec) {
		return Vector4(x * _vec.x, y * _vec.y, z * _vec.z, w * _vec.w);
	}
	Vector4 operator/(const Vector4 &_vec) {
		return Vector4(x / _vec.x, y / _vec.y, z / _vec.z, w / _vec.w);
	}
	float *GetPtr() { return &x; }
};

}  // math