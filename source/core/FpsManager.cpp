#include "./FpsManager.h"
#include "./DirectX/SubResourceSendManager.h"

namespace mslib {

void FpsManager::FpsUpdate() {
	//前回の時間を取得
	m_old_counter = m_counter.QuadPart;

	//現在の時間を取得
	QueryPerformanceCounter(&m_counter);

	//経過時間の取得
	m_delta_time = static_cast<const float>((m_counter.QuadPart - m_old_counter) / m_freq);

	//経過時間を加算
	m_fixed_time_fraction += m_delta_time;
	m_time += m_delta_time;

	//60FPSを規定
	m_fixed_flag = m_fixed_time_fraction > 1.0 / m_fixed_time_parameter;
	if (m_fixed_flag) {
		m_fixed_time_fraction = 0.0;
	}
}

FpsManager::FpsManager() {
	QueryPerformanceCounter(&m_counter);

	m_old_counter = m_counter.QuadPart;		//生成時の時刻(クロック数)を取得

	LARGE_INTEGER frep;
	QueryPerformanceFrequency(&frep);		//	1秒当たりクロック数を取得
	m_freq = (double)frep.QuadPart;

	//タイマーの初期時間設定
	m_start_timer = m_end_timer = 0;

	//固定フレームレームの分数設定
	m_fixed_time_fraction = 0.0;

	//固定フレームレートの母数設定
	m_fixed_time_parameter = 60.0;
}

void FpsManager::Update() {

	//FPSアップデート
	FpsUpdate();

	if (GetFixedFlag()) {
		directx::SubResourceSendManager::GetInstance().SetTimeBuffer(
			math::Vector4(m_time, m_time / 2.f, m_time / 4.f, m_time / 8.f),
			math::Vector4(m_delta_time, m_delta_time / 2.f, m_delta_time / 4.f, m_delta_time / 8.f)
		);
	}
}

}