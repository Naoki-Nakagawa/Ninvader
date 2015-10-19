#include <memory>
#include <Windows.h>
#include "GdkDx9.h"
#include "Scene.h"
#include "TitleScene.h"

using namespace std;
using namespace gdk::dx9;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Screen::Name("Ninvader");
	Screen::Size(Int2(1280, 720));

	GdkDx9 gdk;

	Scene::SetScene(TitleScene::GetInstance());

	while (Screen::Message())
	{
		Scene::GetScene().Update();
		Scene::GetScene().Draw();
	}

	return 0;
}
