#pragma once

//シ－ンの種類
enum Scene
{
	SCENE_NONE,
	SCENE_TITLE,
	SCENE_PLAY,
	SCENE_GAME_CLEAR,
};

//状態
enum SceneState
{
	SCENE_STATE_INIT,
	SCENE_STATE_LOAD,
	SCENE_STATE_START,
	SCENE_STATE_LOOP,
	SCENE_STATE_FIN,
};

//関数

//シーン管理の更新
void SceneManagerUpdate();

void InitScene();
void LoadScene();
void StartScene();
void StepScene();
void UpdateScene();
void DrawScene();
void FinScene();

//切り替え
void ChangeScene();