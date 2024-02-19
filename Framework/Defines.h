#pragma once

enum class Origins
{
	// T M B
	// L C R
	TL, TC, TR, ML, MC, MR, BL, BC, BR, CUSTOM,
};

enum class Sides
{
	NONE = -1, LEFT, RIGHT, COUNT
};

enum class SceneIds
{
	NONE = -1, SCENE_TITLE, SCENE_MENU, SCENE_CHARACTER, SCENE_GAME, SCENE_GAME_2, COUNT,
};

enum class GameMode
{
	Single,
	Multi,
	Player1,
	Player2
};