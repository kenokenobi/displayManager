#include "DisplayManager.h"

Nan::Persistent<v8::Function> DisplayManager::constructor;

LASTINPUTINFO DisplayManager::last_;

DisplayManager::DisplayManager()
{
	last_.cbSize = sizeof(LASTINPUTINFO);
	GetLastInputInfo(&last_);
}

DisplayManager::~DisplayManager()
{}

NAN_MODULE_INIT(DisplayManager::Init)
{
	v8::Local<v8::Context> context = target->CreationContext();
	Nan::HandleScope scope;
	// Prepare constructor template
	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("DisplayManager").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	Nan::SetPrototypeMethod(tpl, "getAttachedDisplays", GetDisplays);
	Nan::SetPrototypeMethod(tpl, "sleep", SleepDevice);
	Nan::SetPrototypeMethod(tpl, "wakey", WakeDevice);
	Nan::SetPrototypeMethod(tpl, "getLastInputTime", GetLastInputTime);

	constructor.Reset(tpl->GetFunction(context).ToLocalChecked());

	target->Set(context, Nan::New("DisplayManager").ToLocalChecked(), tpl->GetFunction(context).ToLocalChecked());
}

NAN_METHOD(DisplayManager::New)
{
   if(!info.IsConstructCall())
   {
      return Nan::ThrowError(Nan::New("In C++: DisplayManager::New - called without new keyword").ToLocalChecked());
   }

   if(info.Length() != 0)
   {
      return Nan::ThrowError(Nan::New("In C++: DisplayManager::New - Expected 0 parameters").ToLocalChecked());
   }

   DisplayManager *def = new DisplayManager();
   def->Wrap(info.Holder());

   info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(DisplayManager::GetDisplays)
{
	v8::Isolate* isolate = info.GetIsolate();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();
	auto type = v8::NewStringType::kNormal;

	std::vector<DISPLAY_DEVICE> devices = getDisplayDevices();

	info.GetReturnValue().Set(convertToObjects(info, devices));
}

NAN_METHOD(DisplayManager::SleepDevice)
{
	SendMessage(GetConsoleWindow(),WM_SYSCOMMAND,SC_MONITORPOWER, (LPARAM)2);
	Sleep(5000);
}

NAN_METHOD(DisplayManager::WakeDevice)
{
	mouse_event(MOUSEEVENTF_MOVE, 0, 1, 0, NULL);
	Sleep(40);
	mouse_event(MOUSEEVENTF_MOVE, 0, -1, 0, NULL);
}

NAN_METHOD(DisplayManager::GetLastInputTime)
{
	float elapsed = GetTickCount() - last_.dwTime;
	info.GetReturnValue().Set(elapsed);
}

std::vector<DISPLAY_DEVICE> DisplayManager::getDisplayDevices()
{
	std::vector<DISPLAY_DEVICE> devices;

	DISPLAY_DEVICE dev;
	int devIndex = 0;
	dev.cb = sizeof(dev);

	while(EnumDisplayDevices(NULL, devIndex++, &dev, 0))
	{
		DISPLAY_DEVICE monitor;
		std::string name = dev.DeviceName;
		int monitorIndex = 0;
		monitor.cb = sizeof(monitor);

		while(EnumDisplayDevices(name.c_str(), monitorIndex++, &monitor, 0))
		{
			devices.push_back(monitor);
		}
	}

	return devices;
}

v8::Local<v8::Object> DisplayManager::convertToObjects(const Nan::FunctionCallbackInfo<v8::Value>& info,
	const std::vector<DISPLAY_DEVICE>& devices)
{
	auto isolate = info.GetIsolate();
	v8::Local<v8::Object> result = v8::Object::New(isolate);
	auto type = v8::NewStringType::kNormal;

	for (int i = 0; i < devices.size(); i++)
	{
		v8::Local<v8::Object> dev = v8::Object::New(isolate);
		dev->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(info.GetIsolate(),
			"index", v8::NewStringType::kNormal).ToLocalChecked(), v8::Number::New(isolate, i));
		dev->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "deviceName", type).ToLocalChecked(),
			v8::String::NewFromUtf8(isolate, devices[i].DeviceName, type).ToLocalChecked());
		dev->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "deviceDescription", type).ToLocalChecked(),
			v8::String::NewFromUtf8(isolate, devices[i].DeviceString, type).ToLocalChecked());
		dev->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "deviceID", type).ToLocalChecked(),
			v8::String::NewFromUtf8(isolate, devices[i].DeviceID, type).ToLocalChecked());
		dev->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "deviceKey", type).ToLocalChecked(),
			v8::String::NewFromUtf8(isolate, devices[i].DeviceKey, type).ToLocalChecked());

		result->Set(info.GetIsolate()->GetCurrentContext(), v8::String::NewFromUtf8(isolate,
			"display", type).ToLocalChecked(), dev);
	}
	return result;
}
