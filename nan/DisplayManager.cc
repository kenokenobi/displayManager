#include <nan.h>
#include <Winuser.h>
#include <iostream>

LASTINPUTINFO last;

std::vector<DISPLAY_DEVICE> getDisplayDevices()
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

v8::Local<v8::Object> convertToObjects(const Nan::FunctionCallbackInfo<v8::Value>& info,
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

void GetDisplays(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	v8::Isolate* isolate = info.GetIsolate();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();
	auto type = v8::NewStringType::kNormal;

	std::vector<DISPLAY_DEVICE> devices = getDisplayDevices();

	info.GetReturnValue().Set(convertToObjects(info, devices));
}

void SleepDevice(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	SendMessage(GetConsoleWindow(),WM_SYSCOMMAND,SC_MONITORPOWER, (LPARAM)2);
	Sleep(5000);
}

void WakeDevice(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	mouse_event(MOUSEEVENTF_MOVE, 0, 1, 0, NULL);
	Sleep(40);
	mouse_event(MOUSEEVENTF_MOVE, 0, -1, 0, NULL);
}

void GetLastInputTime(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	float elapsed = GetTickCount() - last.dwTime;
	info.GetReturnValue().Set(elapsed);
}

void Init(v8::Local<v8::Object> exports) {
	last.cbSize = sizeof(LASTINPUTINFO);
	GetLastInputInfo(&last);

  	v8::Local<v8::Context> context = exports->CreationContext();

  	exports->Set(context,
              	Nan::New("getAttachedDisplays").ToLocalChecked(),
              	Nan::New<v8::FunctionTemplate>(GetDisplays)
                  	->GetFunction(context)
                  	.ToLocalChecked());

	exports->Set(context,
          	Nan::New("sleep").ToLocalChecked(),
          	Nan::New<v8::FunctionTemplate>(SleepDevice)
              	->GetFunction(context)
              	.ToLocalChecked());

	exports->Set(context,
          	Nan::New("wakey").ToLocalChecked(),
          	Nan::New<v8::FunctionTemplate>(WakeDevice)
              	->GetFunction(context)
              	.ToLocalChecked());

	exports->Set(context,
          	Nan::New("getLastInputTime").ToLocalChecked(),
          	Nan::New<v8::FunctionTemplate>(GetLastInputTime)
              	->GetFunction(context)
              	.ToLocalChecked());
}

NODE_MODULE(DisplayManager, Init)
