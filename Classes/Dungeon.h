#pragma once
#include "cocos_framework.h"

class Dungeon : Scene
{
	enum STATE {
		���̻�,
		������,
		������
	};
	Scene* _scene;
	Layer* _layer;

	SpriteFrameCache* cache;

	STATE _state;

	Sprite* _sprite1;
	Sprite* _sprite2;
	Sprite* _sprite3;

	float _hpm, _hp;

public:

	Dungeon(Scene* scene, Layer* layer, float hp);

	void Hit(float atk);
	float getHpm() { return _hpm; }
	float getHp() { return _hp; }
	bool getIsCrash() { return _state == ������ ? 1 : 0; }

	Sprite* getMonsterBase() { return _sprite1; }

	void test();
};