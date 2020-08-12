var addon = require('bindings')('DisplayManager');

function main()
{
	var displayManager = new addon.DisplayManager();
	enumerateDisplays(displayManager);
	console.log("Last Input Time(ms): " + getLastInputTime(displayManager));
	sleep(displayManager);
	console.log("Last Input Time(ms): " + getLastInputTime(displayManager));
	wakeUp(displayManager);
	console.log("Last Input Time(ms): " + getLastInputTime(displayManager));
}

function enumerateDisplays(displayManager)
{
	console.log(displayManager.getAttachedDisplays());
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

main();