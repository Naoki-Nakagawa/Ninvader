#ifndef _Ninvader_Scene_h_
#define _Ninvader_Scene_h_

// シーンのクラス
class Scene
{
private:

	static Scene* scene;

public:

	static void SetScene(Scene& newScene);

	static Scene& GetScene();

	// 更新処理
	virtual void Update() = 0;

	// 描画処理
	virtual void Draw() = 0;
};

#endif	// _Ninvader_Scene_h_
