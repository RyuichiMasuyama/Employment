#pragma once

#include "Vector.h"
//#include "Quaternion.h"

namespace math{
class Matrix :public DirectX::XMFLOAT4X4 {
public:

	Matrix() {
		_11 = 1, _12 = 0, _13 = 0, _14 = 0,
			_21 = 0, _22 = 1, _23 = 0, _24 = 0,
			_31 = 0, _32 = 0, _33 = 1, _34 = 0,
			_41 = 0, _42 = 0, _43 = 0, _44 = 1;

	}

	Matrix(
		float __11, float __12, float __13, float __14,
		float __21, float __22, float __23, float __24,
		float __31, float __32, float __33, float __34,
		float __41, float __42, float __43, float __44)	{

		_11 = __11, _12 = __12, _13 = __13, _14 = __14,
		_21 = __21, _22 = __22, _23 = __23, _24 = __24,
		_31 = __31, _32 = __32, _33 = __33, _34 = __34,
		_41 = __41, _42 = __42, _43 = __43, _44 = __44;
	}


	static Matrix Identity() {
		Matrix ident;
		return ident;
	}

	static void Identity(XMFLOAT4X4 & _mat) {
		Matrix ident;
		_mat = ident;
	}

	Matrix& operator*(const XMFLOAT4X4 & _mat) {

		DirectX::XMMATRIX mat1, mat2;
		Matrix ans;

		mat1 = DirectX::XMLoadFloat4x4(this);
		mat2 = DirectX::XMLoadFloat4x4(&_mat);

		mat2 = XMMatrixMultiply(mat1, mat2);

		XMStoreFloat4x4(&ans, mat2);

		return ans;
	}

	Matrix& operator*=(const XMFLOAT4X4 & _mat) {

		DirectX::XMMATRIX mat1, mat2;
		Matrix ans;

		mat1 = DirectX::XMLoadFloat4x4(this);
		mat2 = DirectX::XMLoadFloat4x4(&_mat);

		mat2 = XMMatrixMultiply(mat1, mat2);

		XMStoreFloat4x4(&ans, mat2);

		*this = ans;

		return *this;
	}

	DirectX::XMMATRIX ToMATRIX() { return  DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(this)); }

	/*
		Matrix& operator*(const Quaternion& qua) {
			Matrix mat = *this;

			DX11MtxFromQt(mat, qua);

			return mat;
		}

		Matrix& operator*=(const Quaternion& qua) {

			DX11MtxFromQt(*this, qua);
			DirectX::XMMATRIX matrix = DirectX::XMLoadFloat4x4(this) * DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&qua));
			DirectX::XMStoreFloat4x4(this, matrix);

			return *this;
	}*/

	void Scaling(const float& _x, const float& _y, const float& _z) {
		DirectX::XMMATRIX mat;
		Matrix ans;

		mat = DirectX::XMMatrixScaling(_x, _y, _z);

		XMStoreFloat4x4(&ans, mat);

		*this = ans;
	}

	void Scaling(const math::Vector3& _scal) {
		DirectX::XMMATRIX mat;
		Matrix ans;

		mat = DirectX::XMMatrixScaling(_scal.x, _scal.y, _scal.z);

		XMStoreFloat4x4(&ans, mat);

		*this = ans;
	}

	void MovePosition(const float& _x, const float& _y, const float& _z) {
		_41 = _x;
		_42 = _y;
		_43 = _z;
	}

	void MovePosition(const math::Vector3& _pos) {
		_41 = _pos.x;
		_42 = _pos.y;
		_43 = _pos.z;
	}

	math::Vector3 GetRight() {
		return math::Vector3(_11, _12, _13);
	}

	math::Vector3 GetUp() {
		return math::Vector3(_21, _22, _23);
	}

	math::Vector3 GetFront() {
		return math::Vector3(_31, _32, _33);
	}

	static Matrix Inverse(const Matrix& qua) {
		DirectX::XMMATRIX mat, matans;
		Matrix ans;

		mat = XMLoadFloat4x4(&qua);

		matans = DirectX::XMMatrixInverse(nullptr, mat);

		XMStoreFloat4x4(&ans, matans);

		return ans;
	}

};
}