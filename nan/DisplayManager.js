var addon = require('bindings')('DisplayManager');

function enumerateDisplays(displayManager)
{
	var displays = displayManager.getAttachedDisplays();

	if (displays  === undefined)
	{
		throw "Unknown Error: DisplayManager did not return anthing";
	}

	console.log(displays);
	return displays;
}

function sleep(displayManager)
{
	displayManager.sleep();
}

function wakeUp(displayManager)
{
	displayManager.wakey();
}

function getLastInputTime(displayManager)
{
	return displayManager.getLastInputTime();
}

function testRun()
{
	var displayManager = new addon.DisplayManager();
	enumerateDisplays(displayManager);
	console.log("Last Input Time(ms): " + getLastInputTime(displayManager));
	sleep(displayManager);
	console.log("Last Input Time(ms): " + getLastInputTime(displayManager));
	setTimeout(function() {
		wakeUp(displayManager);
		console.log("Last Input Time(ms): " + getLastInputTime(displayManager));
	}, 5000);
}

module.exports.enumerateDisplays = enumerateDisplays;
module.exports.sleep = sleep;
module.exports.wakeUp = wakeUp;
module.exports.getLastInputTime = getLastInputTime;

testRun();