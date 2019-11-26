#define _CRT_SECURE_NO_WARNINGS

#ifdef DIRECTX11
#include "./DirectX/DirectXPipeline.h"
#endif

#include "./RenderObject.h"
#include <Windows.h>

namespace mslib {
namespace render {

MyMesh::MyMesh() :m_pipeline(this){
	m_material.textureName.resize(TEXTURE_ENUM::TEXTURE_MAX);
	for (auto& itr : m_material.textureName) {
		itr = "null";
	}
}

Material *MyMesh::GetMaterial() {
	return &m_material;
}

Polygons * MyMesh::GetPolygons() {
	return &m_polygons;
}

Pipeline * MyMesh::GetPipeline()
{
	return &m_pipeline;
}

void MyMesh::Load(std::string _file_name) {
	FILE*p_file;
	p_file = fopen(_file_name.c_str(), "r");

	if (p_file == nullptr) {
		// エラー時にメッセージウィンドウ表示ここのみWindows.h使用
		_file_name = "NotFound[" + _file_name + "]";
		MessageBox(nullptr, _file_name.c_str(), "Error", MB_OK);
	}
	else {
		UINT vertex_num, index_num;

		//頂点データの数
		fscanf(p_file, "%d\n", &vertex_num);

		//各種サイズ変更
		m_polygons.vertex.resize(vertex_num);

		//頂点座標データ
		for (UINT i = 0; i < vertex_num; i++) {
			fscanf(p_file, "%f\t%f\t%f\n", &m_polygons.vertex[i].pos.x, &m_polygons.vertex[i].pos.y, &m_polygons.vertex[i].pos.z);
		}

		fscanf(p_file, "\n");

		//頂点法線データ
		for (UINT i = 0; i < vertex_num; i++) {
			fscanf(p_file, "%f\t%f\t%f\n", &m_polygons.vertex[i].normal.x, &m_polygons.vertex[i].normal.y, &m_polygons.vertex[i].normal.z);
		}

		fscanf(p_file, "\n");


		//UV座標データ
		for (UINT i = 0; i < vertex_num; i++) {
			fscanf(p_file, "%f\t%f\n", &m_polygons.vertex[i].uv.x, &m_polygons.vertex[i].uv.y);
		}

		fscanf(p_file, "\n");

		//インデックスデータの数
		fscanf(p_file, "%d\n", &index_num);

		m_polygons.index.resize(index_num);

		for (UINT i = 0; i < index_num; i++) {
			fscanf(p_file, "%d\n", &m_polygons.index[i]);
		}

		fscanf(p_file, "\n");

		for (UINT i = 0; i < m_material.textureName.size(); i++) {
			char name[256];
			fscanf(p_file, "%s", name);
			m_material.textureName[i] = name;
		}

		fscanf(p_file, "\n");

		fclose(p_file);

		m_pipeline.CreateIndexBuffer(m_polygons.index.size(), &m_polygons.index[0]);
		m_pipeline.CreateVertexBuffer(sizeof(m_polygons.vertex[0]), m_polygons.vertex.size(), &m_polygons.vertex[0]);

		for (auto itr : m_material.textureName) {
			m_pipeline.LoadTexture(itr);
		}

		return; 

		//タンジェント求める
		////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ↓制作途中
		////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*for (UINT i = 0; i < index_num; i += 3) {
			math::Vector3 tan[3];
			math::Vector3 fale_data;

			CalcTangentAndBinormal(
				m_polygons.vertex[m_polygons.index[i]].pos, m_polygons.vertex[m_polygons.index[i]].uv,
				m_polygons.vertex[m_polygons.index[i + 1]].pos, m_polygons.vertex[m_polygons.index[i + 1]].uv,
				m_polygons.vertex[m_polygons.index[i + 2]].pos, m_polygons.vertex[m_polygons.index[i + 2]].uv,
				tan[0], fale_data
			);
			CalcTangentAndBinormal(
				m_polygons.vertex[m_polygons.index[i + 1]].pos, m_polygons.vertex[m_polygons.index[i + 1]].uv,
				m_polygons.vertex[m_polygons.index[i + 2]].pos, m_polygons.vertex[m_polygons.index[i + 2]].uv,
				m_polygons.vertex[m_polygons.index[i]].pos, m_polygons.vertex[m_polygons.index[i]].uv,
				tan[1], fale_data
			);
			CalcTangentAndBinormal(
				m_polygons.vertex[m_polygons.index[i + 2]].pos, m_polygons.vertex[m_polygons.index[i + 2]].uv,
				m_polygons.vertex[m_polygons.index[i]].pos, m_polygons.vertex[m_polygons.index[i]].uv,
				m_polygons.vertex[m_polygons.index[i + 1]].pos, m_polygons.vertex[m_polygons.index[i + 1]].uv,
				tan[2], fale_data
			);

			m_polygons.vertex[m_polygons.index[i]].tangent = tan[0];
			m_polygons.vertex[m_polygons.index[i + 1]].tangent = tan[1];
			m_polygons.vertex[m_polygons.index[i + 2]].tangent = tan[2];
		}*/
		////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ↑制作途中
		////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

}
}