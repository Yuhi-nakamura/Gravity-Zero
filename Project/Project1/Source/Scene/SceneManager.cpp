#include "SceneManager.h"


//最初に開かれるシーンを初期値
Scene g_NowScene = SCENE_PLAY;

//つぎに遷移するシーン
Scene g_NextScene = SCENE_TITLE;

//シーンの状態
SceneState g_SceneState = SCENE_STATE_INIT;

//ループの終了
bool g_IsLoopEnd = false;

void SceneManagerUpdate()
{
	//シーンの状態ごとに各シーンの処理
	switch (g_SceneState)
	{
	case SCENE_STATE_INIT:
		InitScene(); //初期化

		//ロード
		g_SceneState = SCENE_STATE_LOAD;
		break;
	case SCENE_STATE_LOAD:
		LoadScene();

		//ループ終了フラグを折る
		g_IsLoopEnd = false;

		//開始
		g_SceneState = SCENE_STATE_START;
		break;
	case SCENE_STATE_START:
		StartScene();

		g_SceneState = SCENE_STATE_LOOP;
		break;
	case SCENE_STATE_LOOP:
		StepScene();
		UpdateScene();
		DrawScene();

		//ループ終了フラグがたったら終了
		if (g_IsLoopEnd)
		{
			g_SceneState = SCENE_STATE_FIN;
		}
		break;
	case SCENE_STATE_FIN:
		FinScene();

		//次のシーンに切り替え
		g_NowScene = g_NextScene;
		//シーンは初期化から
		g_SceneState = SCENE_STATE_INIT;
		break;
	}
}

void InitScene()
{
	//開いているシーンの初期化
	switch (g_NowScene)
	{
	case SCENE_TITLE: //タイトル
		//InitTitle();
		break;
	case SCENE_PLAY: //プレイ
	 	//InitPlay();
		break;
	case SCENE_GAME_CLEAR: //ゲームクリア
		//InitGameClear();
		break;
	}
}

void LoadScene()
{
	//開いているシーンのロード
	switch (g_NowScene)
	{
	case SCENE_TITLE:
		//LoadTitle();
		break;
	case SCENE_PLAY:
		//LoadPlay();
		break;
	case SCENE_GAME_CLEAR:
		//LoadGameClear();
		break;
	}
}

void StartScene()
{
	switch (g_NowScene)
	{
	case SCENE_TITLE:
		//StartTitle();
		break;
	case SCENE_PLAY:
		//StartPlay();
		break;
	case SCENE_GAME_CLEAR:
		//StartGameClear();
		break;
	}
}

void StepScene()
{
	switch (g_NowScene)
	{
	case SCENE_TITLE:
		//StepTitle();
		break;
	case SCENE_PLAY:
		//StepPlay();
		break;
	case SCENE_GAME_CLEAR:
		//StepGameClear();
		break;
	}
}

void UpdateScene()
{
	switch (g_NowScene)
	{
	case SCENE_TITLE:
		//UpdateTitle();
		break;
	case SCENE_PLAY:
		//UpdatePlay();
		break;
	case SCENE_GAME_CLEAR:
		//UpdateGameClear();
		break;
	}
}

void DrawScene()
{
	switch (g_NowScene)
	{
	case SCENE_TITLE:
		//DrawTitle();
		break;
	case SCENE_PLAY:
		//DrawPlay();
		break;
	case SCENE_GAME_CLEAR:
		//DrawGameClear();
		break;
	}
}

void FinScene()
{
	switch (g_NowScene)
	{
	case SCENE_TITLE:
		//FinTitle();
		break;
	case SCENE_PLAY:
		//FinPlay();
		break;
	case SCENE_GAME_CLEAR:
		//FinGameClear();
		break;
	}
}

void ChangeScene(Scene scene)
{
	// 次に遷移するシーンを設定
	g_NextScene = scene;

	// シーンのループを終了させる
	g_IsLoopEnd = true;
}
