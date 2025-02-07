#ifndef __INTROUI_H__
#define __INTROUI_H__

#include "cocos_framework.h"

class IntroUI
{
 public:
  IntroUI(Scene* pScene);
  void SetTitleLogo(Scene* pScene);
  Sprite* GetTitleLogo() {
    return _titleLogo;
  }
  void SetTitleBtnNewgameUp(Scene* pScene);
  Sprite* GetTitleBtnNewgameUp() {
    return _titleBtnNewgameUp;
  }
  void SetTitleBtnInfoUp(Scene* pScene);
  Sprite* GetTitleBtnInfoUp() {
    return _titleBtnInfoUp;
  }
  void SetTitleLogoCrown(Scene* pScene);
  Sprite* GetTitleLogoCrown() {
    return _titleLogoCrown;
  }
  void SetModeSelectBox(Scene* pScene);
  Sprite* GetModeSelectBox() {
    return _modeSelectBox;
  }
  void SetTxtHeroSelect(Scene* pScene);
  Sprite* GetTxtHeroSelect() {
    return _txtHeroSelect;
  }
  void SetHeroPaladogUp(Scene* pScene);
  Sprite* GetHeroPaladogUp() {
    return _heroPaladogUp;
  }
  void SetHeroDarkdogUp(Scene* pScene);
  Sprite* GetHeroDarkdogUp() {
    return _heroDarkdogUp;
  }
  void SetBtnCampaignUp(Scene* pScene);
  Sprite* GetBtnCampaignUp() {
    return _btnCampaignUp;
  }
  void SetBtnSurvivalUp(Scene* pScene);
  Sprite* GetBtnSurvivalUp() {
    return _btnSurvivalUp;
  }
  void SetDataSlot(Scene* pScene);
  Sprite* GetDataSlot() {
    return _dataSlot;
  }
  void SetSlotInfoEmpty(Scene* pScene);
  Sprite* GetSlotInfoEmpty() {
    return _slotInfoEmpty;
  }
  void SetMsgSelectSlot(Scene* pScene);
  Sprite* GetMsgSelectSlot() {
    return _msgSelectSlot;
  }
  void SetBtnExitUp(Scene* pScene);
  Sprite* GetBtnExitUp() {
    return _btnExitUp;
  }
  void SetStart(Scene* pScene);
  Sprite* GetStart() {
    return _start;
  }
  void SetDelete(Scene* pScene);
  Sprite* GetDelete() {
    return _delete;
  }
  void SetMsgBox(Scene* pScene);
  Sprite* GetMsgBox() {
    return _msgBox;
  }
  void SetBtnCatUp(Scene* pScene);
  Sprite* GetBtnCatUp() {
    return _btnCatUp;
  }
 private:
  SpriteFrameCache* _cache;
  Sprite* _titleLogo;
  Sprite* _titleBtnNewgameUp;
  Sprite* _titleBtnInfoUp;
  Sprite* _titleLogoCrown;
  Sprite* _btnCatUp;
  Sprite* _modeSelectBox;
  Sprite* _txtHeroSelect;
  Sprite* _heroPaladogUp;
  Sprite* _heroDarkdogUp;
  Sprite* _btnCampaignUp;
  Sprite* _btnSurvivalUp;
  Sprite* _dataSlot;
  Sprite* _slotInfoEmpty;
  Sprite* _msgSelectSlot;
  Sprite* _btnExitUp;
  Sprite* _start;
  Sprite* _delete;
  Sprite* _msgBox;
};

#endif // __INTROUI_H__
