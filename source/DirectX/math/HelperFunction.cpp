#include "HelperFunction.h"
#include <stdlib.h>

using namespace DirectX;

/*------------------------
ワールド変換行列を作る
--------------------------*/
void DX11MakeWorldMatrix(XMFLOAT4X4& inoutmat, XMFLOAT3& angle, XMFLOAT3& trans)
{
	ALIGN16 XMMATRIX mat, matx, maty, matz, mattrans;

	matx = XMMatrixRotationX((angle.x*XM_PI) / 180.0f);
	maty = XMMatrixRotationY((angle.y*XM_PI) / 180.0f);
	matz = XMMatrixRotationZ((angle.z*XM_PI) / 180.0f);
	mattrans = XMMatrixTranslation(trans.x, trans.y, trans.z);

	mat = matx * maty*matz*mattrans;

	XMStoreFloat4x4(&inoutmat, mat);
}

/*------------------------
３次元ベクトル×行列
--------------------------*/
void DX11Vec3MulMatrix(DirectX::XMFLOAT3& outvec, const DirectX::XMFLOAT3& invec, const DirectX::XMFLOAT4X4& mat) {

	ALIGN16 XMMATRIX mtx;
	ALIGN16 XMVECTOR inv;
	ALIGN16 XMVECTOR outv;

	mtx = XMLoadFloat4x4(&mat);
	inv = XMLoadFloat3(&invec);

	outv = XMVector3TransformCoord(inv, mtx);

	XMStoreFloat3(&outvec, outv);
}

/*------------------------
外積を計算する
--------------------------*/
void DX11Vec3Cross(DirectX::XMFLOAT3& outvec, DirectX::XMFLOAT3& invec1, DirectX::XMFLOAT3& invec2) {

	ALIGN16 XMVECTOR inv1;
	ALIGN16 XMVECTOR inv2;
	ALIGN16 XMVECTOR outv;

	inv1 = XMLoadFloat3(&invec1);
	inv2 = XMLoadFloat3(&invec2);

	outv = XMVector3Cross(inv1, inv2);

	XMStoreFloat3(&outvec, outv);
}

/*------------------------
内積を計算する
--------------------------*/
void DX11Vec3Dot(float& dot, const DirectX::XMFLOAT3& invec1, const DirectX::XMFLOAT3& invec2) {

	ALIGN16 XMVECTOR inv1;
	ALIGN16 XMVECTOR inv2;
	ALIGN16 XMVECTOR outv;

	inv1 = XMLoadFloat3(&invec1);
	inv2 = XMLoadFloat3(&invec2);

	outv = XMVector3Dot(inv1, inv2);

	XMFLOAT3 outfloat;

	XMStoreFloat3(&outfloat, outv);

	dot = outfloat.x;
}


/*------------------------
正規化する
--------------------------*/
void DX11Vec3Normalize(DirectX::XMFLOAT3& outvec, DirectX::XMFLOAT3& invec) {

	ALIGN16 XMVECTOR inv;
	ALIGN16 XMVECTOR outv;

	inv = XMLoadFloat3(&invec);

	outv = DirectX::XMVector3Normalize(inv);

	XMStoreFloat3(&outvec, outv);
}

/*------------------------
単位行列にする
--------------------------*/
void DX11MtxIdentity(DirectX::XMFLOAT4X4& mat) {

	ALIGN16 XMMATRIX mtx;

	mtx = XMMatrixIdentity();

	XMStoreFloat4x4(&mat, mtx);
}

/*------------------------
行列からクオータニオンを生成する
--------------------------*/
void DX11GetQtfromMatrix(const XMFLOAT4X4& mat, XMFLOAT4& qt) {

	ALIGN16 XMMATRIX mtx;
	ALIGN16 XMVECTOR outvec;

	mtx = XMLoadFloat4x4(&mat);

	outvec = XMQuaternionRotationMatrix(mtx);

	XMStoreFloat4(&qt, outvec);
}

/*------------------------
指定軸を中心に回転したクオータニオンを生成する
--------------------------*/
void DX11QtRotationAxis(XMFLOAT4& qt, XMFLOAT4& axis, float angle) {

	ALIGN16 XMVECTOR outqt;
	ALIGN16 XMVECTOR axisvec;

	axisvec = XMLoadFloat4(&axis);
	
	outqt = XMQuaternionRotationAxis(axisvec, DirectX::XMConvertToRadians(angle));

	XMStoreFloat4(&qt, outqt);
}

/*------------------------
クオータニオンの掛け算
--------------------------*/
void DX11QtMul(XMFLOAT4& outqt, const XMFLOAT4& qt1, const XMFLOAT4& qt2) {
	ALIGN16 XMVECTOR qtvec1;
	ALIGN16 XMVECTOR qtvec2;
	ALIGN16 XMVECTOR outqtvec;

	qtvec1 = XMLoadFloat4(&qt1);
	qtvec2 = XMLoadFloat4(&qt2);

	outqtvec = XMQuaternionMultiply(qtvec1, qtvec2);

	XMStoreFloat4(&outqt, outqtvec);
}

/*------------------------
クオータニオンから行列を生成
--------------------------*/
void DX11MtxFromQt(XMFLOAT4X4& outmtx, const XMFLOAT4& qt) {

	ALIGN16 XMMATRIX mtx;
	ALIGN16 XMVECTOR qtvec;
	qtvec = XMLoadFloat4(&qt);

	mtx = XMMatrixRotationQuaternion(qtvec);

	XMStoreFloat4x4(&outmtx, mtx);

}

/*------------------------
　　転置する
  --------------------------*/
void DX11MtxTranspose(XMFLOAT4X4& outmtx, const XMFLOAT4X4& inmtx) {

	ALIGN16 XMMATRIX mtx;
	ALIGN16 XMMATRIX inmmtx;
	inmmtx = XMLoadFloat4x4(&inmtx);

	mtx = XMMatrixTranspose(inmmtx);

	XMStoreFloat4x4(&outmtx, mtx);

}



/*------------------------
クオータニオンのノーマライズ
--------------------------*/
void DX11QtNormalize(XMFLOAT4& inqt, XMFLOAT4& outqt) {

	ALIGN16 XMVECTOR qtoutvec;
	ALIGN16 XMVECTOR qtvec;
	qtvec = XMLoadFloat4(&inqt);

	qtoutvec = XMQuaternionNormalize(qtvec);

	XMStoreFloat4(&outqt, qtoutvec);

}

/*------------------------
ベクトルの長さを求める
--------------------------*/
void DX11Vec4Length(XMFLOAT4& vec, float& length) {

	ALIGN16 XMVECTOR outvec;
	ALIGN16 XMVECTOR invec;
	XMFLOAT4 l;

	invec = XMLoadFloat4(&vec);

	outvec = XMVector3Length(invec);

	XMStoreFloat4(&l, outvec);

	length = l.x;
}

/*------------------------
ベクトルの長さを求める
--------------------------*/
void DX11Vec3Length(XMFLOAT3& vec, float& length) {

	ALIGN16 XMVECTOR outvec;
	ALIGN16 XMVECTOR invec;
	XMFLOAT4 l;

	l.x = vec.x;
	l.y = vec.y;
	l.z = vec.z;
	l.w = 0.0f;

	invec = XMLoadFloat4(&l);

	outvec = XMVector3Length(invec);

	XMStoreFloat4(&l, outvec);

	length = l.x;
}

/*------------------------
２点間の距離を求める
--------------------------*/
void DX11p2pLength(const XMFLOAT3& p1, const XMFLOAT3& p2, float& length) {

	XMFLOAT4 vec4;

	vec4.x = p1.x - p2.x;
	vec4.y = p1.y - p2.y;
	vec4.z = p1.z - p2.z;
	vec4.w = 1.0f;

	DX11Vec4Length(vec4, length);
}

/*------------------------
平行移動行列を作成する
--------------------------*/
void DX11MtxTranslation(const XMFLOAT3& trans, XMFLOAT4X4& matrix) {
	ALIGN16 XMMATRIX mattrans;

	mattrans = XMMatrixTranslation(trans.x, trans.y, trans.z);

	XMStoreFloat4x4(&matrix, mattrans);
}

/*------------------------
スラープ補間
--------------------------*/
void DX11QtSlerp(const XMFLOAT4& fromqt, const XMFLOAT4& toqt, float t, XMFLOAT4& ansqt) {

	ALIGN16 XMVECTOR infromqt;
	ALIGN16 XMVECTOR intoqt;
	ALIGN16 XMVECTOR qt;

	infromqt = XMLoadFloat4(&fromqt);
	intoqt = XMLoadFloat4(&toqt);

	qt = XMQuaternionSlerp(infromqt, intoqt, t);

	XMStoreFloat4(&ansqt, qt);
}

/*------------------------
単位クオータニオンにする
--------------------------*/
void DX11QtIdentity(XMFLOAT4& qt) {

	ALIGN16 XMVECTOR outqt;

	outqt = XMQuaternionIdentity();

	XMStoreFloat4(&qt, outqt);

}

/*------------------------
指定軸で回転する行列を作成する（angleは、度数法）
--------------------------*/
void DX11MtxRotationAxis(const XMFLOAT3& axis, float angle, XMFLOAT4X4& outmtx) {

	ALIGN16 XMVECTOR vaxis;
	ALIGN16 XMMATRIX mtx;

	// 軸を同時座標に変換
	XMFLOAT4 axis4 = { axis.x,axis.y,axis.z,0 };
	vaxis = XMLoadFloat4(&axis4);

	// 度数法をラジアンに変換
	angle = (angle * XM_PI) / 180.0f;

	// 指定軸を中心に回転する行列を作成する
	mtx = XMMatrixRotationAxis(vaxis, angle);

	XMStoreFloat4x4(&outmtx, mtx);
}

/*------------------------
X軸回転行列を求める
--------------------------*/
void DX11MtxRotationX(float angle, XMFLOAT4X4& outmtx) {

	ALIGN16 XMMATRIX mtx;

	// 度数法をラジアンに変換
	angle = (angle * XM_PI) / 180.0f;

	// X軸を中心に回転する行列を作成する
	mtx = XMMatrixRotationX(angle);

	XMStoreFloat4x4(&outmtx, mtx);
}

/*------------------------
Y軸回転行列を求める
--------------------------*/
void DX11MtxRotationY(float angle, XMFLOAT4X4& outmtx) {

	ALIGN16 XMMATRIX mtx;

	// 度数法をラジアンに変換
	angle = (angle * XM_PI) / 180.0f;

	// Y軸を中心に回転する行列を作成する
	mtx = XMMatrixRotationY(angle);

	XMStoreFloat4x4(&outmtx, mtx);
}

/*------------------------
Z軸回転行列を求める
--------------------------*/
void DX11MtxRotationZ(float angle, XMFLOAT4X4& outmtx) {

	ALIGN16 XMMATRIX mtx;

	// 度数法をラジアンに変換
	angle = (angle * XM_PI) / 180.0f;

	// 指定軸を中心に回転する行列を作成する
	mtx = XMMatrixRotationZ(angle);

	XMStoreFloat4x4(&outmtx, mtx);
}


/*------------------------
ハルトン数列を計算
入力
unsigned int no : 何番目か
unsined base : 基底

戻り値
　　ハルトン数列値
  --------------------------*/
float haltonseq(unsigned int no, unsigned int base) {

	unsigned int i = no;
	float result = 0;
	float f = 1;

	while (i > 0) {
		f = f / base;
		result = result + f * (i % base);
		i = i / base;
	}

	return result;
}

/*------------------------
ランダムな数を受け取る
--------------------------*/
int Random() {
	return rand();
}

/*------------------------
ランダムな範囲内の数を受け取る
--------------------------*/
int Random(int min, int max) {
	int range = max - min;
	int ran = rand() % range;

	ran += min;

	return ran;
}