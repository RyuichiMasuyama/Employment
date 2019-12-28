#define _CRT_SECURE_NO_WARNINGS

#ifdef DIRECTX11
#include "./DirectX/DirectXPipeline.h"
#endif

#include "./RenderObject.h"
#include <filesystem>
#include <fstream>

#define CHAR_PTR_CAST(t) reinterpret_cast<char*>(&t)

using fi = std::ifstream;

namespace fs = std::experimental::filesystem;

namespace mslib {
namespace render {

MyMesh::MyMesh() :m_pipeline(this){
	m_polygons = std::make_shared<render::Polygons>();
}

const std::vector<std::shared_ptr<Material>> & MyMesh::GetMaterial(){
	return m_material;
}

std::shared_ptr<Material> MyMesh::GetMaterial(int num) {
	if (num < m_material.size())
		return m_material[num];
	else
		return nullptr;
}

std::shared_ptr<Polygons> MyMesh::GetPolygons() {
	return m_polygons;
}

void MyMesh::SetShader(std::string _shaderName, shader::ShaderType _shaderType) {
	switch (_shaderType)
	{
	case mslib::shader::ShaderType::VS:
		m_pipeline.SetVertexShader(_shaderName);
		break;
	case mslib::shader::ShaderType::PS:
		m_pipeline.SetPixelShader(_shaderName);
		break;
	case mslib::shader::ShaderType::GS:
		m_pipeline.SetGeometory(_shaderName);
		break;
	case mslib::shader::ShaderType::DS:
		m_pipeline.SetDomainShader(_shaderName);
		break;
	case mslib::shader::ShaderType::HS:
		m_pipeline.SetHullShader(_shaderName);
		break;
	default:
		break;
	}
}

void MyMesh::SetTexture(std::string _textureName, int textureNumber) {
	loader::TextureLoader textureLoader;
	m_pipeline.SetTexture(textureLoader.Load(_textureName), textureNumber);
}

Pipeline * MyMesh::GetPipeline()
{
	return &m_pipeline;
}
void MyMesh::Load(std::string _file_name) {
	// �t�@�C�����J���O����
	fi file;
	fs::path filePath(_file_name);

	// �t�@�C�����J��
	file.open(filePath, fi::out | fi::binary);

	// �t�@�C��������ɊJ������
	if (!file.is_open()) return;
	int MeshNum;

	struct InputVertex {
		math::Vector3 pos;
		math::Vector3 normal;
		math::Vector2 tex;
	};

	struct InputMaterial {
		math::Vector3 ambient;		//�A���r�G���g
		math::Vector3 diffuse;		//�f�B�t���[�Y
		math::Vector3 emissive;		//�G�~�b�V�u
		math::Vector3 bump;			//�o���v
		float transparency;		//�g�����X�y�A�����g
		math::Vector3 specular;		//�X�y�L����
		float specular_power;	//�X�y�L�����p���[
		float shininess;		//�V���C�j�[�Y
		float reflectivity;		//���t���N�V����
	};

	// 1�D���b�V����
	file.read(CHAR_PTR_CAST(MeshNum), sizeof(int));

	for (int i = 0; i < MeshNum; i++) {
		// 2�D���b�V���̃T�C�Y
		int VectorSize;
		file.read(CHAR_PTR_CAST(VectorSize), sizeof(int));

		std::vector<InputVertex> InVers;

		InVers.resize(VectorSize);
		m_polygons->vertex.resize(VectorSize);

		// 3. ���_���
		file.read(reinterpret_cast<char*>(const_cast<InputVertex*>(InVers.data())), sizeof(InputVertex) * VectorSize);

		// ���_�����i�[
		for (int i = 0; i < VectorSize; i++) {
			m_polygons->vertex[i].normal = InVers[i].normal;
			m_polygons->vertex[i].pos = InVers[i].pos;
			m_polygons->vertex[i].tex = InVers[i].tex;
		}

		// 4�D�C���f�b�N�X�̃T�C�Y
		int IndexSize;
		file.read(CHAR_PTR_CAST(IndexSize), sizeof(int));
		m_polygons->index.resize(IndexSize);

		// 5. �C���f�b�N�X���
		file.read(reinterpret_cast<char*>(const_cast<UINT*>(m_polygons->index.data())), sizeof(UINT)*IndexSize);
	}

	int MaterialNum;
	// 6�D�}�e���A���̐�
	file.read(CHAR_PTR_CAST(MaterialNum), sizeof(int));

	for (int i = 0; i < MaterialNum; i++) {
		InputMaterial InMats;
		// 7. �}�e���A���̃f�[�^
		file.read(CHAR_PTR_CAST(InMats), sizeof(InputMaterial));
		m_material.push_back(std::make_shared<Material>());
		m_material[i]->ambient = InMats.ambient;
		m_material[i]->bump = InMats.bump;
		m_material[i]->diffuse = InMats.diffuse;
		m_material[i]->emissive = InMats.emissive;
		m_material[i]->reflectivity = InMats.reflectivity;
		m_material[i]->shininess = InMats.shininess;
		m_material[i]->specular = InMats.specular;
		m_material[i]->specular.w = InMats.specular_power;
		m_material[i]->transparency = InMats.transparency;

		for (auto& itr : m_material[i]->textureName) {
			int FilePathNameSize;
			// 8. �e�e�N�X�`���̃t�@�C���p�X�̃f�[�^�̃T�C�Y
			file.read(CHAR_PTR_CAST(FilePathNameSize), sizeof(int));
			// 9. �e�e�N�X�`���̃t�@�C���p�X�̃f�[�^
			char filePaht[512];
			file.read(filePaht, sizeof(char)*FilePathNameSize);
			filePaht[FilePathNameSize] = '\0';
			itr = filePaht;
		}

		for (auto& itr : m_material[i]->shaderName) {
			int FilePathNameSize;
			// 10.�e�V�F�[�_�̃t�@�C���p�X�̕����̃f�[�^�̃T�C�Y
			file.read(CHAR_PTR_CAST(FilePathNameSize), sizeof(int));
			// 11.�e�V�F�[�_�̃t�@�C���p�X�f�[�^
			char filePaht[512];
			file.read(filePaht, sizeof(char)*FilePathNameSize);
			filePaht[FilePathNameSize] = '\0';
			itr = filePaht;
		}
	}

	m_pipeline.CreateIndexBuffer(m_polygons->index.size(), &m_polygons->index[0]);
	m_pipeline.CreateVertexBuffer(sizeof(m_polygons->vertex[0]), m_polygons->vertex.size(), &m_polygons->vertex.at(0));

	if (0 < m_material.size()) {
		for (auto itr : m_material[0]->textureName) {
			m_pipeline.LoadTexture(itr);
		}
		// �V�F�[�_�[���[�h
		m_pipeline.SetVertexPixcle(
			m_material[0]->shaderName[static_cast<int>(SHADER_ENUM::VERTEX_SHADER)],
			m_material[0]->shaderName[static_cast<int>(SHADER_ENUM::PIXEL_SHADER)]
		);
		m_pipeline.SetGeometory(m_material[0]->shaderName[static_cast<int>(SHADER_ENUM::GEOMETRY_SHADER)]);
		m_pipeline.SetHullDomainShader(
			m_material[0]->shaderName[static_cast<int>(SHADER_ENUM::HULL_SHADER)],
			m_material[0]->shaderName[static_cast<int>(SHADER_ENUM::DOMAIN_SHADER)]
		);
	}

	// �t�@�C�������
	file.close();
}

//void MyMesh::Load(std::string _file_name) {
//	FILE*p_file;
//	p_file = fopen(_file_name.c_str(), "r");
//
//	if (p_file == nullptr) {
//		// �G���[���Ƀ��b�Z�[�W�E�B���h�E�\�������̂�Windows.h�g�p
//		_file_name = "NotFound[" + _file_name + "]";
//		MessageBox(nullptr, _file_name.c_str(), "Error", MB_OK);
//	}
//	else {
//		UINT vertex_num, index_num;
//
//		//���_�f�[�^�̐�
//		fscanf(p_file, "%d\n", &vertex_num);
//
//		//�e��T�C�Y�ύX
//		m_polygons.vertex.resize(vertex_num);
//
//		//���_���W�f�[�^
//		for (UINT i = 0; i < vertex_num; i++) {
//			fscanf(p_file, "%f\t%f\t%f\n", &m_polygons.vertex[i].pos.x, &m_polygons.vertex[i].pos.y, &m_polygons.vertex[i].pos.z);
//		}
//
//		fscanf(p_file, "\n");
//
//		//���_�@���f�[�^
//		for (UINT i = 0; i < vertex_num; i++) {
//			fscanf(p_file, "%f\t%f\t%f\n", &m_polygons.vertex[i].normal.x, &m_polygons.vertex[i].normal.y, &m_polygons.vertex[i].normal.z);
//		}
//
//		fscanf(p_file, "\n");
//
//
//		//UV���W�f�[�^
//		for (UINT i = 0; i < vertex_num; i++) {
//			fscanf(p_file, "%f\t%f\n", &m_polygons.vertex[i].uv.x, &m_polygons.vertex[i].uv.y);
//		}
//
//		fscanf(p_file, "\n");
//
//		//�C���f�b�N�X�f�[�^�̐�
//		fscanf(p_file, "%d\n", &index_num);
//
//		m_polygons.index.resize(index_num);
//
//		for (UINT i = 0; i < index_num; i++) {
//			fscanf(p_file, "%d\n", &m_polygons.index[i]);
//		}
//
//		fscanf(p_file, "\n");
//
//		for (UINT i = 0; i < m_material.textureName.size(); i++) {
//			char name[256];
//			fscanf(p_file, "%s", name);
//			m_material.textureName[i] = name;
//		}
//
//		fscanf(p_file, "\n");
//
//		char shaderName[256];
//		fscanf(p_file, "%s", shaderName);
//		m_material.vsName= shaderName;
//		fscanf(p_file, "%s", shaderName);
//		m_material.psName = shaderName;
//		fscanf(p_file, "%s", shaderName);
//		m_material.gsName = shaderName;
//		fscanf(p_file, "%s", shaderName);
//		m_material.hsName = shaderName;
//		fscanf(p_file, "%s", shaderName);
//		m_material.dsName = shaderName;
//		fclose(p_file);
//
//		m_pipeline.CreateIndexBuffer(m_polygons.index.size(), &m_polygons.index[0]);
//		m_pipeline.CreateVertexBuffer(sizeof(m_polygons.vertex[0]), m_polygons.vertex.size(), &m_polygons.vertex.at(0));
//
//		for (auto itr : m_material.textureName) {
//			m_pipeline.LoadTexture(itr);
//		}
//		// �V�F�[�_�[���[�h
//		m_pipeline.SetVertexPixcle(m_material.vsName, m_material.psName);
//		m_pipeline.SetGeometory(m_material.gsName);
//		m_pipeline.SetHullDomainShader(m_material.hsName, m_material.dsName);
//
//		return; 
//
//		//�^���W�F���g���߂�
//		////////////////////////////////////////////////////////////////////////////////////////////////////////
//		// ������r��
//		////////////////////////////////////////////////////////////////////////////////////////////////////////
//		/*for (UINT i = 0; i < index_num; i += 3) {
//			math::Vector3 tan[3];
//			math::Vector3 fale_data;
//
//			CalcTangentAndBinormal(
//				m_polygons.vertex[m_polygons.index[i]].pos, m_polygons.vertex[m_polygons.index[i]].uv,
//				m_polygons.vertex[m_polygons.index[i + 1]].pos, m_polygons.vertex[m_polygons.index[i + 1]].uv,
//				m_polygons.vertex[m_polygons.index[i + 2]].pos, m_polygons.vertex[m_polygons.index[i + 2]].uv,
//				tan[0], fale_data
//			);
//			CalcTangentAndBinormal(
//				m_polygons.vertex[m_polygons.index[i + 1]].pos, m_polygons.vertex[m_polygons.index[i + 1]].uv,
//				m_polygons.vertex[m_polygons.index[i + 2]].pos, m_polygons.vertex[m_polygons.index[i + 2]].uv,
//				m_polygons.vertex[m_polygons.index[i]].pos, m_polygons.vertex[m_polygons.index[i]].uv,
//				tan[1], fale_data
//			);
//			CalcTangentAndBinormal(
//				m_polygons.vertex[m_polygons.index[i + 2]].pos, m_polygons.vertex[m_polygons.index[i + 2]].uv,
//				m_polygons.vertex[m_polygons.index[i]].pos, m_polygons.vertex[m_polygons.index[i]].uv,
//				m_polygons.vertex[m_polygons.index[i + 1]].pos, m_polygons.vertex[m_polygons.index[i + 1]].uv,
//				tan[2], fale_data
//			);
//
//			m_polygons.vertex[m_polygons.index[i]].tangent = tan[0];
//			m_polygons.vertex[m_polygons.index[i + 1]].tangent = tan[1];
//			m_polygons.vertex[m_polygons.index[i + 2]].tangent = tan[2];
//		}*/
//		////////////////////////////////////////////////////////////////////////////////////////////////////////
//		// ������r��
//		////////////////////////////////////////////////////////////////////////////////////////////////////////
//	}
//}

}
}