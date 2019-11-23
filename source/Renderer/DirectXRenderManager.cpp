#include "DirectXRenderManager.h"
#include "./Shader/Shader.h"
#include "DirectXRenderObject.h"
#include "MyDirectXTransform.h"
#include "DirectX/DirectXTextureManager.h"
#include "./Shader/MyDirectXPixelShader.h"
#include "./Shader/MyDirectXVertexShader.h"

namespace mslib {
namespace render {

//オブジェクトのコンストラクタ
//シェーダー引数がなければすべてnullptrになる
//描画に絶対必要なシェーダのみ設定できる
DirectXRenderObject::DirectXRenderObject(
	mslib::directx::VertexShader _vertex_shader,
	mslib::directx::InputLayout _input_layout,
	mslib::directx::PixelShader _pixel_shader) {
	m_shader_resource = std::make_unique<shader::ShaderResource>();

	m_shader_resource->m_vertex_shader = _vertex_shader;
	m_shader_resource->m_input_layout = _input_layout;
	m_shader_resource->m_pixel_shader = _pixel_shader;

	m_vertex_buffer = nullptr;
	m_index_buffer = nullptr;
}

DirectXRenderObject::~DirectXRenderObject() {
}

//ジオメトリシェーダーと
void DirectXRenderObject::SetGeometory(mslib::directx::GeometryShader _geometry_shader)
{
	m_shader_resource->m_geometry_shader = _geometry_shader;
}

void DirectXRenderObject::SetHullDomainShader(mslib::directx::DomainShader _domain_shader, mslib::directx::HullShader _hull_shader)
{
	m_shader_resource->m_domain_shader = _domain_shader;
	m_shader_resource->m_hull_shader = _hull_shader;
}

void DirectXRenderWork::RendBefor(mslib::directx::RenderTargetView _renderTergetView) {
	float color[4] = { 0.f,0.f,1.f,1.f };
	m_device_context->OMSetRenderTargets(1, _renderTergetView.GetAddressOf(), m_depth.Get());
	m_device_context->ClearRenderTargetView(_renderTergetView.Get(), color);
	m_device_context->ClearDepthStencilView(m_depth.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DirectXRenderWork::Draw(std::unique_ptr<DirectXRenderCommand > &_render_command)
{
	//////////////////////////////////////////////////////////////////////
	//					シェーダーセッティング部分						//
	//////////////////////////////////////////////////////////////////////
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

	//weak_ptr型でrender_objectを代入
	auto render_object = m_directx_render_object_warehouse->OutRenderObject(_render_command->m_render_model_name);

	if (render_object.expired())return;

	//unipu_ptr型でシェーダリソースズを参照
	auto& shader_resources = render_object.lock()->GetShaderResources();

	//描画用のシェーダーやレイアウト、頂点データーを送信
	// 頂点フォーマットをセット
	m_device_context->IASetInputLayout(shader_resources->m_input_layout.Get());

	// 頂点シェーダーをセット
	m_device_context->VSSetShader(shader_resources->m_vertex_shader.Get(), nullptr, 0);

	// ピクセルシェーダーをセット
	m_device_context->PSSetShader(shader_resources->m_pixel_shader.Get(), nullptr, 0);

	// サンプラーステートを転送
	// m_device_context->PSSetSamplers(0, 1, render_object.lock()->GetAddressOf());

	//ジオメトリシェーダーをセット
	m_device_context->GSSetShader(shader_resources->m_geometry_shader.Get(), nullptr, 0);

	//ハルシェーダーをセット
	m_device_context->HSSetShader(shader_resources->m_hull_shader.Get(), nullptr, 0);

	//ドメインシェーダーをセット
	m_device_context->DSSetShader(shader_resources->m_domain_shader.Get(), nullptr, 0);

	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//////////////////////////////////////////////////////////////////////
	//					頂点データーセッティング部分					//
	//////////////////////////////////////////////////////////////////////
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

	// 頂点バッファをセットする
	unsigned int stride = sizeof(Vertex3DModel);
	unsigned  offset = 0;

	Transform::TransformSendContext::GetInstance().SendTransform(_render_command->m_matrix, Transform::TransformSendContext::TYPE::WORLD);

	m_device_context->IASetVertexBuffers(0, 1, render_object.lock()->GetVertexBuffer().GetAddressOf(), &stride, &offset);

	//インデックスバッファをセット
	m_device_context->IASetIndexBuffer(render_object.lock()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	for (unsigned int i = 0; i < render_object.lock()->m_mesh.GetMaterial()->texture.size(); i++) {
		m_device_context->PSSetShaderResources(i, 1, render_object.lock()->m_mesh.GetMaterial()->texture[i].GetAddressOf());
	}
	// m_device_context->PSSetShaderResources(1, 1, shader_resources->m_shadowMapshade.GetAddressOf());

	// 描画！！！
	m_device_context->DrawIndexed(
		render_object.lock()->m_mesh.GetPolygons()->index.size(),					// インデックスの数
		0,							// 最初のインデックスバッファの位置
		0							// 頂点バッファの最初からの位置
	);

	//m_device_context->Draw(4,0);

	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑


}
void DirectXRenderWork::DrawQuadLast() {
	//////////////////////////////////////////////////////////////////////
	//					シェーダーセッティング部分						//
	//////////////////////////////////////////////////////////////////////
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	std::string polygon = "polygon";
	//weak_ptr型でrender_objectを代入
	auto render_object = m_directx_render_object_warehouse->OutRenderObject(polygon);

	if (render_object.expired())return;

	//unipu_ptr型でシェーダリソースズを参照
	auto& shader_resources = render_object.lock()->GetShaderResources();

	//描画用のシェーダーやレイアウト、頂点データーを送信
	// 頂点フォーマットをセット
	m_device_context->IASetInputLayout(shader_resources->m_input_layout.Get());

	// 頂点シェーダーをセット
	m_device_context->VSSetShader(shader_resources->m_vertex_shader.Get(), nullptr, 0);

	// ピクセルシェーダーをセット
	m_device_context->PSSetShader(shader_resources->m_pixel_shader.Get(), nullptr, 0);

	// サンプラーステートを転送
	// m_device_context->PSSetSamplers(0, 1, shader_resources->m_shadowMapSmapler.GetAddressOf());

	//ジオメトリシェーダーをセット
	m_device_context->GSSetShader(shader_resources->m_geometry_shader.Get(), nullptr, 0);

	//ハルシェーダーをセット
	m_device_context->HSSetShader(shader_resources->m_hull_shader.Get(), nullptr, 0);

	//ドメインシェーダーをセット
	m_device_context->DSSetShader(shader_resources->m_domain_shader.Get(), nullptr, 0);

	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//////////////////////////////////////////////////////////////////////
	//					頂点データーセッティング部分					//
	//////////////////////////////////////////////////////////////////////
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

	// 頂点バッファをセットする
	unsigned int stride = sizeof(Vertex3DModel);
	unsigned  offset = 0;
	math::Matrix mat;

	Transform::TransformSendContext::GetInstance().SendTransform(
		mat, Transform::TransformSendContext::TYPE::WORLD);

	m_device_context->IASetVertexBuffers(0, 1, render_object.lock()->GetVertexBuffer().GetAddressOf(), &stride, &offset);

	//インデックスバッファをセット
	m_device_context->IASetIndexBuffer(render_object.lock()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	// m_device_context->PSSetShaderResources(1, 1, shader_resources->m_shadowMapshade.GetAddressOf());

	// 描画！！！
	m_device_context->DrawIndexed(
		render_object.lock()->m_mesh.GetPolygons()->index.size(),					// インデックスの数
		0,							// 最初のインデックスバッファの位置
		0							// 頂点バッファの最初からの位置
	);


	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

}

void DirectXRenderWork::DrawPostEffect(const std::unique_ptr<DirectXPostEffectRenderCommand> &_effectComand) {
	//////////////////////////////////////////////////////////////////////
	//					シェーダーセッティング部分						//
	//////////////////////////////////////////////////////////////////////
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	std::string polygon = "polygon";
	//weak_ptr型でrender_objectを代入
	//auto render_object = m_directx_render_object_warehouse->OutRenderObject(polygon);

	//if (render_object.expired())return;

	//描画用のシェーダーやレイアウト、頂点データーを送信
	// 頂点フォーマットをセット
	//m_device_context->IASetInputLayout();

	//// 頂点シェーダーをセット
	//m_device_context->VSSetShader(shader_resources->m_vertex_shader.Get(), nullptr, 0);

	//// ピクセルシェーダーをセット
	//m_device_context->PSSetShader(shader_resources->m_pixel_shader.Get(), nullptr, 0);

	// サンプラーステートを転送
	// m_device_context->PSSetSamplers(0, 1, shader_resources->m_shadowMapSmapler.GetAddressOf());

	//ジオメトリシェーダーをセット
	m_device_context->GSSetShader(nullptr, nullptr, 0);

	//ハルシェーダーをセット
	m_device_context->HSSetShader(nullptr, nullptr, 0);

	//ドメインシェーダーをセット
	m_device_context->DSSetShader(nullptr, nullptr, 0);

	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//////////////////////////////////////////////////////////////////////
	//					頂点データーセッティング部分					//
	//////////////////////////////////////////////////////////////////////
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

	// 頂点バッファをセットする
	unsigned int stride = sizeof(Vertex3DModel);
	unsigned  offset = 0;
	// 画面に張り付けるだけなのでマトリックスは初期のものをセット
	math::Matrix mat;

	Transform::TransformSendContext::GetInstance().SendTransform(
		mat, Transform::TransformSendContext::TYPE::WORLD);

	//m_device_context->IASetVertexBuffers(0, 1, render_object.lock()->GetVertexBuffer().GetAddressOf(), &stride, &offset);

	////インデックスバッファをセット
	//m_device_context->IASetIndexBuffer(render_object.lock()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	// m_device_context->PSSetShaderResources(1, 1, shader_resources->m_shadowMapshade.GetAddressOf());

	// 描画！！！
	//m_device_context->DrawIndexed(
	//	render_object.lock()->m_mesh.GetPolygons()->index.size(),					// インデックスの数
	//	0,							// 最初のインデックスバッファの位置
	//	0							// 頂点バッファの最初からの位置
	//);


	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
}

DirectXRenderObjectLoder::DirectXRenderObjectLoder(
	directx::Device _device, 
	directx::ShaderWark * _shader_wark, 
	DirectXRenderObjectWarehouse * _directx_render_object_warehouse, 
	texture::TextureLoder* _texture_loader)
	:m_vertex_shader_manager(_shader_wark->GetVertexShaderManager()), 
	m_pixel_shader_manager(_shader_wark->GetPixelShaderManager()), 
	m_geometry_shader_manager(_shader_wark->GetGeometryShaderManager()),
	m_directx_render_object_warehouse(_directx_render_object_warehouse), 
	m_device(_device), 
	m_texture_loader(_texture_loader) {
	m_buffer_creater = std::make_unique<directx::BufferCreater>(_device);
}

DirectXRenderObjectLoder::~DirectXRenderObjectLoder() = default;

void DirectXRenderObjectLoder::LoadRenderObjectTest() {
	auto new_object = std::make_shared<DirectXRenderObject>(
		m_vertex_shader_manager->GetVertexShader("normal_vs"),
		m_vertex_shader_manager->GetInputLayer("normal_vs"),
		m_pixel_shader_manager->GetShader("normal_ps"));

	new_object->SetGeometory(m_geometry_shader_manager->GetShader("normal_gs"));

	new_object->m_mesh.Load("assets/aaa.mobj");

	for (unsigned int i = 0; i < new_object->m_mesh.GetMaterial()->texture_name.size(); i++) {
		if (new_object->m_mesh.GetMaterial()->texture_name[i] == "null") continue;
		new_object->m_mesh.GetMaterial()->texture[i] = m_texture_loader->Load(new_object->m_mesh.GetMaterial()->texture_name[i].c_str());
	}

	new_object->SetVertexBuffer(m_buffer_creater->CreateVertexBuffer(&new_object->m_mesh.GetPolygons()->vertex.at(0), new_object->m_mesh.GetPolygons()->vertex.size()));

	new_object->SetIndexBuffer(m_buffer_creater->CreateIndexBuffer(&new_object->m_mesh.GetPolygons()->index.at(0), new_object->m_mesh.GetPolygons()->index.size()));

	m_directx_render_object_warehouse->PushRenderObject(new_object, "dragon");

	auto new_object2 = std::make_shared<DirectXRenderObject>(
		m_vertex_shader_manager->GetVertexShader("gauss_vs"),
		m_vertex_shader_manager->GetInputLayer("gauss_vs"),
		m_pixel_shader_manager->GetShader("gauss_ps"));

	new_object2->m_mesh.Load("assets/polygon.mobj");

	for (unsigned int i = 0; i < new_object2->m_mesh.GetMaterial()->texture_name.size(); i++) {
		if (new_object2->m_mesh.GetMaterial()->texture_name[i] == "null") continue;
		new_object2->m_mesh.GetMaterial()->texture[i] = m_texture_loader->Load(new_object2->m_mesh.GetMaterial()->texture_name[i].c_str());
	}

	new_object2->SetVertexBuffer(m_buffer_creater->CreateVertexBuffer(&new_object2->m_mesh.GetPolygons()->vertex.at(0), new_object2->m_mesh.GetPolygons()->vertex.size()));

	new_object2->SetIndexBuffer(m_buffer_creater->CreateIndexBuffer(&new_object2->m_mesh.GetPolygons()->index.at(0), new_object2->m_mesh.GetPolygons()->index.size()));

	m_directx_render_object_warehouse->PushRenderObject(new_object2, "polygon");
}

void DirectXRenderObjectLoder::CreateVertexBuffer(
	unsigned int stride,				// １頂点当たりバイト数
	unsigned int vertexnum,				// 頂点数
	void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
	ID3D11Buffer** pVertexBuffer		// 頂点バッファ
)
{
	HRESULT hr;

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;							// バッファ使用方法
	bd.ByteWidth = stride * vertexnum;						// バッファの大きさ
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// 頂点バッファ
	bd.CPUAccessFlags = 0;									// CPUアクセス不要

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertexdata;							// バッファの初期値

	hr = m_device->CreateBuffer(&bd, &InitData, pVertexBuffer);		// バッファ生成
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return;
	}

	return;
}

void DirectXRenderObjectLoder::CreateIndexBuffer(
	unsigned int indexnum,						// インデックス数
	void* indexdata,							// インデックスデータ格納メモリ先頭アドレス
	ID3D11Buffer** pIndexBuffer) 				// インデックスバッファ
{
	// インデックスバッファ生成
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;								// バッファ使用方
	bd.ByteWidth = sizeof(unsigned int) * indexnum;				// バッファの大き
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;						// インデックスバッファ
	bd.CPUAccessFlags = 0;										// CPUアクセス不要

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indexdata;

	HRESULT hr = m_device->CreateBuffer(&bd, &InitData, pIndexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(index buffer) error", "Error", MB_OK);
		return;
	}
}

}
}