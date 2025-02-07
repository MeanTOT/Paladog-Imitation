#include "AppDelegate.h"
#include "MindForest_Stage1.h"
#include "MindForest_Stage2.h"
#include "MindForest_Stage3.h"
#include "ShopScene.h"
#include "IntroScene.h"
#include "UpgradeScene.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
#if USE_AUDIO_ENGINE
  AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
  SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs() {
  // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
  GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

  GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages() {
  return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  auto director = Director::getInstance();
  auto glview = director->getOpenGLView();
  if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    glview = GLViewImpl::createWithRect("practice", cocos2d::Rect(0, 0, 1280, 720));
#else
    glview = GLViewImpl::create("practice");
#endif
    director->setOpenGLView(glview);
  }

  // turn on display FPS
  director->setDisplayStats(false);

  // set FPS. the default value is 1.0/60 if you don't call this
  director->setAnimationInterval(1.0f / 60);

  // Set the design resolution
  glview->setDesignResolutionSize(480, 320, ResolutionPolicy::EXACT_FIT);

  // create a scene. it's an autorelease object
  auto scene = IntroScene::createScene();

  // run
  director->runWithScene(scene);

  return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
  Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
  AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
  SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
  SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
  Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
  AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
  SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
  SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
