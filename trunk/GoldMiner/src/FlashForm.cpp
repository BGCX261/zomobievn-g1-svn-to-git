#include "FlashForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::System;

FlashForm::FlashForm() :
		__pFlash(null),
		__soundProperty(true)
{

}

FlashForm::~FlashForm()
{

}

bool
FlashForm::Initialize()
{
	Construct(L"IDF_FLASHFORM");

	return true;
}

result
FlashForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	// Get a flash via resource ID
	__pFlash = static_cast<Flash *>(GetControl(L"IDC_FLASH1"));
	__soundProperty = __pFlash->IsSoundEnabled();
	SendUserEvent(REQUEST_FLASH_PLAY, null);

	return r;
}

result
FlashForm::OnTerminating(void)
{
	// TODO: Add your termination code here

	return E_SUCCESS;
}

void
FlashForm::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs)
{
	if(requestId == REQUEST_FLASH_PLAY)
	{
		Draw();
		Show();

		Play();
	}
}

void
FlashForm::Play(void)
{
	SetSoundStatus();

	__pFlash->Play();
}

void
FlashForm::Pause(void)
{
	__pFlash->Pause();
}

void
FlashForm::Resume(void)
{
	SetSoundStatus();

	//__pFlash->Resume();
}

void
FlashForm::SetSoundStatus()
{
	if(__soundProperty == true)
	{
		bool silentMode;
		String stateWiredHeadSet, stateWiredHeadPhone, stateBluetoothHeadSet;

		DeviceManager::GetState(WiredHeadset, stateWiredHeadSet);
		DeviceManager::GetState(WiredHeadphone, stateWiredHeadPhone);
		DeviceManager::GetState(BluetoothHeadset, stateBluetoothHeadSet);

		if(stateWiredHeadSet == L"Inserted" || stateWiredHeadPhone == L"Inserted" || stateBluetoothHeadSet == L"Inserted")
		{
			__pFlash->SetSoundEnabled(true);
		}
		else if(stateWiredHeadSet == L"Removed" || stateWiredHeadPhone == L"Removed" || stateBluetoothHeadSet == L"Removed")
		{
			SettingInfo::GetValue(L"SilentMode", silentMode);
			__pFlash->SetSoundEnabled(!silentMode);
		}
	}
	else
	{
		__pFlash->SetSoundEnabled(false);
	}
}

