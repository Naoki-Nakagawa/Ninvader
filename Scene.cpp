#include "Scene.h"

using namespace std;

Scene* Scene::scene;

void Scene::SetScene(Scene& newScene)
{
	scene = &newScene;
}

Scene& Scene::GetScene()
{
	return *scene;
}
