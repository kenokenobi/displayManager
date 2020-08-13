var addon = require('bindings')('DisplayManager');

function main()
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

function sum(a, b)
{
	return a + b;
}

main();