#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "./AssetManager/AssetManager.h"

#ifdef DIRECTX11
#include "./DirectX/DirectX11Manager.h"
#include "./ShaderCompiler.h"
#endif

#include <string>

////�e��V�F�[�_�[�̃}�l�[�W��
//#include "MyDirectXVertexShader.h"
//#include "MyDirectXPixelShader.h"
//#include "MyDirectXGeometryShader.h"

#define SHADER_NAME_MAX 256

//�O���錾
namespace mslib {
namespace shader {

#ifdef DIRECTX11
// using Shader = Microsoft::WRL::WeakRef;
using Shader = directx::PixelShader;

enum class ShaderType {
	VS,
	IL,
	PS,
	GS,
	DS,
	HS
};

using VertexShader = directx::VertexShader;
using InputLayer = directx::InputLayout;
using PixelShader = directx::PixelShader;
using GeometryShader = directx::GeometryShader;
using DomainShader = directx::DomainShader;
using HullShader = directx::HullShader;


//�V�F�[�_���܂Ƃ߂��N���X
struct ShaderResource {
	VertexShader vertexShader = nullptr;
	InputLayer inputLayer = nullptr;
	PixelShader pixelShader = nullptr;
	GeometryShader geometryShader = nullptr;
	DomainShader domainShader = nullptr;
	HullShader hullShader = nullptr;
};
#endif

class Shaders {
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	Shaders() = default;
	~Shaders() = default;

	// �V�F�[�_�̃Z�b�g
	void SetVertexShader(VertexShader _shader);
	void SetPixelShader(PixelShader _shader);
	void SetGeometryShader(GeometryShader _shader);
	void SetDomainShader(DomainShader _shader);
	void SetHullShader(HullShader _shader);
private:
	VertexShader m_vertexShader = nullptr;
	InputLayer inputLayer = nullptr;
	PixelShader pixelShader = nullptr;
	GeometryShader geometryShader = nullptr;
	DomainShader domainShader = nullptr;
	HullShader hullShader = nullptr;
};
}
}