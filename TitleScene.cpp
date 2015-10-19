#include <string>
#include <fstream>
#include "GdkDx9.h"
#include "MainScene.h"
#include "Random.h"
#include "TitleScene.h"

using namespace std;
using namespace gdk::dx9;

TitleScene::TitleScene() :
	camera(D3DXVECTOR3(0.0f, 3.0f, -7.5f), D3DXVECTOR3(D3DXToRadian(20), 0.0f, 0.0f)),
	enemy(),
	star("Textures/effect0.png"),
	fontL(64, ""),
	fontS(32, ""),
	enemyRotationScale(0.0f),
	highScore(0)
{
	for (int i = 0; i < 1000; ++i)
	{
		star.Set(D3DXVECTOR3(Random::FloatRange(-250.0f, 250.0f), Random::FloatRange(-400.0f, 100.0f), Random::FloatRange(100.0f, 1100.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 5.0f, -1);
	}

	enemy[0].Load("Models/enemy0.x", "Textures/enemy0.png");
	enemy[1].Load("Models/enemy1.x", "Textures/enemy1.png");
	enemy[2].Load("Models/enemy2.x", "Textures/enemy2.png");

	ifstream ifs("highScore.txt");
	if (!ifs.fail())
	{
		string str;
		getline(ifs, str);
		highScore = stoi(str);
	}
	else
	{
		highScore = 0;
	}
}

TitleScene::~TitleScene()
{

}

TitleScene& TitleScene::GetInstance()
{
	static TitleScene instance;

	return instance;
}

// XVˆ—
void TitleScene::Update()
{
	enemyRotationScale += 0.01f;

	if (Input::GetKey(DIK_LEFTARROW))
	{
		enemyRotationScale += 0.1f;
	}

	if (Input::GetKey(DIK_RIGHTARROW))
	{
		enemyRotationScale -= 0.11f;
	}

	if (enemyRotationScale < 0.0f)
	{
		enemyRotationScale += D3DX_PI * 2.0f;
	}

	if (enemyRotationScale > D3DX_PI * 2.0f)
	{
		enemyRotationScale -= D3DX_PI * 2.0f;
	}

	if (Input::GetKey(DIK_Z))
	{
		Scene::SetScene(MainScene::GetInstance());
	}

	for (int i = 0; i < enemy.size(); ++i)
	{
		enemy[i].position.x = sin(enemyRotationScale + D3DXToRadian(120 * i)) * 2.0f;
		enemy[i].position.z = cos(enemyRotationScale + D3DXToRadian(120 * i)) * 2.0f;
		enemy[i].rotation.y = enemyRotationScale + D3DXToRadian(180 + 120 * i);
	}
}

// •`‰æˆ—
void TitleScene::Draw()
{
	star.Draw();

	fontS.position = D3DXVECTOR3(-1.4f, 3.1f, 0.0f);
	fontS.Print("HighScore : " + to_string(highScore));

	fontL.position = D3DXVECTOR3(-1.15f, 2.7f, 0.0f);
	fontL.Print("Ninvader");

	fontL.position = D3DXVECTOR3(-1.85f, -3.0f, 0.0f);
	fontL.Print("Push Z Key");

	for (int i = 0; i < enemy.size(); ++i)
	{
		enemy[i].Draw();
	}
}
