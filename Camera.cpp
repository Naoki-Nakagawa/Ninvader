#include <d3d9.h>
#include "Camera.h"
#include "Screen.h"
#include "Render.h"

namespace gdk
{
	namespace dx9
	{
		void Camera::Create()
		{
			D3DVIEWPORT9 viewPort;
			viewPort.X = 0;
			viewPort.Y = 0;
			viewPort.Width = Screen::Size().x;
			viewPort.Height = Screen::Size().y;
			viewPort.MinZ = 0.0f;
			viewPort.MaxZ = 1.0f;

			Render::Device()->SetViewport(&viewPort);

			// 射影行列の初期化
			D3DXMATRIX m_projection;
			D3DXMatrixIdentity(&m_projection);

			// 射影行列を作成
			D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), static_cast<float>(viewPort.Width) / viewPort.Height, 0.1f, 10000.0f);

			// 射影行列をパイプラインに設定
			Render::Device()->SetTransform(D3DTS_PROJECTION, &m_projection);

			View();
		}

		Camera::Camera() :
			position(0.0f, 0.0f, 0.0f),
			rotation(0.0f, 0.0f, 0.0f)
		{
			Create();
		}

		Camera::Camera(const D3DXVECTOR3& position, const D3DXVECTOR3& rotation) :
			position(position),
			rotation(rotation)
		{
			Create();
		}

		Camera::~Camera()
		{

		}

		void Camera::View()
		{
			D3DXMATRIX m_view, m_temp;

			D3DXMatrixIdentity(&m_view);
			D3DXMatrixIdentity(&m_temp);

			// 行列を回転する
			D3DXMatrixRotationX(&m_temp, rotation.x);
			m_view *= m_temp;

			// 行列を回転する
			D3DXMatrixRotationY(&m_temp, rotation.y);
			m_view *= m_temp;

			// 行列を回転する
			D3DXMatrixRotationZ(&m_temp, rotation.z);
			m_view *= m_temp;

			// 行列を平行移動させる
			D3DXMatrixTranslation(&m_temp, position.x, position.y, position.z);
			m_view *= m_temp;

			// 逆行列を求める
			D3DXMatrixInverse(&m_view, nullptr, &m_view);

			Render::Device()->SetTransform(D3DTS_VIEW, &m_view);
		}
	}
}
