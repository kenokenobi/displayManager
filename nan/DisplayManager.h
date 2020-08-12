#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <nan.h>
#include <Winuser.h>

class DisplayManager : public Nan::ObjectWrap
{
public:
	explicit DisplayManager();
	~DisplayManager();

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);
	static NAN_METHOD(GetDisplays);
	static NAN_METHOD(SleepDevice);
	static NAN_METHOD(WakeDevice);
	static NAN_METHOD(GetLastInputTime);

private:
	static LASTINPUTINFO last_;
	static std::vector<DISPLAY_DEVICE> getDisplayDevices();
	static v8::Local<v8::Object> convertToObjects(const Nan::FunctionCallbackInfo<v8::Value>& info,
		const std::vector<DISPLAY_DEVICE>& devices);
	static Nan::Persistent<v8::Function> constructor;
};

#endif  // DISPLAY_MANAGER_H
