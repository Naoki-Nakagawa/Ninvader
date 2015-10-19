#ifndef _Ninvader_MainScene_h_
#define _Ninvader_MainScene_h_

#include <array>
#include "Camera.h"
#include "Mesh.h"
#include "Particle.h"
#include "Scene.h"

// メインシーン
class MainScene : public Scene
{
private:

	gdk::dx9::Camera camera;
	gdk::dx9::Mesh player;
	gdk::dx9::Particle jet;
	float playerVelocity;
	std::array<gdk::dx9::Mesh, 3> enemy;
	gdk::dx9::Particle star;
	bool enemyExist[30];
	float enemySpeed;
	float enemyRotationScale;
	float enemyScaleScale;
	int score;
	int highScore;

	bool bulletExist;
	gdk::dx9::Particle bullet;
	D3DXVECTOR3 bulletPosition;

	// デフォルトコンストラクタ
	MainScene();

	// デストラクタ
	~MainScene();

public:

	static MainScene& GetInstance();

	// 更新処理
	virtual void Update();

	// 描画処理
	virtual void Draw();
};

#endif	// _Ninvader_MainScene_h_
