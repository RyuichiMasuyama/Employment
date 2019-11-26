#include "./DirectXRenderTerget.h"

#include "./Renderer/RenderObject.h"

#include "./Windows/WindowsDefineData.h"

namespace mslib {
namespace directx {
DirectXRenderTerget::DirectXRenderTerget(render::RenderTergetType _renderTergetType) :
	render::RenderTerget(_renderTergetType) {};

DirectXRenderTerget::~DirectXRenderTerget() = default;

void DirectXRenderTerget::SetRenderTerget() {
	// directx::DirectX11Manager::GetInstance().GetDeviceContext()->PSSetShaderResources(_number + 1, 1, m_shaderResourceView.GetAddressOf());
	DirectX11Manager::GetInstance().GetDeviceContext()->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
}

void DirectXRenderTerget::SetShaderResouce(int _number) {
	DirectX11Manager::GetInstance().GetDeviceContext()->PSSetShaderResources(_number, 1, m_shaderResourceView.GetAddressOf());
}

void DirectXRenderTerget::RenderBefor() {
	float color[4] = { 0.f,0.f,1.f,1.f };
	auto deviceContext = DirectX11Manager::GetInstance().GetDeviceContext();;
	auto depth = DirectX11Manager::GetInstance().GetDepthStencilView();

	deviceContext->OMSetRenderTargets(1, m_renderTergetView.GetAddressOf(), depth.Get());
	deviceContext->ClearRenderTargetView(m_renderTergetView.Get(), color);
	deviceContext->ClearDepthStencilView(depth.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}
//
//void DirectXRenderTerget::Pipeline() {
//
//	//////////////////////////////////////////////////////////////////////
//	//					�V�F�[�_�[�Z�b�e�B���O����						//
//	//////////////////////////////////////////////////////////////////////
//	//��������������������������������������������������������������������
//
//	//weak_ptr�^��render_object����
//	// auto render_object = m_directx_render_object_warehouse->OutRenderObject(_render_command->m_render_model_name);
//
//	// if (render_object.expired())return;
//
//	//unipu_ptr�^�ŃV�F�[�_���\�[�X�Y���Q��
//	auto material = Mesh()->GetMaterial();
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
//}

MainDirectXRenderTerget::MainDirectXRenderTerget(render::RenderTergetType _renderTergetType)
	:DirectXRenderTerget(_renderTergetType) {
	// 2�����e�N�X�`���̐ݒ�
	D3D11_TEXTURE2D_DESC texDesc;
	memset(&texDesc, 0, sizeof(texDesc));
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Width = SCREEN_X;
	texDesc.Height = SCREEN_Y;
	texDesc.CPUAccessFlags = 0;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;

	// 2�����e�N�X�`���̐���
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateTexture2D(
		&texDesc,
		NULL,
		m_texture2d.GetAddressOf());

	// �����_�[�^�[�Q�b�g�r���[�̐ݒ�
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// �����_�[�^�[�Q�b�g�r���[�̐���
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateRenderTargetView(
		m_texture2d.Get(),
		&rtvDesc,
		m_renderTergetView.GetAddressOf());

	// �V�F�[�_���\�[�X�r���[�̐ݒ�
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(srvDesc));
	srvDesc.Format = rtvDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	// �V�F�[�_���\�[�X�r���[�̐���
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateShaderResourceView(
		m_texture2d.Get(),
		&srvDesc,
		m_shaderResourceView.GetAddressOf());

	// �T���v���X�e�[�g�̐ݒ�
	D3D11_SAMPLER_DESC smpDesc;
	memset(&smpDesc, 0, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	smpDesc.MinLOD = 0;
	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// �T���v���X�e�[�g����
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateSamplerState(
		&smpDesc,
		m_samplerState.GetAddressOf());
}

SubDirectXRenderTerget::SubDirectXRenderTerget(render::RenderTergetType _renderTergetType)
	:DirectXRenderTerget(_renderTergetType) {
	// 2�����e�N�X�`���̐ݒ�
	D3D11_TEXTURE2D_DESC texDesc;
	memset(&texDesc, 0, sizeof(texDesc));
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Width = SCREEN_X;
	texDesc.Height = SCREEN_Y;
	texDesc.CPUAccessFlags = 0;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;

	// 2�����e�N�X�`���̐���
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateTexture2D(
		&texDesc,
		NULL,
		m_texture2d.GetAddressOf());

	// �����_�[�^�[�Q�b�g�r���[�̐ݒ�
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// �����_�[�^�[�Q�b�g�r���[�̐���
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateRenderTargetView(
		m_texture2d.Get(),
		&rtvDesc,
		m_renderTergetView.GetAddressOf());

	// �V�F�[�_���\�[�X�r���[�̐ݒ�
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(srvDesc));
	srvDesc.Format = rtvDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	// �V�F�[�_���\�[�X�r���[�̐���
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateShaderResourceView(
		m_texture2d.Get(),
		&srvDesc,
		m_shaderResourceView.GetAddressOf());

	// �T���v���X�e�[�g�̐ݒ�
	D3D11_SAMPLER_DESC smpDesc;
	memset(&smpDesc, 0, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	smpDesc.MinLOD = 0;
	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// �T���v���X�e�[�g����
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateSamplerState(
		&smpDesc,
		m_samplerState.GetAddressOf());

}

ShadowMapDirectXRenderTerget::ShadowMapDirectXRenderTerget(render::RenderTergetType _renderTergetType)
	:DirectXRenderTerget(_renderTergetType) {
	// 2�����e�N�X�`���̐ݒ�
	D3D11_TEXTURE2D_DESC texDesc;
	memset(&texDesc, 0, sizeof(texDesc));
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Width = SCREEN_X;
	texDesc.Height = SCREEN_Y;
	texDesc.CPUAccessFlags = 0;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;

	// 2�����e�N�X�`���̐���
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateTexture2D(
		&texDesc,
		NULL,
		m_texture2d.GetAddressOf());

	// �����_�[�^�[�Q�b�g�r���[�̐ݒ�
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// �����_�[�^�[�Q�b�g�r���[�̐���
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateRenderTargetView(
		m_texture2d.Get(),
		&rtvDesc,
		m_renderTergetView.GetAddressOf());

	// �V�F�[�_���\�[�X�r���[�̐ݒ�
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(srvDesc));
	srvDesc.Format = rtvDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	// �V�F�[�_���\�[�X�r���[�̐���
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateShaderResourceView(
		m_texture2d.Get(),
		&srvDesc,
		m_shaderResourceView.GetAddressOf());

	// �T���v���X�e�[�g�̐ݒ�
	D3D11_SAMPLER_DESC smpDesc;
	memset(&smpDesc, 0, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	smpDesc.BorderColor[0] = 1.0f;
	smpDesc.BorderColor[1] = 1.0f;
	smpDesc.BorderColor[2] = 1.0f;
	smpDesc.BorderColor[3] = 1.0f;
	smpDesc.MaxAnisotropy = 1;
	smpDesc.MipLODBias = 0;
	smpDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
	smpDesc.MinLOD = D3D11_FTOI_INSTRUCTION_MIN_INPUT;
	smpDesc.MaxLOD = D3D11_FTOI_INSTRUCTION_MAX_INPUT;

	// �T���v���X�e�[�g����
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateSamplerState(
		&smpDesc,
		m_samplerState.GetAddressOf());
}

}
}
