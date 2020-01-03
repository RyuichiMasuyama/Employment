#pragma once

#pragma comment (lib,"winmm.lib")

#include <Windows.h>
#include <mmsystem.h>
#include <Singleton.h>
#include <memory>

#ifdef DIRECTX11
#include "MyDirectXMath.h"
#endif

namespace mslib {

class FpsManager :public pattern::Singleton<FpsManager> {
private:
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

public:
	FpsManager();

	~FpsManager() = default; // デストラクタを非インライン化;

	void Update();

	//固定フレームのフラグ
	bool GetFixedFlag() { return m_fixed_flag; }

	float GetDeltaTime() { return m_delta_time; };
};

}