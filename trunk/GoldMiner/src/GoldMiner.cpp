#include "GoldMiner.h"
#include "FlashForm.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

GoldMiner::GoldMiner() :
			__pFlashForm(null)
{
}

GoldMiner::~GoldMiner()
{
}

Application*
GoldMiner::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new GoldMiner();
}

bool
GoldMiner::OnAppInitializing(AppRegistry& appRegistry)
{
	// TODO:
	// Initialize UI resources and application specific data.
	// The application's permanent data and context can be obtained from the appRegistry.
	//
	// If this method is successful, return true; otherwise, return false.
	// If this method returns false, the application will be terminated.

	// Uncomment the following statement to listen to the screen on/off events.
	//PowerManager::SetScreenEventListener(*this);

	// Create a form
	__pFlashForm = new FlashForm();
	__pFlashForm->Initialize();

	// Add the form to the frame
	Frame *pFrame = GetAppFrame()->GetFrame();
	pFrame->AddControl(*__pFlashForm);

	// Set the current form
	pFrame->SetCurrentForm(*__pFlashForm);

	DeviceManager::AddDeviceEventListener(BluetoothHeadset , *this);
	DeviceManager::AddDeviceEventListener(WiredHeadset, *this);
	DeviceManager::AddDeviceEventListener(WiredHeadphone, *this);

	// Draw and Show the form
	__pFlashForm->Draw();
	__pFlashForm->Show();

	return true;
}

bool
GoldMiner::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this application for termination.
	// The application's permanent data and context can be saved via appRegistry.
	return true;
}

void
GoldMiner::OnForeground(void)
{
	// TODO:
	// Start or resume drawing when the application is moved to the foreground.
	if(__pFlashForm)
	{
		__pFlashForm->Resume();
	}
}

void
GoldMiner::OnBackground(void)
{
	// TODO:
	// Stop drawing when the application is moved to the background.
	AppUiState appUiState = Osp::App::Application::GetInstance()->GetAppUiState();

	if(appUiState == APP_UI_STATE_PARTIAL_BACKGROUND)
	{
		return;
	}

	if(__pFlashForm)
	{
		__pFlashForm->Pause();
	}
}

void
GoldMiner::OnDeviceStateChanged(Osp::System::DeviceType deviceType, const Osp::Base::String& state)
{
	__pFlashForm->SetSoundStatus();
}

void
GoldMiner::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}

void
GoldMiner::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void
GoldMiner::OnScreenOn (void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void
GoldMiner::OnScreenOff (void)
{
	// TODO:
	//  Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}
