#ifndef _Ninvader_TitleScene_h_
#define _Ninvader_TitleScene_h_

#include <array>
#include "Camera.h"
#include "Font.h"
#include "Mesh.h"
#include "Particle.h"
#include "Scene.h"

// タイトルシーン
class TitleScene : public Scene
{
private:

	gdk::dx9::Camera camera;
	std::array<gdk::dx9::Mesh, 3> enemy;
	gdk::dx9::Particle star;
	gdk::dx9::Font fontL;
	gdk::dx9::Font fontS;
	float enemyRotationScale;
	int highScore;

	// デフォルトコンストラクタ
	TitleScene();

	// デストラクタ
	~TitleScene();

public:

	static TitleScene& GetInstance();

	// 更新処理
	virtual void Update();

	// 描画処理
	virtual void Draw();
};

#endif	// _Ninvader_TitleScene_h_
