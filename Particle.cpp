#include "Render.h"
#include "Particle.h"

using namespace std;

namespace gdk
{
	namespace dx9
	{
		DWORD FloatToDWORD(float val)
		{
			return *((DWORD*)&val);
		}

		Particle::Particle() :
			buffer(nullptr),
			texture(nullptr),
			transform()
		{
			Render::Device()->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
			Render::Device()->SetRenderState(D3DRS_POINTSCALEENABLE, true);
			Render::Device()->SetRenderState(D3DRS_POINTSIZE, FloatToDWORD(1.0f));
			Render::Device()->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDWORD(0.0f));
			Render::Device()->SetRenderState(D3DRS_POINTSCALE_A, FloatToDWORD(0.0f));
			Render::Device()->SetRenderState(D3DRS_POINTSCALE_B, FloatToDWORD(0.0f));
			Render::Device()->SetRenderState(D3DRS_POINTSCALE_C, FloatToDWORD(1.0f));

			if (FAILED(Render::Device()->CreateVertexBuffer(100 * sizeof(Vertex), D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_PSIZE, D3DPOOL_MANAGED, &buffer, nullptr)))
			{
				return;
			}
		}

		Particle::Particle(string textureFileDirectory) :
			buffer(nullptr),
			texture(nullptr),
			transform()
		{
			Render::Device()->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
			Render::Device()->SetRenderState(D3DRS_POINTSCALEENABLE, true);
			Render::Device()->SetRenderState(D3DRS_POINTSIZE, FloatToDWORD(1.0f));
			Render::Device()->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDWORD(0.0f));
			Render::Device()->SetRenderState(D3DRS_POINTSCALE_A, FloatToDWORD(0.0f));
			Render::Device()->SetRenderState(D3DRS_POINTSCALE_B, FloatToDWORD(0.0f));
			Render::Device()->SetRenderState(D3DRS_POINTSCALE_C, FloatToDWORD(1.0f));

			if (FAILED(Render::Device()->CreateVertexBuffer(100 * sizeof(Vertex), D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_PSIZE, D3DPOOL_MANAGED, &buffer, nullptr)))
			{
				return;
			}

			Load(textureFileDirectory);
		}

		Particle::~Particle()
		{
			if (buffer)
			{
				buffer->Release();
				buffer = nullptr;
			}

			if (texture)
			{
				texture->Release();
				texture = nullptr;
			}
		}

		void Particle::Load(string textureFileDirectory)
		{
			if (FAILED(D3DXCreateTextureFromFile(Render::Device(), textureFileDirectory.c_str(), &texture)))
			{
				return;
			}
		}

		void Particle::Set(D3DXVECTOR3 position, D3DXVECTOR3 velocity, float gravity, float scale, int duration)
		{
			Transform instanceTransform = { position,velocity,gravity,scale,duration };
			transform.push_back(instanceTransform);
		}

		void Particle::Draw()
		{
			for (int i = 0; i < transform.size(); i++)
			{
				if (transform[i].duration == 0)
				{
					transform.erase(transform.begin() + i);
					i--;
				}
			}

			Render::Device()->SetRenderState(D3DRS_ZENABLE, false);

			int iMax = transform.size() / 100;
			for (int i = 0; i <= iMax; i++)
			{
				Vertex *v;
				buffer->Lock(0, 0, (LPVOID*)&v, 0);
				for (int j = 0; j < 100; j++)
				{
					if (transform.size() <= i * 100 + j)
					{
						break;
					}

					v[j].pos = transform[i * 100 + j].position += transform[i * 100 + j].velocity += D3DXVECTOR3(0, transform[i * 100 + j].gravity, 0);
					v[j].size = transform[i * 100 + j].scale;

					transform[i * 100 + j].duration--;
				}
				buffer->Unlock();

				Render::Device()->SetTexture(0, texture);

				D3DXMATRIX m_world;
				D3DXMatrixIdentity(&m_world);
				Render::Device()->SetTransform(D3DTS_WORLD, &m_world);

				Render::Device()->SetStreamSource(0, buffer, 0, sizeof(Vertex));
				Render::Device()->SetFVF(D3DFVF_XYZ | D3DFVF_PSIZE);
				Render::Device()->DrawPrimitive(D3DPT_POINTLIST, 0, transform.size());
			}

			Render::Device()->SetRenderState(D3DRS_ZENABLE, true);
		}
	}
}
