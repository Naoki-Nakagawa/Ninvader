#ifndef _Ninvader_Scene_h_
#define _Ninvader_Scene_h_

// �V�[���̃N���X
class Scene
{
private:

	static Scene* scene;

public:

	static void SetScene(Scene& newScene);

	static Scene& GetScene();

	// �X�V����
	virtual void Update() = 0;

	// �`�揈��
	virtual void Draw() = 0;
};

#endif	// _Ninvader_Scene_h_
