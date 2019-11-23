#pragma once

#include "./DirectX/math/HelperFunction.h"
#include "./Vector.h"
#include "./Matrix.h"
namespace math {
class Quaternion :public DirectX::XMFLOAT4 {
private:


public:
	Quaternion() {
		this->x = 0.f;
		this->y = 0.f;
		this->z = 0.f;
		this->w = 1.f;
	}

	void Rotate(float _x, float _y, float _z) {

		Vector4  gt;
		DirectX::XMFLOAT4X4 _mat;
		DX11GetQtfromMatrix(_mat, gt);
		DirectX::XMStoreFloat4x4(&_mat, DirectX::XMMatrixIdentity());

		Vector4 gtx, gty, gtz;
		Vector4 axx(_mat._11, _mat._12, _mat._13);
		Vector4 axy(_mat._21, _mat._22, _mat._23);
		Vector4 axz(_mat._31, _mat._32, _mat._33);

		DX11QtRotationAxis(gtx, axx, _x);
		DX11QtRotationAxis(gty, axy, _y);
		DX11QtRotationAxis(gtz, axz, _z);

		Quaternion temp1, temp2, temp3;

		DX11QtMul(temp1, gt, gtx);
		DX11QtMul(temp2, gty, gtz);
		DX11QtMul(temp3, temp1, temp2);

		DX11QtNormalize(temp3, temp3);


		*this = temp3;

	}

	void Rotate(Vector3 _rot) {

		Vector4  gt;
		Matrix _ans;

		DirectX::XMStoreFloat4x4(&_ans, DirectX::XMMatrixIdentity());

		DX11GetQtfromMatrix(_ans, gt);

		Vector4 gtx, gty, gtz;
		Vector4 axx = Vector4::Right();
		Vector4 axy = Vector4::Up();
		Vector4 axz = Vector4::Front();

		DX11QtRotationAxis(gtx, axx, _rot.x);
		DX11QtRotationAxis(gty, axy, _rot.y);
		DX11QtRotationAxis(gtz, axz, _rot.z);

		Quaternion temp1, temp2, temp3;

		DX11QtMul(temp1, gt, gtx);
		DX11QtMul(temp2, gty, gtz);
		DX11QtMul(temp3, temp1, temp2);

		DX11QtNormalize(temp3, temp3);

		*this = temp3;
	}

	void AddRotate(float _x, float _y, float _z) {

		Vector4  gt;
		DirectX::XMFLOAT4X4 _mat;
		DX11GetQtfromMatrix(_mat, gt);

		Vector4 gtx, gty, gtz;
		Vector4 axx(_mat._11, _mat._12, _mat._13);
		Vector4 axy(_mat._21, _mat._22, _mat._23);
		Vector4 axz(_mat._31, _mat._32, _mat._33);

		DX11QtRotationAxis(gtx, axx, _x);
		DX11QtRotationAxis(gty, axy, _y);
		DX11QtRotationAxis(gtz, axz, _z);

		Quaternion temp1, temp2, temp3;

		DX11QtMul(temp1, gt, gtx);
		DX11QtMul(temp2, gty, gtz);
		DX11QtMul(temp3, temp1, temp2);

		DX11QtNormalize(temp3, temp3);

		*this *= temp3;

	}

	void AddRotate(Vector3 _rot) {

		Vector4  gt;

		_rot.x = DirectX::XMConvertToRadians(_rot.x);
		_rot.y = DirectX::XMConvertToRadians(_rot.y);
		_rot.z = DirectX::XMConvertToRadians(_rot.z);

		DirectX::XMFLOAT4X4 _ans;

		DirectX::XMStoreFloat4x4(&_ans, DirectX::XMMatrixIdentity());

		DX11GetQtfromMatrix(_ans, gt);

		Vector4 gtx, gty, gtz;
		Vector4 axx = Vector4::Right();
		Vector4 axy = Vector4::Up();
		Vector4 axz = Vector4::Front();

		DX11QtRotationAxis(gtx, axx, _rot.x);
		DX11QtRotationAxis(gty, axy, _rot.y);
		DX11QtRotationAxis(gtz, axz, _rot.z);

		Quaternion temp1, temp2, temp3;

		DX11QtMul(temp1, gt, gtx);
		DX11QtMul(temp2, gty, gtz);
		DX11QtMul(temp3, temp1, temp2);

		DX11QtNormalize(temp3, temp3);

		*this *= temp3;
	}

	Quaternion operator*(const Quaternion& _qua) {
		Quaternion ans;
		DirectX::XMStoreFloat4(&ans, DirectX::XMQuaternionMultiply(DirectX::XMLoadFloat4(this), DirectX::XMLoadFloat4(&_qua)));

		return ans;
	}

	Quaternion operator*=(const Quaternion& _qua) {
		Quaternion ans;
		DirectX::XMStoreFloat4(&ans, DirectX::XMQuaternionMultiply(DirectX::XMLoadFloat4(this), DirectX::XMLoadFloat4(&_qua)));
		*this = ans;

		return *this;
	}

	Matrix GetMatrix() {
		Matrix ans;
		DX11MtxFromQt(ans, *this);
		return ans;
	}
};

}  // math
