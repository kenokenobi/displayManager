var addon = require('bindings')('DisplayManager');
var _ = require('underscore');

function enumerateDisplays(objs)
{
	_.each(objs, function(obj) {
		console.log(obj);
	});
}

function main()
{
	var objs = addon.getAttachedDisplays();
	enumerateDisplays(objs);
	addon.sleep();
	addon.wakey();

	var lastInputTime = addon.getLastInputTime();
	console.log("Last Input Time(ms): " + lastInputTime);
}

main();