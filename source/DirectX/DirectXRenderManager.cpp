#include "./DirectXRenderManager.h"
#include "./Shader/Shader.h"
#include "./Renderer/RenderObject.h"
#include "./SubResourceSendManager.h"

namespace mslib {
namespace directx {
//
//DirectXRenderObject::DirectXRenderObject(std::string _vs, std::string _ps) {
//	m_mesh.GetMaterial()->vsName = _vs;
//	m_mesh.GetMaterial()->psName = _ps;
//}
//
////�W�I���g���V�F�[�_�[��
//void DirectXRenderObject::SetGeometory(std::string _gs) {
//	m_mesh.GetMaterial()->gsName = _gs;
//}
//
//void DirectXRenderObject::SetHullDomainShader(std::string _ds, std::string _hs) {
//	m_mesh.GetMaterial()->dsName = _ds;
//	m_mesh.GetMaterial()->hsName = _hs;
//}
//
//void DirectXRenderWork::RendBefor(mslib::directx::RenderTargetView _renderTergetView) {
//	float color[4] = { 0.f,0.f,1.f,1.f };
//	m_device_context->OMSetRenderTargets(1, _renderTergetView.GetAddressOf(), m_depth.Get());
//	m_device_context->ClearRenderTargetView(_renderTergetView.Get(), color);
//	m_device_context->ClearDepthStencilView(m_depth.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
//}
//
//void DirectXRenderWork::Draw(std::unique_ptr<DirectXRenderCommand > &_render_command)
//{
//	//////////////////////////////////////////////////////////////////////
//	//					�V�F�[�_�[�Z�b�e�B���O����						//
//	//////////////////////////////////////////////////////////////////////
//	//��������������������������������������������������������������������
//
//	//weak_ptr�^��render_object����
//	auto render_object = m_directx_render_object_warehouse->OutRenderObject(_render_command->m_render_model_name);
//
//	if (render_object.expired())return;
//
//	//unipu_ptr�^�ŃV�F�[�_���\�[�X�Y���Q��
//	auto material = render_object.lock()->GetMesh()->GetMaterial();
//
//	//�`��p�̃V�F�[�_�[�⃌�C�A�E�g�A���_�f�[�^�[�𑗐M
//	// ���_�t�H�[�}�b�g���Z�b�g
//	auto il = ShaderWark::GetInstance().GetVertexShaderManager()->GetInputLayer(material->vsName.c_str());
//	m_device_context->IASetInputLayout(il.Get());
//
//	// ���_�V�F�[�_�[���Z�b�g
//	auto vs = ShaderWark::GetInstance().GetVertexShaderManager()->GetVertexShader(material->vsName.c_str());
//	m_device_context->VSSetShader(vs.Get(), nullptr, 0);
//
//	// �s�N�Z���V�F�[�_�[���Z�b�g
//	auto ps = ShaderWark::GetInstance().GetPixelShaderManager()->GetShader(material->psName.c_str());
//	m_device_context->PSSetShader(ps.Get(), nullptr, 0);
//
//	// �T���v���[�X�e�[�g��]��
//	// m_device_context->PSSetSamplers(0, 1, render_object.lock()->GetAddressOf());
//
//	//�W�I���g���V�F�[�_�[���Z�b�g
//	auto gs = ShaderWark::GetInstance().GetGeometryShaderManager()->GetShader(material->gsName.c_str());
//	m_device_context->GSSetShader(gs.Get(), nullptr, 0);
//
//	//�n���V�F�[�_�[���Z�b�g
//	m_device_context->HSSetShader(nullptr, nullptr, 0);
//
//	//�h���C���V�F�[�_�[���Z�b�g
//	m_device_context->DSSetShader(nullptr, nullptr, 0);
//
//	//��������������������������������������������������������������������
//
//	//////////////////////////////////////////////////////////////////////
//	//					���_�f�[�^�[�Z�b�e�B���O����					//
//	//////////////////////////////////////////////////////////////////////
//	//��������������������������������������������������������������������
//
//	// ���_�o�b�t�@���Z�b�g����
//	unsigned int stride = sizeof(render::Vertex3DModel);
//	unsigned  offset = 0;
//
//	Transform::TransformSendContext::GetInstance().SendTransform(_render_command->m_matrix, Transform::TransformSendContext::TYPE::WORLD);
//
//	m_device_context->IASetVertexBuffers(0, 1, render_object.lock()->GetVertexBuffer().GetAddressOf(), &stride, &offset);
//
//	//�C���f�b�N�X�o�b�t�@���Z�b�g
//	m_device_context->IASetIndexBuffer(render_object.lock()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
//	
//	for (unsigned int i = 0; i < material->textureName.size(); i++) {
//		m_device_context->PSSetShaderResources(i, 1, material->texture[i].GetAddressOf());
//	}
//	// m_device_context->PSSetShaderResources(1, 1, shader_resources->m_shadowMapshade.GetAddressOf());
//
//	// �`��I�I�I
//	m_device_context->DrawIndexed(
//		render_object.lock()->GetMesh()->GetPolygons()->index.size(),					// �C���f�b�N�X�̐�
//		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
//		0							// ���_�o�b�t�@�̍ŏ�����̈ʒu
//	);
//
//	//m_device_context->Draw(4,0);
//
//	//��������������������������������������������������������������������
//
//
//}
//void DirectXRenderWork::DrawQuadLast() {
//	//////////////////////////////////////////////////////////////////////
//	//					�V�F�[�_�[�Z�b�e�B���O����						//
//	//////////////////////////////////////////////////////////////////////
//	//��������������������������������������������������������������������
//	std::string polygon = "polygon";
//	//weak_ptr�^��render_object����
//	auto render_object = m_directx_render_object_warehouse->OutRenderObject(polygon);
//
//	//unipu_ptr�^�ŃV�F�[�_���\�[�X�Y���Q��
//	auto material = render_object.lock()->GetMesh()->GetMaterial();
//
//	//�`��p�̃V�F�[�_�[�⃌�C�A�E�g�A���_�f�[�^�[�𑗐M
//	// ���_�t�H�[�}�b�g���Z�b�g
//	auto il = ShaderWark::GetInstance().GetVertexShaderManager()->GetInputLayer(material->vsName.c_str());
//	m_device_context->IASetInputLayout(il.Get());
//
//	// ���_�V�F�[�_�[���Z�b�g
//	auto vs = ShaderWark::GetInstance().GetVertexShaderManager()->GetVertexShader(material->vsName.c_str());
//	m_device_context->VSSetShader(vs.Get(), nullptr, 0);
//
//	// �s�N�Z���V�F�[�_�[���Z�b�g
//	auto ps = ShaderWark::GetInstance().GetPixelShaderManager()->GetShader(material->psName.c_str());
//	m_device_context->PSSetShader(ps.Get(), nullptr, 0);
//
//	// �T���v���[�X�e�[�g��]��
//	// m_device_context->PSSetSamplers(0, 1, render_object.lock()->GetAddressOf());
//
//	//�W�I���g���V�F�[�_�[���Z�b�g
//	auto gs = ShaderWark::GetInstance().GetGeometryShaderManager()->GetShader(material->gsName.c_str());
//	m_device_context->GSSetShader(gs.Get(), nullptr, 0);
//
//	//�n���V�F�[�_�[���Z�b�g
//	m_device_context->HSSetShader(nullptr, nullptr, 0);
//
//	//�h���C���V�F�[�_�[���Z�b�g
//	m_device_context->DSSetShader(nullptr, nullptr, 0);
//	//��������������������������������������������������������������������
//
//	//////////////////////////////////////////////////////////////////////
//	//					���_�f�[�^�[�Z�b�e�B���O����					//
//	//////////////////////////////////////////////////////////////////////
//	//��������������������������������������������������������������������
//
//	// ���_�o�b�t�@���Z�b�g����
//	unsigned int stride = sizeof(render::Vertex3DModel);
//	unsigned  offset = 0;
//	math::Matrix mat;
//
//	Transform::TransformSendContext::GetInstance().SendTransform(
//		mat, Transform::TransformSendContext::TYPE::WORLD);
//
//	m_device_context->IASetVertexBuffers(0, 1, render_object.lock()->GetVertexBuffer().GetAddressOf(), &stride, &offset);
//
//	//�C���f�b�N�X�o�b�t�@���Z�b�g
//	m_device_context->IASetIndexBuffer(render_object.lock()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
//
//	// m_device_context->PSSetShaderResources(1, 1, shader_resources->m_shadowMapshade.GetAddressOf());
//
//	// �`��I�I�I
//	m_device_context->DrawIndexed(
//		render_object.lock()->GetMesh()->GetPolygons()->index.size(),					// �C���f�b�N�X�̐�
//		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
//		0							// ���_�o�b�t�@�̍ŏ�����̈ʒu
//	);
//
//
//	//��������������������������������������������������������������������
//
//}
//
//void DirectXRenderWork::DrawPostEffect(const std::unique_ptr<DirectXPostEffectRenderCommand> &_effectComand) {
//	//////////////////////////////////////////////////////////////////////
//	//					�V�F�[�_�[�Z�b�e�B���O����						//
//	//////////////////////////////////////////////////////////////////////
//	//��������������������������������������������������������������������
//	std::string polygon = "polygon";
//	//weak_ptr�^��render_object����
//	//auto render_object = m_directx_render_object_warehouse->OutRenderObject(polygon);
//
//	//if (render_object.expired())return;
//
//	//�`��p�̃V�F�[�_�[�⃌�C�A�E�g�A���_�f�[�^�[�𑗐M
//	// ���_�t�H�[�}�b�g���Z�b�g
//	//m_device_context->IASetInputLayout();
//
//	//// ���_�V�F�[�_�[���Z�b�g
//	//m_device_context->VSSetShader(shader_resources->m_vertex_shader.Get(), nullptr, 0);
//
//	//// �s�N�Z���V�F�[�_�[���Z�b�g
//	//m_device_context->PSSetShader(shader_resources->m_pixel_shader.Get(), nullptr, 0);
//
//	// �T���v���[�X�e�[�g��]��
//	// m_device_context->PSSetSamplers(0, 1, shader_resources->m_shadowMapSmapler.GetAddressOf());
//
//	//�W�I���g���V�F�[�_�[���Z�b�g
//	m_device_context->GSSetShader(nullptr, nullptr, 0);
//
//	//�n���V�F�[�_�[���Z�b�g
//	m_device_context->HSSetShader(nullptr, nullptr, 0);
//
//	//�h���C���V�F�[�_�[���Z�b�g
//	m_device_context->DSSetShader(nullptr, nullptr, 0);
//
//	//��������������������������������������������������������������������
//
//	//////////////////////////////////////////////////////////////////////
//	//					���_�f�[�^�[�Z�b�e�B���O����					//
//	//////////////////////////////////////////////////////////////////////
//	//��������������������������������������������������������������������
//
//	// ���_�o�b�t�@���Z�b�g����
//	unsigned int stride = sizeof(render::Vertex3DModel);
//	unsigned  offset = 0;
//	// ��ʂɒ���t���邾���Ȃ̂Ń}�g���b�N�X�͏����̂��̂��Z�b�g
//	math::Matrix mat;
//
//	Transform::TransformSendContext::GetInstance().SendTransform(
//		mat, Transform::TransformSendContext::TYPE::WORLD);
//
//	//m_device_context->IASetVertexBuffers(0, 1, render_object.lock()->GetVertexBuffer().GetAddressOf(), &stride, &offset);
//
//	////�C���f�b�N�X�o�b�t�@���Z�b�g
//	//m_device_context->IASetIndexBuffer(render_object.lock()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
//
//	// m_device_context->PSSetShaderResources(1, 1, shader_resources->m_shadowMapshade.GetAddressOf());
//
//	// �`��I�I�I
//	//m_device_context->DrawIndexed(
//	//	render_object.lock()->m_mesh.GetPolygons()->index.size(),					// �C���f�b�N�X�̐�
//	//	0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
//	//	0							// ���_�o�b�t�@�̍ŏ�����̈ʒu
//	//);
//
//
//	//��������������������������������������������������������������������
//}
//
//DirectXRenderObjectLoder::DirectXRenderObjectLoder(
//	shader::ShaderWark * _shader_wark, 
//	DirectXRenderObjectWarehouse * _directx_render_object_warehouse)
//	:m_vertex_shader_manager(_shader_wark->GetVertexShaderManager()), 
//	m_pixel_shader_manager(_shader_wark->GetPixelShaderManager()), 
//	m_geometry_shader_manager(_shader_wark->GetGeometryShaderManager()),
//	m_directx_render_object_warehouse(_directx_render_object_warehouse), 
//	m_device(_device), 
//	m_texture_loader(_texture_loader) {
//	m_buffer_creater = std::make_unique<directx::BufferCreater>(_device);
//}
//
//DirectXRenderObjectLoder::~DirectXRenderObjectLoder() = default;
//
//void DirectXRenderObjectLoder::LoadRenderObjectTest() {
//	auto new_object = std::make_shared<DirectXRenderObject>(
//		m_vertex_shader_manager->GetVertexShader("normal_vs"),
//		m_vertex_shader_manager->GetInputLayer("normal_vs"),
//		m_pixel_shader_manager->GetShader("normal_ps"));
//
//	new_object->SetGeometory(m_geometry_shader_manager->GetShader("normal_gs"));
//
//	new_object->m_mesh.Load("assets/aaa.mobj");
//
//	// ��
//	for (unsigned int i = 0; i < new_object->m_mesh.GetMaterial()->textureName.size(); i++) {
//		if (new_object->m_mesh.GetMaterial()->textureName[i] == "null") continue;
//		new_object->m_mesh.GetMaterial()->texture[i] = m_texture_loader->Load(new_object->m_mesh.GetMaterial()->textureName[i].c_str());
//	}
//
//	new_object->SetVertexBuffer(m_buffer_creater->CreateVertexBuffer(&new_object->m_mesh.GetPolygons()->vertex.at(0), new_object->m_mesh.GetPolygons()->vertex.size()));
//
//	new_object->SetIndexBuffer(m_buffer_creater->CreateIndexBuffer(&new_object->m_mesh.GetPolygons()->index.at(0), new_object->m_mesh.GetPolygons()->index.size()));
//
//	m_directx_render_object_warehouse->PushRenderObject(new_object, "dragon");
//	// ��
//
//	auto new_object2 = std::make_shared<DirectXRenderObject>(
//		m_vertex_shader_manager->GetVertexShader("gauss_vs"),
//		m_vertex_shader_manager->GetInputLayer("gauss_vs"),
//		m_pixel_shader_manager->GetShader("gauss_ps"));
//
//	new_object2->m_mesh.Load("assets/polygon.mobj");
//
//	for (unsigned int i = 0; i < new_object2->m_mesh.GetMaterial()->textureName.size(); i++) {
//		if (new_object2->m_mesh.GetMaterial()->textureName[i] == "null") continue;
//		new_object2->m_mesh.GetMaterial()->texture[i] = m_texture_loader->Load(new_object2->m_mesh.GetMaterial()->textureName[i].c_str());
//	}
//
//	new_object2->SetVertexBuffer(m_buffer_creater->CreateVertexBuffer(&new_object2->m_mesh.GetPolygons()->vertex.at(0), new_object2->m_mesh.GetPolygons()->vertex.size()));
//
//	new_object2->SetIndexBuffer(m_buffer_creater->CreateIndexBuffer(&new_object2->m_mesh.GetPolygons()->index.at(0), new_object2->m_mesh.GetPolygons()->index.size()));
//
//	m_directx_render_object_warehouse->PushRenderObject(new_object2, "polygon");
//}
//
//void DirectXRenderObjectLoder::CreateVertexBuffer(
//	unsigned int stride,				// �P���_������o�C�g��
//	unsigned int vertexnum,				// ���_��
//	void* vertexdata,					// ���_�f�[�^�i�[�������擪�A�h���X
//	ID3D11Buffer** pVertexBuffer		// ���_�o�b�t�@
//)
//{
//	HRESULT hr;
//
//	// ���_�o�b�t�@����
//	D3D11_BUFFER_DESC bd;
//	ZeroMemory(&bd, sizeof(bd));
//	bd.Usage = D3D11_USAGE_DEFAULT;							// �o�b�t�@�g�p���@
//	bd.ByteWidth = stride * vertexnum;						// �o�b�t�@�̑傫��
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// ���_�o�b�t�@
//	bd.CPUAccessFlags = 0;									// CPU�A�N�Z�X�s�v
//
//	D3D11_SUBRESOURCE_DATA InitData;
//	ZeroMemory(&InitData, sizeof(InitData));
//	InitData.pSysMem = vertexdata;							// �o�b�t�@�̏����l
//
//	hr = m_device->CreateBuffer(&bd, &InitData, pVertexBuffer);		// �o�b�t�@����
//	if (FAILED(hr)) {
//		MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
//		return;
//	}
//
//	return;
//}
//
//void DirectXRenderObjectLoder::CreateIndexBuffer(
//	unsigned int indexnum,						// �C���f�b�N�X��
//	void* indexdata,							// �C���f�b�N�X�f�[�^�i�[�������擪�A�h���X
//	ID3D11Buffer** pIndexBuffer) 				// �C���f�b�N�X�o�b�t�@
//{
//	// �C���f�b�N�X�o�b�t�@����
//	D3D11_BUFFER_DESC bd;
//	D3D11_SUBRESOURCE_DATA InitData;
//
//	ZeroMemory(&bd, sizeof(bd));
//	bd.Usage = D3D11_USAGE_DEFAULT;								// �o�b�t�@�g�p��
//	bd.ByteWidth = sizeof(unsigned int) * indexnum;				// �o�b�t�@�̑傫
//	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;						// �C���f�b�N�X�o�b�t�@
//	bd.CPUAccessFlags = 0;										// CPU�A�N�Z�X�s�v
//
//	ZeroMemory(&InitData, sizeof(InitData));
//	InitData.pSysMem = indexdata;
//
//	HRESULT hr = m_device->CreateBuffer(&bd, &InitData, pIndexBuffer);
//	if (FAILED(hr)) {
//		MessageBox(nullptr, "CreateBuffer(index buffer) error", "Error", MB_OK);
//		return;
//	}
//}
//
//void DirectXRenderObject::LoadModelData(std::string _modelName, std::string _hashName){
//	auto new_object = std::make_shared<DirectXRenderObject>(
//		m_vertex_shader_manager->GetVertexShader("normal_vs"),
//		m_vertex_shader_manager->GetInputLayer("normal_vs"),
//		m_pixel_shader_manager->GetShader("normal_ps"));
//
//	new_object->SetGeometory(m_geometry_shader_manager->GetShader("normal_gs"));
//
//	new_object->m_mesh.Load("assets/aaa.mobj");
//
//	// ��
//	for (unsigned int i = 0; i < new_object->m_mesh.GetMaterial()->textureName.size(); i++) {
//		if (new_object->m_mesh.GetMaterial()->textureName[i] == "null") continue;
//		new_object->m_mesh.GetMaterial()->texture[i] = m_texture_loader->Load(new_object->m_mesh.GetMaterial()->textureName[i].c_str());
//	}
//
//	new_object->SetVertexBuffer(m_buffer_creater->CreateVertexBuffer(&new_object->m_mesh.GetPolygons()->vertex.at(0), new_object->m_mesh.GetPolygons()->vertex.size()));
//
//	new_object->SetIndexBuffer(m_buffer_creater->CreateIndexBuffer(&new_object->m_mesh.GetPolygons()->index.at(0), new_object->m_mesh.GetPolygons()->index.size()));
//
//	m_directx_render_object_warehouse->PushRenderObject(new_object, "dragon");
//}

}
}