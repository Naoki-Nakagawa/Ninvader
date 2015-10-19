#include <d3dx9.h>
#include "Render.h"
#include "Screen.h"

namespace gdk
{
	namespace dx9
	{
		IDirect3DDevice9* Render::device(nullptr);

		Render::Render()
		{
			IDirect3D9* direct3d = Direct3DCreate9(D3D_SDK_VERSION);
			if (!direct3d)
			{
				return;
			}

			D3DPRESENT_PARAMETERS pp;
			ZeroMemory(&pp, sizeof(pp));
			pp.hDeviceWindow = Screen::Handle();
			pp.BackBufferCount = 1;
			pp.BackBufferWidth = Screen::Size().x;
			pp.BackBufferHeight = Screen::Size().y;
			pp.BackBufferFormat = D3DFMT_UNKNOWN;
			pp.Windowed = true;
			pp.MultiSampleType = D3DMULTISAMPLE_NONE;
			pp.MultiSampleQuality = 0;
			pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
			pp.EnableAutoDepthStencil = true;
			pp.AutoDepthStencilFormat = D3DFMT_D16;
			pp.Flags = 0;
			pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
			pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

			if (FAILED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Screen::Handle(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &device)))
			{
				direct3d->Release();
				device = nullptr;
				return;
			}

			device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
			device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
			device->SetRenderState(D3DRS_DITHERENABLE, true);
			device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			device->SetRenderState(D3DRS_ZENABLE, true);
			device->SetRenderState(D3DRS_ZWRITEENABLE, true);
			device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
			device->SetRenderState(D3DRS_LIGHTING, true);
			device->SetRenderState(D3DRS_SPECULARENABLE, true);
			device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
			device->SetRenderState(D3DRS_ALPHAREF, 0x00000000);
			device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
			device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
			device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
			device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

			D3DLIGHT9 light;
			ZeroMemory(&light, sizeof(D3DLIGHT9));

			light.Type = D3DLIGHT_DIRECTIONAL;
			light.Direction = D3DXVECTOR3(1, -1, 1);
			light.Diffuse.r = 1.0f;
			light.Diffuse.g = 1.0f;
			light.Diffuse.b = 1.0f;

			device->SetLight(0, &light);
			device->LightEnable(0, true);
			device->SetRenderState(D3DRS_LIGHTING, true);
			device->SetRenderState(D3DRS_AMBIENT, 0xff030303);

			Clear(0x00000000);
		}

		Render::~Render()
		{
			if (device)
			{
				device->Release();
				device = nullptr;
			}
		}

		void Render::Create()
		{
			static Render instance;
		}

		void Render::Clear(const int& color)
		{
			device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0);
		}

		void Render::Present()
		{
			device->EndScene();

			device->Present(nullptr, nullptr, nullptr, nullptr);

			device->BeginScene();
		}

		IDirect3DDevice9* Render::Device()
		{
			return device;
		}
	}
}
