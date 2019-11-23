#pragma once

#pragma comment (lib,"winmm.lib")

#include <Windows.h>
#include <mmsystem.h>
#include <memory>

#include "./DirectX/DirectX11Manager.h"
#include "MyDirectXMath.h"

class FpsManager {
private:
	struct ConstantBufferTime {
		math::Vector4 time;
		math::Vector4 delta_time;
	};

	//コンスタントバッファ
	mslib::directx::ConstantBuffer m_constant_buffer;

	//デバイス
	mslib::directx::Device m_device;

	//デバイスコンテキスト
	mslib::directx::DeviceContext m_device_context;

	LARGE_INTEGER m_counter;
	LONGLONG m_old_counter;
	LONGLONG m_start_timer;
	LONGLONG m_end_timer;

	double m_freq;

	bool m_fixed_flag;

	//固定フレームの分数
	double m_fixed_time_fraction;
	
	//固定フレームの母数
	double m_fixed_time_parameter;

	//可変フレームにおけるアプリ起動からの経過時間
	float m_time;

	//可変フレームにおける時間の経過
	float m_delta_time;

	//FPS計算系のアップデート
	void FpsUpdate();

	//コンスタントバッファ送信用アップデート
	void SendConstantBufferUpdate();

public:// bar.h
	//FpsManager & operator=(const FpsManager& bar) = default;  // <- またcpp内で適切に実装してやる必要がある
	FpsManager(mslib::directx::DirectX11Manager*_directx);

	~FpsManager(); // デストラクタを非インライン化;

	void Update();

	//固定フレームのフラグ
	bool GetFixedFlag() { return m_fixed_flag; }

	float GetDeltaTime() { return m_delta_time; };
};