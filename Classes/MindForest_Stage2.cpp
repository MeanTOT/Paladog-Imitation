#include "MindForest_Stage2.h"
#include "MapMindForestScene.h"

bool MindForest_Stage2::_isComplete = false;

Scene* MindForest_Stage2::createScene() {
	return MindForest_Stage2::create();
}

bool MindForest_Stage2::init() {
	if (!Scene::init()) {
		return false;
	}

	_soundBs = AudioEngine::play2d("Sound/start_battle.mp3", false, 1.f);

	_bgLayer = Layer::create();
	this->addChild(_bgLayer, -100);

	Hero::getInstance()->createHeroInfo(this, _bgLayer);
	_heroControl = new HeroControl(this, _bgLayer, _dungeon);
	_dungeon = new Dungeon(this, _bgLayer, 20000.0f); //3번째 인자에 체력 넣음
	_servecScene = new ServiceScene(this);

	this->schedule(schedule_selector(MindForest_Stage2::tick));
	this->schedule(schedule_selector(MindForest_Stage2::HeroManaRegen), Hero::getInstance()->getManaRegenSpeed());
	this->schedule(schedule_selector(MindForest_Stage2::HeroMeatRegen), Hero::getInstance()->getMeatRegenSpeed());

	// 배경이미지 plist
	_cache = SpriteFrameCache::getInstance();
	_cache->addSpriteFramesWithFile("UI/Background/background_04.plist");

	// 배경이미지 만들기.
	_backGround1 = Sprite::createWithSpriteFrameName("background_04_a.png");
	_backGround1->setPosition({ 0,525 });
	_backGround1->setAnchorPoint({ 0,1 });

	// 이미지가 짧아서 여러장 붙힘
	_backGround2 = Sprite::createWithSpriteFrameName("background_04_b.png");
	_backGround2->setPosition({ 0,525 });
	_backGround2->setAnchorPoint({ 0,1 });
	_backGround2_1 = Sprite::createWithSpriteFrameName("background_04_b.png");
	_backGround2_1->setPosition({ 752,525 });
	_backGround2_1->setAnchorPoint({ 0,1 });

	_backGround3 = Sprite::createWithSpriteFrameName("background_04_c.png");
	_backGround3->setPosition({ 0,525 });
	_backGround3->setAnchorPoint({ 0,1 });

	// 이미지가 짧아서 여러장 붙힘
	_backGround3_1 = Sprite::createWithSpriteFrameName("background_04_c.png");
	_backGround3_1->setPosition({ 480,525 });
	_backGround3_1->setAnchorPoint({ 0,1 });
	_backGround3_2 = Sprite::createWithSpriteFrameName("background_04_c.png");
	_backGround3_2->setPosition({ 960,525 });
	_backGround3_2->setAnchorPoint({ 0,1 });

	// 이미지가 만나는 가장자리에 검은선이 생기는 현상을 방지
	_backGround1->getTexture()->setAliasTexParameters();
	_backGround2->getTexture()->setAliasTexParameters();
	_backGround2_1->getTexture()->setAliasTexParameters();
	_backGround3->getTexture()->setAliasTexParameters();
	_backGround3_1->getTexture()->setAliasTexParameters();
	_backGround3_2->getTexture()->setAliasTexParameters();

	// 배경레이어에 추가
	_bgLayer->addChild(_backGround1, -1000);
	_bgLayer->addChild(_backGround2, -1010);
	_bgLayer->addChild(_backGround2_1, -1010);
	_bgLayer->addChild(_backGround3, -1020);
	_bgLayer->addChild(_backGround3_1, -1020);
	_bgLayer->addChild(_backGround3_2, -1020);

	// Follow 액션으로 화면이동구현
	_bgLayer->runAction(Follow::create(Hero::getInstance()->getHero(), Rect(0, 0, 1024, 512)));

	// 겟 레디 화면
	_servecScene->GetReady();

	// 사운드

	BgSoundClear = false;

	Hero::getInstance()->setStageKind(Stage1And2);

	Hero::getInstance()->getHeroBuffOra()->runAction(Hero::getInstance()->getOraAct());

	return true;
}

void MindForest_Stage2::tick(float delta)
{
	if (AudioEngine::getState(_soundBs) != AudioEngine::AudioState::PLAYING && AudioEngine::getState(_soundBg1) != AudioEngine::AudioState::PLAYING && !BgSoundClear)
	{
		_soundBg1 = AudioEngine::play2d("Sound/bg_stage.mp3", true, 0.6);
		BgSoundClear = true;
	}

	if (Hero::getInstance()->getStageStart())
		MonsterTick();

	for (int i = 0; i < _heroControl->getHeroUnitVec().size(); i++)
	{
		_heroControl->getHeroUnitVec()[i]->BringMonsterVec(_monster);

		// 힐 스킬 사용시 작동
		if (Hero::getInstance()->getIsHealing())
			_heroControl->getHeroUnitVec()[i]->Healing();
	}

	// 모든 객체의 힐이 끝나면 힐 스킬 비활성화 상태로 돌려줌
	Hero::getInstance()->setIsHealing(false);

	// 스킬 1 미사일 과 몬스터 유닛 충돌 처리
	for (int i = 0; i < _heroControl->getMissileCollisionVec().size(); i++)
	{
		_heroControl->getMissileCollisionVec()[i]->BringMonsterVec(_monster, _dungeon);
	}

	_heroControl->HeroMove(_dungeon); // 히어로 각종 조작
	_heroControl->UnitVecErase(); // 유닛백터 삭제
	_heroControl->CoolTime(); // 쿨타임 계산

	// 스테이지 클리어 화면
	_servecScene->StageClear();

	if (_dungeon->getHp() <= 0)
	{
		if (!Hero::getInstance()->getStageClear())
		{
			AudioEngine::stop(_soundBg1);
			AudioEngine::play2d("Sound/stage_clear.mp3", false, 1.0f);
			Hero::getInstance()->setStageClear(true);
		}
	}

	// 씬 전환
	if (Hero::getInstance()->getSceneChange())
	{
		AudioEngine::stopAll();
		AudioEngine::uncacheAll();
        _isComplete = true;
		Hero::getInstance()->setSceneChange(false);
		auto scene = MapMindForestScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}

}

void MindForest_Stage2::HeroManaRegen(float delta)
{
	if (Hero::getInstance()->getStageStart() && !Hero::getInstance()->getStageClear())
		_heroControl->HeroManaRegen(); // 마나리젠
}

void MindForest_Stage2::HeroMeatRegen(float delta)
{
	if (Hero::getInstance()->getStageStart() && !Hero::getInstance()->getStageClear())
		_heroControl->HeroMeatRegen(); // 고기리젠
}

void MindForest_Stage2::MonsterTick()
{
	if (!_dungeon->getIsCrash()) {
		if (rand() % 500 == 0) {
			_monster.push_back(new Monster(this, _bgLayer, _heroControl->getHeroUnitVec(), Mob::강화좀비));
		}
		if (rand() % 1500 == 0) {
			_monster.push_back(new Monster(this, _bgLayer, _heroControl->getHeroUnitVec(), Mob::광부좀비));
		}
		if (rand() % 2200 == 0) {
			_monster.push_back(new Monster(this, _bgLayer, _heroControl->getHeroUnitVec(), Mob::일반미라));
		}
	}
	for (int i = 0; i < _monster.size(); i++) {
		if (_monster[i]->getUnitAttack() != -1 &&
			_monster[i]->getUnitAttack() < _heroControl->getHeroUnitVec().size()) {
			_heroControl->getHeroUnitVec()[_monster[i]->getUnitAttack()]->setHp(_heroControl->getHeroUnitVec()[_monster[i]->getUnitAttack()]->getHp() - _monster[i]->getAtk());
			_monster[i]->setUnitAttack();
		}
		if (_dungeon->getIsCrash()) {
			_monster[i]->Hit(999999);
		}
		if (_heroControl->getHeroUnitVec().size() != _monster[i]->getUnitSize()) {
			_monster[i]->setUnit(_heroControl->getHeroUnitVec());
		}
		_monster[i]->MonsterMove();
		if (_monster[i]->getIsRemove()) {
			_bgLayer->removeChild(_monster[i]->getMonster());
			_monster.erase(_monster.begin() + i);
		}
	}
}