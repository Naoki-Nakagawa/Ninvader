#include <string>
#include <fstream>
#include "GdkDx9.h"
#include "Random.h"
#include "MainScene.h"

using namespace std;
using namespace gdk::dx9;

bool PointToSphere(const D3DXVECTOR3& pPos, const D3DXVECTOR3& sPos, float sRadius)
{
	// êÇíºï˚å¸ÇÃìñÇËîªíË
	float xValue = pow(pPos.x - sPos.x, 2);
	float yValue = pow(pPos.y - sPos.y, 2);
	float zValue = pow(pPos.z - sPos.z, 2);
	float rValue = pow(sRadius, 2);

	if (xValue + yValue <= rValue)
	{
		// êÖïΩï˚å¸ÇÃìñÇËîªíË
		if (zValue + yValue <= rValue)
		{
			return true;
		}
	}

	return false;
}

MainScene::MainScene() :
	camera(D3DXVECTOR3(0.0f, player.position.y + 5.0f, player.position.z - 10.0f), D3DXVECTOR3(D3DXToRadian(20), 0.0f, 0.0f)),
	player("Models/player.x", "Textures/player.png"),
	jet("Textures/effect1.png"),
	playerVelocity(0.0f),
	enemy(),
	star("Textures/effect0.png"),
	enemyRotationScale(0.0f),
	enemyExist(),
	enemySpeed(0.05f),
	score(0),
	highScore(0),
	bulletExist(false),
	bullet("Textures/effect0.png"),
	bulletPosition()
{
	for (int i = 0; i < 1000; ++i)
	{
		star.Set(D3DXVECTOR3(Random::FloatRange(-250.0f, 250.0f), Random::FloatRange(-400.0f, 100.0f), Random::FloatRange(100.0f, 1100.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 5.0f, -1);
	}

	enemy[0].Load("Models/enemy0.x", "Textures/enemy0.png");
	enemy[1].Load("Models/enemy1.x", "Textures/enemy1.png");
	enemy[2].Load("Models/enemy2.x", "Textures/enemy2.png");

	player.rotation.y = D3DX_PI;

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

	for (int i = 0; i < 30; ++i)
	{
		enemyExist[i] = true;
	}
}

MainScene::~MainScene()
{

}

MainScene& MainScene::GetInstance()
{
	static MainScene instance;

	return instance;
}

// çXêVèàóù
void MainScene::Update()
{
	camera.position.x = player.position.x;

	if (Input::GetKey(DIK_LEFTARROW))
	{
		playerVelocity -= 0.1f;
	}

	if (Input::GetKey(DIK_RIGHTARROW))
	{
		playerVelocity += 0.1f;
	}

	playerVelocity *= 0.8f;

	player.position.x += playerVelocity;

	if (player.position.x < -20.0f)
	{
		playerVelocity = 1.0f;
	}
	if (player.position.x > 20.0f)
	{
		playerVelocity = -1.0f;
	}

	player.rotation.z = -playerVelocity;

	for (int i = 0; i < 10; ++i)
	{
		jet.Set(player.position + D3DXVECTOR3(Random::FloatRange(-0.3f, 0.3), Random::FloatRange(-0.3f, 0.3), Random::FloatRange(-0.3f, 0.3)), D3DXVECTOR3(0.0f, 0.0f, Random::FloatRange(-1.0f, -0.5f)), 0.0f, Random::FloatRange(2.0f, 3.0f), Random::IntRange(3, 5));
	}

	if (Input::GetKey(DIK_Z))
	{
		if (bulletExist == false || bulletPosition.z > 40.0f)
		{
			bulletPosition = player.position;
			bulletExist = true;
		}
	}

	if (bulletExist)
	{
		bulletPosition.z += 2.0f;

		for (int i = 0; i < 10; ++i)
		{
			bullet.Set(bulletPosition + D3DXVECTOR3(Random::FloatRange(-0.3f, 0.3), Random::FloatRange(-0.3f, 0.3), Random::FloatRange(-0.3f, 0.3)), D3DXVECTOR3(0.0f, 0.0f, Random::FloatRange(-1.0f, -0.5f)), 0.0f, Random::FloatRange(2.0f, 3.0f), Random::IntRange(3, 5));
		}

		for (int z = 0; z < 3; ++z)
		{
			for (int x = 0; x < 10; ++x)
			{
				if (enemyExist[x + z * 10])
				{

				}
			}
		}
	}
}

// ï`âÊèàóù
void MainScene::Draw()
{
	camera.View();

	jet.Draw();

	star.Draw();

	player.Draw();

	if (bulletExist)
	{
		bullet.Draw();
	}
}
