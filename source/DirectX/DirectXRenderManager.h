#pragma once

#include "./DirectX/DirectX11Manager.h"
#include "./MyDirectXMath.h"
#include "./renderer/RenderObject.h"
#include "./Renderer/RenderTerget.h"
#include <Singleton.h>
#include <list>
#include <unordered_map>
#include <memory>

//�O���錾
namespace mslib {
namespace shader {
struct ShaderResource;
class VertexShaderManager;
class PixelShaderManager;
class GeometryShaderManager;
class ShaderWark;
}
namespace directx {
class BufferCreater;

}
namespace texture {
class TextureLoader;
}
}
//
//namespace mslib{
//namespace render {
//
//struct PostEffectData{
//	// Gauss�G�t�F�N�g
//	bool GaussFlag;
//	float GaussPower;
//
//	// �u���[���G�t�F�N�g
//	bool BloomFlag;
//	float BloomPower;
//};
//
//}
//}

namespace mslib {
namespace directx {

enum RENDER_MODEL_NAME :unsigned int;
//
//class DirectXRender;
//class DirectXRenderWork;
//class DirectXRenderObject;
//class DirectXRenderCommand;
//class RenderWarkPackage;
//class DirectXRenderObjectWarehouse;


//�����_�����O�����I�u�W�F�N�g�N���X
//���b�V�����̂ݕێ�			
//class DirectXRenderObject {
//private:
//	VertexBuffer m_vertex_buffer;
//	IndexBuffer m_index_buffer;
//	render::MyMesh m_mesh;
//	shader::ShaderResource m_shaderResource;
//
//public:
//	// �����_�[�I�u�W�F�N�g
//	// ���݁A�V�F�[�_�[�̃f�[�^��cpp�œ��͂���
//	// ���̂��߁A�R���X�g���N�^�Őݒ肹���镉���Ȃ�
//	// ����A�}�e���A���̃��[�h�ƂƂ��ɃV�F�[�_�[��
//	// �t�@�C���������[�h����
//	DirectXRenderObject(
//		std::string	_vs = "null",
//		std::string	_ps = "null"
//	);
//	~DirectXRenderObject() = default;
//
//	//���̑��V�F�[�_�[�̐ݒ�
//	void SetGeometory(std::string	_gs);
//	void SetHullDomainShader(std::string	_ds, std::string	_hs);
//
//	void SetVertexBuffer(ID3D11Buffer*_buffer) { m_vertex_buffer.Attach(_buffer); };
//	void SetIndexBuffer(ID3D11Buffer*_buffer) { m_index_buffer.Attach(_buffer); };
//
//	mslib::directx::VertexBuffer GetVertexBuffer() { return m_vertex_buffer; }
//	mslib::directx::IndexBuffer GetIndexBuffer() { return m_index_buffer; }
//
//	render::MyMesh* GetMesh() { return &m_mesh; }
//
//	void LoadModelData(std::string _modelName,std::string _hashName);
//};
//
//class DirectXRenderObjectLoder {
//public:
//	DirectXRenderObjectLoder(
//		 directx::ShaderWark* _shader_wark, DirectXRenderObjectWarehouse*_directx_render_object_warehouse
//	);
//	~DirectXRenderObjectLoder();
//
//	void LoadRenderObjectTest();
//
//private:
//	shader::VertexShaderManager * m_vertex_shader_manager;
//	shader::PixelShaderManager * m_pixel_shader_manager;
//	shader::GeometryShaderManager * m_geometry_shader_manager;
//	DirectXRenderObjectWarehouse* m_directx_render_object_warehouse;
//
//	std::unique_ptr < directx::BufferCreater > m_buffer_creater;
//
//	void CreateVertexBuffer(unsigned int stride, unsigned int vertexnum, void* vertexdata, ID3D11Buffer** pVertexBuffer);
//	void CreateIndexBuffer(unsigned int indexnum, void* indexdata, ID3D11Buffer** pIndexBuffer);
//
//	template<class T>
//	ID3D11Buffer* CreateVertexBuffer(T*_vertex_data, UINT _vertex_num) {
//		//���_�o�b�t�@�쐬
//		D3D11_BUFFER_DESC buffer_desc;
//		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
//		buffer_desc.ByteWidth = sizeof(T) * _vertex_num;
//		buffer_desc.Usage = D3D11_USAGE_DEFAULT;
//		buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//		buffer_desc.CPUAccessFlags = 0;
//
//		D3D11_SUBRESOURCE_DATA subresource_data;
//		ZeroMemory(&subresource_data, sizeof(subresource_data));
//		subresource_data.pSysMem = _vertex_data;
//
//		ID3D11Buffer* buffer;
//		if (FAILED(m_device->CreateBuffer(&buffer_desc, &subresource_data, &buffer))) {
//			return nullptr;
//		}
//		return buffer;
//	};
//
//	//ID3D11Buffer* CreateIndexBuffer(UINT* Index, UINT IndexNum);
//
//};
//
//class DirectXRenderObjectWarehouse {
//private:
//	std::unordered_map<std::string, std::shared_ptr<DirectXRenderObject>> m_directx_render_object;
//
//public:
//	void PushRenderObject(std::shared_ptr<DirectXRenderObject> _render_object, const std::string& render_name) { m_directx_render_object[render_name] = _render_object; };
//	std::weak_ptr<DirectXRenderObject> OutRenderObject(const std::string& _render_model_name) { return m_directx_render_object[_render_model_name]; };
//
//};
//
////�����_�����O�̃R�}���h�N���X
//class DirectXRenderCommand final {
//	friend DirectXRenderObject;
//
//public:
//	DirectXRenderCommand(const std::string &_render_model_name, const math::Matrix &_matrix) :
//		m_render_model_name(_render_model_name), m_matrix(_matrix) {};
//
//	//	const RENDER_MODEL_NAME& GetRenderModelName() { return m_render_model_name; };
//
//	//private:
//		//const���Ă邩��public�ł悭�ˁH
//	const std::string m_render_model_name;
//	const math::Matrix m_matrix;
//
//};

////�`���Ƃ����郌���_�����O�N���X
//class DirectXRenderWork {
//private:
//	//�R���X�^���g�o�b�t�@���M�p�o�b�t�@
//	mslib::directx::Device m_device;
//
//	//�`��p�f�o�C�X
//	mslib::directx::DeviceContext m_device_context;
//
//	DirectXRenderObjectWarehouse* m_directx_render_object_warehouse;
//
//	mslib::directx::DepthStencilView m_depth;
//public:
//	DirectXRenderWork(mslib::directx::Device _device,
//		mslib::directx::DeviceContext _device_context,
//		mslib::directx::DepthStencilView _depth,
//		DirectXRenderObjectWarehouse* _directx_render_object_warehouse)
//		:m_device(_device),
//		m_device_context(_device_context),
//		m_depth(_depth),
//		m_directx_render_object_warehouse(_directx_render_object_warehouse) {
//	}
//
//	void RendBefor(mslib::directx::RenderTargetView _renderTergetView);
//	void RendAfter(mslib::directx::ShaderTexture _renderTergetView);
//	void Draw(std::unique_ptr<DirectXRenderCommand> &_render_command);
//
//	void DrawQuadLast();
//
//};

enum RENDER_MODEL_NAME :unsigned int {
	RENDER_MODEL_POLYGON,
	RENDER_MODEL_DRAGON,
	RENDER_MODEL_MAX
};

class DirectXRender  {
private:
	// 1�D���ׂẴJ����������������
	// 2�D�e��t���邽�߂ɁA��ɃV���h�E�}�b�v�p�̃J�����������_�����O����
	// 3�D���C���J�����Ŏg�p����T�u�J�����������_�����O����
	// 4�D���C���J�����������_�����O����
	// 5�D�|�X�g�G�t�F�N�g��������
	// 6�D�I������������

	// RenderTerget���K�v
	// 

public:
	DirectXRender() {}

	void Initialize() {}

	void Render() {


		//int i = 0;
		//for (auto itr : mslib::render::RenderTergetManager::GetInstance().GetRenderTergets()) {
		//	m_directx_render_wark->RendBefor(itr->GetRenderTergetView());
		//	for (auto& buf : m_command_list) {
		//		m_directx_render_wark->Draw(buf);
		//	}
		//	i++;
		//}
		//m_command_list.clear();
	}

	void RenderQuad() {
		//int i = 0;
		//auto effectComand = m_postEffectCommnd.begin();
		//for (auto itr : mslib::render::RenderTergetManager::GetInstance().GetRenderTergets()) {
		//	itr->SetShaderResorce(i);
		//	//m_directx_render_wark->DrawPostEffect(*effectComand);
		//	m_directx_render_wark->DrawQuadLast();
		//	i++;
		//	//effectComand++;
		//}
	}
};

}
}
