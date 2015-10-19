#ifndef _GdkDx9_Particle_h_
#define _GdkDx9_Particle_h_

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>

namespace gdk
{
	namespace dx9
	{
		class Particle
		{
		private:

			struct Transform
			{
				D3DXVECTOR3 position;	// ���W
				D3DXVECTOR3 velocity;	// �x�N�g��
				float gravity;			// �d�͉����x
				float scale;			// �傫��
				int duration;			// ��������
			};

			struct Vertex
			{
				D3DXVECTOR3 pos;
				float size;
			};

			IDirect3DVertexBuffer9* buffer;
			IDirect3DTexture9* texture;
			std::vector<Transform> transform;

		public:

			Particle();

			Particle(std::string textureFileDirectory);

			~Particle();

			void Load(std::string textureFileDirectory);

			void Set(D3DXVECTOR3 position, D3DXVECTOR3 velocity, float gravity, float scale, int duration);

			void Draw();

		};
	}
}

#endif	// _GdkDx9_Particle_h_
