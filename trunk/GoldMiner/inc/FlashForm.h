#ifndef _FLASHFORM_H_
#define _FLASHFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FSystem.h>

class FlashForm :
	public Osp::Ui::Controls::Form
{

public:
	static const int REQUEST_FLASH_PLAY = 100;

public:
	FlashForm(void);
	virtual ~FlashForm(void);

	bool Initialize(void);
	void Play(void);
	void Pause(void);
	void Resume(void);
	void SetSoundStatus(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	virtual void OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs);

private:
	Osp::Ui::Controls::Flash *__pFlash;
	bool __soundProperty;
};

#endif
