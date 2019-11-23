#pragma once

#include	<DirectXMath.h>

//一部鈴木先生のソースコピー

// 16バイトにアラインメントする。
#define ALIGN16 _declspec(align(16))

void DX11MakeWorldMatrix(DirectX::XMFLOAT4X4& mat, DirectX::XMFLOAT3& angle, DirectX::XMFLOAT3& trans);
void DX11Vec3MulMatrix(DirectX::XMFLOAT3& outvec, const DirectX::XMFLOAT3& invec, const DirectX::XMFLOAT4X4& mat);
void DX11Vec3Cross(DirectX::XMFLOAT3& outvec, DirectX::XMFLOAT3& invec1, DirectX::XMFLOAT3& invec2);
void DX11Vec3Dot(float& dot, const DirectX::XMFLOAT3& invec1, const DirectX::XMFLOAT3& invec2);
void DX11Vec3Normalize(DirectX::XMFLOAT3& outvec, DirectX::XMFLOAT3& invec);
void DX11MtxIdentity(DirectX::XMFLOAT4X4& mat);
void DX11GetQtfromMatrix(const DirectX::XMFLOAT4X4& mat, DirectX::XMFLOAT4& qt);
void DX11QtRotationAxis(DirectX::XMFLOAT4& qt, DirectX::XMFLOAT4& axis, float angle);
void DX11QtMul(DirectX::XMFLOAT4& outqt, const DirectX::XMFLOAT4& qt1, const DirectX::XMFLOAT4& qt2);
void DX11MtxFromQt(DirectX::XMFLOAT4X4& outmtx, const DirectX::XMFLOAT4& qt);
void DX11QtNormalize(DirectX::XMFLOAT4& inqt, DirectX::XMFLOAT4& outqt);
void DX11Vec4Length(DirectX::XMFLOAT4& vec, float& length);
void DX11p2pLength(const DirectX::XMFLOAT3& p1, const DirectX::XMFLOAT3& p2, float& length);
void DX11MtxTranslation(const DirectX::XMFLOAT3& trans, DirectX::XMFLOAT4X4& matrix);
void DX11QtSlerp(const DirectX::XMFLOAT4& fromqt, const DirectX::XMFLOAT4& toqt, float t, DirectX::XMFLOAT4& ansqt);
void DX11QtIdentity(DirectX::XMFLOAT4& qt);
void DX11Vec3Length(DirectX::XMFLOAT3& vec, float& length);
void DX11MtxRotationAxis(const DirectX::XMFLOAT3& axis, float angle, DirectX::XMFLOAT4X4& outmtx);

void DX11MtxTranspose(DirectX::XMFLOAT4X4& outmtx, const DirectX::XMFLOAT4X4& inmtx);
void DX11MtxRotationX(float angle, DirectX::XMFLOAT4X4& outmtx);
void DX11MtxRotationY(float angle, DirectX::XMFLOAT4X4& outmtx);
void DX11MtxRotationZ(float angle, DirectX::XMFLOAT4X4& outmtx);
float haltonseq(unsigned int no, unsigned int base);
int Random();
int Random(int min, int max);
