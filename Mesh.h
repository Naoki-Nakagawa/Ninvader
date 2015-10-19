#ifndef _GdkDx9_Mesh_h_
#define _GdkDx9_Mesh_h_

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

namespace gdk
{
	namespace dx9
	{
		class Mesh
		{
		private:

			ID3DXMesh* mesh;
			ID3DXBuffer* geometry;
			IDirect3DTexture9* texture;
			DWORD materialNum;

		public:

			D3DXVECTOR3 position;
			D3DXVECTOR3 rotation;
			D3DXVECTOR3 scale;

			Mesh();

			Mesh(const std::string& xFileDirectory, const std::string& textureFileDirectory);

			~Mesh();

			void Load(const std::string& xFileDirectory, const std::string& textureFileDirectory);

			void Draw();

		};
	}
}

#endif	// _GdkDx9_Mesh_h_
