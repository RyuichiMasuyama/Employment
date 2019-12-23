
#ifdef DIRECTX11
#include "./Windows/WindowsDefineData.h"

#include "./DirectXPostEffect.h"
#include "./DirectX/SubResourceSendManager.h"
#include "./AssetManager/ShaderLoader.h"

namespace mslib {
namespace directx {
DirectXPostEffect::DirectXPostEffect(render::CameraTexture _cameraTexture) {
	auto device = directx::DirectX11Manager::GetInstance().GetDevice();
	loader::MeshLoader meshLoader;
	loader::ShaderLoader shaderLoader;

	m_mesh = meshLoader.Load("Quad");

	shaderLoader.Load("shader/PSGauss.fx", m_shader[static_cast<unsigned int>(DIRECTX_POSTEFFECT_TYPE::GAUSS)].pixelShader, shader::ShaderType::PS);
	shaderLoader.Load("shader/VSGauss.fx", m_shader[static_cast<unsigned int>(DIRECTX_POSTEFFECT_TYPE::GAUSS)].vertexShader, shader::ShaderType::VS);
	shaderLoader.Load("shader/VSGauss.fx", m_shader[static_cast<unsigned int>(DIRECTX_POSTEFFECT_TYPE::GAUSS)].inputLayer, shader::ShaderType::IL);

	shaderLoader.Load("shader/Base/psRender2DBase.fx", m_basic2dPS, shader::ShaderType::PS);
	shaderLoader.Load("shader/Base/vsRender2DBase.fx", m_basic2dVS, shader::ShaderType::VS);
	shaderLoader.Load("shader/Base/vsRender2DBase.fx", m_basic2dIL, shader::ShaderType::IL);

	m_resourceView = _cameraTexture;
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
	device->CreateTexture2D(
		&texDesc,
		NULL,
		m_gaussTexture2d.GetAddressOf());
	for (auto& itr : m_bloomTexture2d) {
		device->CreateTexture2D(
			&texDesc,
			NULL,
			itr.GetAddressOf());
	}

	// �����_�[�^�[�Q�b�g�r���[�̐ݒ�
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// �����_�[�^�[�Q�b�g�r���[�̐���
	device->CreateRenderTargetView(
		m_gaussTexture2d.Get(),
		&rtvDesc,
		m_gaussRenderTergetView.GetAddressOf());
	for (int i = 0; i < m_bloomRenderTergetView.size(); i++) {
		device->CreateRenderTargetView(
			m_bloomTexture2d[i].Get(),
			&rtvDesc,
			m_bloomRenderTergetView[i].GetAddressOf());
	}

	// �V�F�[�_���\�[�X�r���[�̐ݒ�
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(srvDesc));
	srvDesc.Format = rtvDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	// �V�F�[�_���\�[�X�r���[�̐���	
	device->CreateShaderResourceView(
		m_gaussTexture2d.Get(),
		&srvDesc,
		m_gaussShaderResourceView.GetAddressOf());
	for (int i = 0; i < m_bloomRenderTergetView.size(); i++) {
		device->CreateShaderResourceView(
			m_bloomTexture2d[i].Get(),
			&srvDesc,
			m_bloomShaderResourceView[i].GetAddressOf());
	}
}
void DirectXPostEffect::Rendering() {
	auto deviceContext = directx::DirectX11Manager::GetInstance().GetDeviceContext();

	bool flag = false;
	for (auto itr : m_postEffectStatus.OnFlag) {
		if (itr) {
			flag = itr;
			break;
		}
	}

	if (flag) {
		SubResourceSendManager::GetInstance().SetPostEffect(
			m_postEffectStatus.GaussPower,
			m_postEffectStatus.BloomDiffusePower,
			m_postEffectStatus.BloomSpecularPower
		);
	}
	else {
		return;
	}

	directx::RenderTargetView oldRenderTerget;
	directx::DepthStencilView oldDepthStencil;

	deviceContext->OMGetRenderTargets(1, oldRenderTerget.GetAddressOf(), oldDepthStencil.GetAddressOf());

	// 1. Gauss
	if (m_postEffectStatus.OnFlag[static_cast<unsigned int>(DIRECTX_POSTEFFECT_TYPE::GAUSS)]) {
		deviceContext->OMSetRenderTargets(1, m_gaussRenderTergetView.GetAddressOf(), oldDepthStencil.Get());

		deviceContext->IASetInputLayout(m_shader[static_cast<unsigned int>(DIRECTX_POSTEFFECT_TYPE::GAUSS)].inputLayer.Get());
		deviceContext->VSSetShader(m_shader[static_cast<unsigned int>(DIRECTX_POSTEFFECT_TYPE::GAUSS)].vertexShader.Get(), nullptr, 0);
		deviceContext->PSSetShader(m_shader[static_cast<unsigned int>(DIRECTX_POSTEFFECT_TYPE::GAUSS)].pixelShader.Get(), nullptr, 0);

		deviceContext->GSSetShader(nullptr, nullptr, 0);
		deviceContext->HSSetShader(nullptr, nullptr, 0);
		deviceContext->DSSetShader(nullptr, nullptr, 0);

		SubResourceSendManager::GetInstance().SetPostEffect(
			m_postEffectStatus.GaussPower,
			m_postEffectStatus.BloomDiffusePower,
			m_postEffectStatus.BloomSpecularPower
		);

		deviceContext->PSSetShaderResources(0, 1, m_resourceView.GetAddressOf());

		// ���_�o�b�t�@���Z�b�g����
		unsigned int stride = sizeof(render::Vertex3DModel);
		unsigned  offset = 0;

		// �o�[�e�b�N�X�o�b�t�@���Z�b�g
		deviceContext->IASetVertexBuffers(0, 1, m_mesh->GetPipeline()->m_vertex_buffer.GetAddressOf(), &stride, &offset);

		//�C���f�b�N�X�o�b�t�@���Z�b�g
		deviceContext->IASetIndexBuffer(m_mesh->GetPipeline()->m_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);

		// �`��I�I�I
		deviceContext->DrawIndexed(
			static_cast<UINT>(m_mesh->GetPolygons()->index.size()),					// �C���f�b�N�X�̐�
			0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
			0							// ���_�o�b�t�@�̍ŏ�����̈ʒu
		);
	}

	// 2�DBloom
	if (m_postEffectStatus.OnFlag[static_cast<unsigned int>(DIRECTX_POSTEFFECT_TYPE::BLOOM)]) {

		deviceContext->VSSetShader(nullptr, nullptr, 0);
		deviceContext->PSSetShader(nullptr, nullptr, 0);
		// ���O�m��
		deviceContext->GSSetShader(nullptr, nullptr, 0);
		deviceContext->HSSetShader(nullptr, nullptr, 0);
		deviceContext->DSSetShader(nullptr, nullptr, 0);

		// ���_�o�b�t�@���Z�b�g����
		unsigned int stride = sizeof(render::Vertex3DModel);
		unsigned  offset = 0;

		deviceContext->IASetVertexBuffers(0, 1, m_mesh->GetPipeline()->m_vertex_buffer.GetAddressOf(), &stride, &offset);

		//�C���f�b�N�X�o�b�t�@���Z�b�g
		deviceContext->IASetIndexBuffer(m_mesh->GetPipeline()->m_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);

		// �`��I�I�I
		deviceContext->DrawIndexed(
			static_cast<UINT>(m_mesh->GetPolygons()->index.size()),					// �C���f�b�N�X�̐�
			0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
			0							// ���_�o�b�t�@�̍ŏ�����̈ʒu
		);
	}
	float backColor[4] = { 0.f,0.f,1.f,1.f };

	deviceContext->OMSetRenderTargets(1, oldRenderTerget.GetAddressOf(), oldDepthStencil.Get());
	deviceContext->ClearRenderTargetView(oldRenderTerget.Get(), backColor);
	deviceContext->ClearDepthStencilView(oldDepthStencil.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	deviceContext->IASetInputLayout(m_basic2dIL.Get());
	deviceContext->VSSetShader(m_basic2dVS.Get(), nullptr, 0);
	deviceContext->PSSetShader(m_basic2dPS.Get(), nullptr, 0);

	deviceContext->GSSetShader(nullptr, nullptr, 0);
	deviceContext->HSSetShader(nullptr, nullptr, 0);
	deviceContext->DSSetShader(nullptr, nullptr, 0);

	deviceContext->PSSetShaderResources(0, 1, m_gaussShaderResourceView.GetAddressOf());

	// ���_�o�b�t�@���Z�b�g����
	unsigned int stride = sizeof(render::Vertex3DModel);
	unsigned  offset = 0;

	// �o�[�e�b�N�X�o�b�t�@���Z�b�g
	deviceContext->IASetVertexBuffers(0, 1, m_mesh->GetPipeline()->m_vertex_buffer.GetAddressOf(), &stride, &offset);

	//�C���f�b�N�X�o�b�t�@���Z�b�g
	deviceContext->IASetIndexBuffer(m_mesh->GetPipeline()->m_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	deviceContext->DrawIndexed(
		static_cast<UINT>(m_mesh->GetPolygons()->index.size()),					// �C���f�b�N�X�̐�
		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0							// ���_�o�b�t�@�̍ŏ�����̈ʒu
	);
}
}
}
#endif