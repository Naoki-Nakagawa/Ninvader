#ifndef _Ninvader_MainScene_h_
#define _Ninvader_MainScene_h_

#include <array>
#include "Camera.h"
#include "Mesh.h"
#include "Particle.h"
#include "Scene.h"

// ���C���V�[��
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

	// �f�t�H���g�R���X�g���N�^
	MainScene();

	// �f�X�g���N�^
	~MainScene();

public:

	static MainScene& GetInstance();

	// �X�V����
	virtual void Update();

	// �`�揈��
	virtual void Draw();
};

#endif	// _Ninvader_MainScene_h_
