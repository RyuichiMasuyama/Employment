#pragma once

#include "./DirectX/DirectX11Manager.h"
#include "./Math/Matrix.h"
#include "./DirectXRenderObject.h"
#include "./Singleton.h"
#include "./DirectX/DeviceGetter.h"
#include "./RenderTerget.h"
#include <list>
#include <unordered_map>
#include <memory>

//前方宣言
namespace mslib {
namespace shader {
class ShaderResource;
class VertexShaderManager;
class PixelShaderManager;
class GeometryShaderManager;
class ShaderWark;
}
namespace directx {
class BufferCreater;

}
namespace texture {
class TextureLoder;
}
}

namespace mslib{
namespace render {

struct PostEffectData{
	// Gaussエフェクト
	bool GaussFlag;
	float GaussPower;

	// ブルームエフェクト
	bool BloomFlag;
	float BloomPower;
};

}
}

namespace mslib {
namespace render {

enum RENDER_MODEL_NAME :unsigned int;

class DirectXRender;
class DirectXRenderWork;
class DirectXRenderObject;
class DirectXRenderCommand;
class RenderWarkPackage;
class DirectXRenderObjectWarehouse;

//レンダリングされるオブジェクトクラス
//メッシュ情報のみ保持			
class DirectXRenderObject :public mslib::directx::DeviceGetter {
private:
	//各種シェーダー
	std::unique_ptr<shader::ShaderResource> m_shader_resource;

	float m_materia_num;
	mslib::directx::VertexBuffer m_vertex_buffer;
	mslib::directx::IndexBuffer m_index_buffer;

public:
	//レンダーオブジェクト
	DirectXRenderObject(
		mslib::directx::VertexShader	_vertex_shader = nullptr,
		mslib::directx::InputLayout	_input_layout = nullptr,
		mslib::directx::PixelShader	_pixel_shader = nullptr
	);
	~DirectXRenderObject();

	///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////
	//			一時的なpublic変数
	//			なおさなきゃダメだよ
	///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////
	MyMesh m_mesh;
	///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////
	//			一時的なpublic変数
	//			なおさなきゃダメだよ
	///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////

	//その他シェーダーの設定
	void SetGeometory(mslib::directx::GeometryShader _geometry_shader);
	void SetHullDomainShader(mslib::directx::DomainShader	_domain_shader, mslib::directx::HullShader _hull_shader);
	std::unique_ptr<shader::ShaderResource>& GetShaderResources() { return m_shader_resource; };

	void SetVertexBuffer(ID3D11Buffer*_buffer) { m_vertex_buffer.Attach(_buffer); };
	void SetIndexBuffer(ID3D11Buffer*_buffer) { m_index_buffer.Attach(_buffer); };

	mslib::directx::VertexBuffer GetVertexBuffer() { return m_vertex_buffer; }
	mslib::directx::IndexBuffer GetIndexBuffer() { return m_index_buffer; }
};

class DirectXRenderObjectLoder {
public:
	DirectXRenderObjectLoder(
		mslib::directx::Device _device, directx::ShaderWark* _shader_wark, DirectXRenderObjectWarehouse*_directx_render_object_warehouse
		, mslib::texture::TextureLoder* _texture_loader
	);
	~DirectXRenderObjectLoder();

	void LoadRenderObjectTest();

private:
	mslib::directx::Device m_device;

	shader::VertexShaderManager * m_vertex_shader_manager;
	shader::PixelShaderManager * m_pixel_shader_manager;
	shader::GeometryShaderManager * m_geometry_shader_manager;
	DirectXRenderObjectWarehouse* m_directx_render_object_warehouse;
	mslib::texture::TextureLoder* m_texture_loader;

	std::unique_ptr < directx::BufferCreater > m_buffer_creater;

	void CreateVertexBuffer(unsigned int stride, unsigned int vertexnum, void* vertexdata, ID3D11Buffer** pVertexBuffer);
	void CreateIndexBuffer(unsigned int indexnum, void* indexdata, ID3D11Buffer** pIndexBuffer);

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

	//ID3D11Buffer* CreateIndexBuffer(UINT* Index, UINT IndexNum);

};

class DirectXRenderObjectWarehouse {
private:
	std::unordered_map<std::string, std::shared_ptr<DirectXRenderObject>> m_directx_render_object;

public:
	void PushRenderObject(std::shared_ptr<DirectXRenderObject> _render_object, const std::string& render_name) { m_directx_render_object[render_name] = _render_object; };
	std::weak_ptr<DirectXRenderObject> OutRenderObject(const std::string& _render_model_name) { return m_directx_render_object[_render_model_name]; };

};

//レンダリングのコマンドクラス
class DirectXRenderCommand final {
	friend DirectXRenderObject;

public:
	DirectXRenderCommand(const std::string &_render_model_name, const math::Matrix &_matrix) :
		m_render_model_name(_render_model_name), m_matrix(_matrix) {};

	//	const RENDER_MODEL_NAME& GetRenderModelName() { return m_render_model_name; };

	//private:
		//constついてるからpublicでよくね？
	const std::string m_render_model_name;
	const math::Matrix m_matrix;

};

class DirectXPostEffectRenderCommand final {
	friend DirectXRenderObject;

public:
	DirectXPostEffectRenderCommand(const PostEffectData& _postEffectData) : m_postEffectData(_postEffectData) {};

private:
	const PostEffectData m_postEffectData;
};


//描画作業をするレンダリングクラス
class DirectXRenderWork {
private:
	//コンスタントバッファ送信用バッファ
	mslib::directx::Device m_device;

	//描画用デバイス
	mslib::directx::DeviceContext m_device_context;

	DirectXRenderObjectWarehouse* m_directx_render_object_warehouse;

	mslib::directx::DepthStencilView m_depth;
public:
	DirectXRenderWork(mslib::directx::Device _device,
		mslib::directx::DeviceContext _device_context,
		mslib::directx::DepthStencilView _depth,
		DirectXRenderObjectWarehouse* _directx_render_object_warehouse)
		:m_device(_device),
		m_device_context(_device_context),
		m_depth(_depth),
		m_directx_render_object_warehouse(_directx_render_object_warehouse) {
	}

	void RendBefor(mslib::directx::RenderTargetView _renderTergetView);
	void RendAfter(mslib::directx::ShaderTexture _renderTergetView);
	void Draw(std::unique_ptr<DirectXRenderCommand> &_render_command);

	void DrawQuadLast();

	void DrawPostEffect(const std::unique_ptr<DirectXPostEffectRenderCommand> &_effectComand);
};

class RenderWarkPackage {
private:
	//Library::DirectXRenderWork m_directx_render_work;
	//Library::DirectXRenderObjectWarehouse m_direct_render_object_warehouse;

public:
	void Draw(render::DirectXRenderCommand* rend) {
		//m_directx_render_work.Draw(rend)
	}
};


enum RENDER_MODEL_NAME :unsigned int {
	RENDER_MODEL_POLYGON,
	RENDER_MODEL_DRAGON,
	RENDER_MODEL_MAX
};

class DirectXRender :public pattern::Singleton<DirectXRender> {
private:
	std::list<std::unique_ptr<DirectXRenderCommand>> m_command_list;
	std::list<std::unique_ptr<DirectXPostEffectRenderCommand>> m_postEffectCommnd;
	std::unique_ptr<render::DirectXRenderWork> m_directx_render_wark;

public:
	DirectXRender() {};

	void Initialize(mslib::directx::DirectX11Manager* _directx11_manager, render::DirectXRenderObjectWarehouse *_directx_render_object_warehouse) {
		m_directx_render_wark = std::make_unique<render::DirectXRenderWork>(_directx11_manager->GetDevice(),
			_directx11_manager->GetDeviceContext(),
			_directx11_manager->GetDepthStencilView(),
			_directx_render_object_warehouse);
	}

	void Draw(const std::string &_render_model_name, const math::Matrix &_matrix) {

		m_command_list.emplace_back(std::make_unique< render::DirectXRenderCommand>(_render_model_name, _matrix));
	}

	void DrawPostEffect(const render::PostEffectData& _data) {
		m_postEffectCommnd.emplace_back(std::make_unique< render::DirectXPostEffectRenderCommand>(_data));
	}

	void Render() {
		int i = 0;
		for (auto itr : mslib::render::RenderTergetManager::GetInstance().GetRenderTergets()) {
			m_directx_render_wark->RendBefor(itr->GetRenderTergetView());
			for (auto& buf : m_command_list) {
				m_directx_render_wark->Draw(buf);
			}
			i++;
		}
		m_command_list.clear();
	}

	void RenderQuad() {
		int i = 0;
		auto effectComand = m_postEffectCommnd.begin();
		for (auto itr : mslib::render::RenderTergetManager::GetInstance().GetRenderTergets()) {
			itr->SetShaderResorce(i);
			//m_directx_render_wark->DrawPostEffect(*effectComand);
			m_directx_render_wark->DrawQuadLast();
			i++;
			//effectComand++;
		}
	}
};

}
}
