#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <d3dcompiler.h>
#include <locale>
#include "./DirectX/DirectX11Manager.h"

//各種シェーダーのマネージャ
#include "MyDirectXVertexShader.h"
#include "MyDirectXPixelShader.h"
#include "MyDirectXGeometryShader.h"

#define SHADER_NAME_MAX 256

//前方宣言
namespace mslib {
namespace shader {
//シェーダをまとめたクラス
class ShaderResource {
public:
	directx::VertexShader	m_vertex_shader = nullptr;
	directx::InputLayout	m_input_layout = nullptr;
	directx::PixelShader	m_pixel_shader = nullptr;
	directx::GeometryShader m_geometry_shader = nullptr;
	directx::DomainShader	m_domain_shader = nullptr;
	directx::HullShader	m_hull_shader = nullptr;
};
}

namespace directx {
//シェーダーをコンパイルする関数
//鈴木先生のソースコード参考
//ジオメトリシェーダーなどに併用も可能確認(ZeroGram様ブログ参照)
HRESULT CompileShaderFromFile(const char * _file_name, LPCSTR _main_fanction_name, LPCSTR _shader_version, ID3DBlob** _compile_shader);

class BufferCreater {
public:
	BufferCreater(mslib::directx::Device _device) :m_device(_device) {}
	BufferCreater() :m_device(DirectX11Manager::GetInstance().GetDevice()) {}

	ID3D11Buffer* CreateConstantBuffer(UINT _byte_size);
	ID3D11Buffer* CreateIndexBuffer(UINT* Index, UINT IndexNum);

	template<class T>
	ID3D11Buffer* CreateVertexBuffer(T*_vertex_data, UINT _vertex_num) {
		//頂点バッファ作成
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.ByteWidth = sizeof(T) * _vertex_num;
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subresource_data;
		ZeroMemory(&subresource_data, sizeof(subresource_data));
		subresource_data.pSysMem = _vertex_data;

		ID3D11Buffer* buffer;
		if (FAILED(m_device->CreateBuffer(&buffer_desc, &subresource_data, &buffer))) {
			return nullptr;
		}
		return buffer;
	};

private:
	mslib::directx::Device m_device;
};


class ShaderWark {
private:
	shader::VertexShaderManager m_vertex_manager;
	shader::PixelShaderManager m_pixel_manager;
	shader::GeometryShaderManager m_geometry_manager;

	// ポストエフェクト専用
	std::unordered_map<std::string, mslib::directx::VertexShader> m_vertex_shader;
	std::unordered_map<std::string, mslib::directx::InputLayout> m_input_layout;
	std::unordered_map<std::string, mslib::directx::PixelShader> m_pixel_shader;

public:
	ShaderWark(mslib::directx::Device _device) :m_vertex_manager(_device), m_pixel_manager(_device), m_geometry_manager(_device) {};

	void Create();

	shader::VertexShaderManager* GetVertexShaderManager() { return &m_vertex_manager; };
	shader::PixelShaderManager* GetPixelShaderManager() { return &m_pixel_manager; };
	shader::GeometryShaderManager* GetGeometryShaderManager() { return &m_geometry_manager; };

};

}
}