#include "Mesh.h"
#include "Render.h"

using namespace std;

namespace gdk
{
	namespace dx9
	{
		Mesh::Mesh() :
			mesh(nullptr),
			geometry(nullptr),
			texture(nullptr),
			materialNum(0),
			position(0.0f, 0.0f, 0.0f),
			rotation(0.0f, 0.0f, 0.0f),
			scale(1.0f, 1.0f, 1.0f)
		{

		}

		Mesh::Mesh(const string& xFileDirectory, const string& textureFileDirectory) :
			mesh(nullptr),
			geometry(nullptr),
			texture(nullptr),
			materialNum(0),
			position(0.0f, 0.0f, 0.0f),
			rotation(0.0f, 0.0f, 0.0f),
			scale(1.0f, 1.0f, 1.0f)
		{
			Load(xFileDirectory, textureFileDirectory);
		}

		Mesh::~Mesh()
		{
			if (mesh)
			{
				mesh->Release();
				mesh = nullptr;
			}

			if (geometry)
			{
				geometry->Release();
				geometry = nullptr;
			}

			if (texture)
			{
				texture->Release();
				texture = nullptr;
			}
		}

		void Mesh::Load(const string& xFileDirectory, const string& textureFileDirectory)
		{
			if (FAILED(D3DXLoadMeshFromX(xFileDirectory.c_str(), D3DXMESH_SYSTEMMEM, Render::Device(), nullptr, &geometry, nullptr, &materialNum, &mesh)))
			{
				return;
			}

			if (FAILED(D3DXCreateTextureFromFile(Render::Device(), textureFileDirectory.c_str(), &texture)))
			{
				return;
			}
		}

		void Mesh::Draw()
		{
			D3DXMATRIX m_world, m_temp;

			D3DXMatrixIdentity(&m_world);
			D3DXMatrixIdentity(&m_temp);

			// �s����g��k������
			D3DXMatrixScaling(&m_temp, scale.x, scale.y, scale.z);
			m_world *= m_temp;

			// �s�����]����
			D3DXMatrixRotationX(&m_temp, rotation.x);
			m_world *= m_temp;

			// �s�����]����
			D3DXMatrixRotationY(&m_temp, rotation.y);
			m_world *= m_temp;

			// �s�����]����
			D3DXMatrixRotationZ(&m_temp, rotation.z);
			m_world *= m_temp;

			// �s��𕽍s�ړ�������
			D3DXMatrixTranslation(&m_temp, position.x, position.y, position.z);
			m_world *= m_temp;

			Render::Device()->SetTransform(D3DTS_WORLD, &m_world);

			Render::Device()->SetTexture(0, texture);

			// ���f���̕`��
			D3DXMATERIAL *materials = (D3DXMATERIAL *)geometry->GetBufferPointer();

			for (DWORD i = 0; i < materialNum; i++)
			{
				// �}�e���A���̐ݒ�
				Render::Device()->SetMaterial(&materials[i].MatD3D);

				// �������ꂽ���b�V���̕`��
				mesh->DrawSubset(i);
			}
		}
	}
}
