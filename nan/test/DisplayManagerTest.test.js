const dm = require('../DisplayManager');
var addon = require('bindings')('DisplayManager');

describe('DisplayManager', () => {

    var obj = new addon.DisplayManager();

    function enumerateDisplays() {
        dm.enumerateDisplays(obj);
    }

    test('should enumerate displays returned by DisplayManager.getAttachedDisplays', () => {
        var sampleDisplayInfo = {
                display: {
                    index : 0,
                    deviceName: "Sample"
                }
            };
        let mockFn = jest.fn().mockImplementation(() => {
            return sampleDisplayInfo;
        });
        addon.DisplayManager.prototype.getAttachedDisplays = mockFn;
        console.log = jest.fn();

        expect(dm.enumerateDisplays(obj)).toBe(sampleDisplayInfo);
        expect(console.log).toHaveBeenCalledWith(sampleDisplayInfo);
        expect(mockFn).toHaveBeenCalledTimes(1);
    });

    test('should throw error when DisplayManager.getAttachedDisplays does not return any object', () => {
        let mockFn = jest.fn().mockImplementation(() => {
            return undefined;
        });
        addon.DisplayManager.prototype.getAttachedDisplays = mockFn;

        console.log = jest.fn();

        expect(enumerateDisplays).toThrow('Unknown Error');
        expect(console.log).toHaveBeenCalledTimes(0);
        expect(mockFn).toHaveBeenCalledTimes(1);
    });

    test('should check if DisplayManager.sleep function will be called', () => {
        let mockFn = jest.fn();
        addon.DisplayManager.prototype.sleep = mockFn;

        dm.sleep(obj);
        expect(mockFn).toHaveBeenCalledTimes(1);
    });

    test('should check if DisplayManager.wakey function will be called', () => {
        let mockFn = jest.fn();
        addon.DisplayManager.prototype.wakey = mockFn;

        dm.wakeUp(obj);
        expect(mockFn).toHaveBeenCalledTimes(1);
    });

    test('should check if DisplayManager.getLastInputTime function will be called', () => {
        var sampleTime = 1000;
        let mockFn = jest.fn().mockImplementation(() => {
            return sampleTime;
        });
        addon.DisplayManager.prototype.getLastInputTime = mockFn;

        expect(dm.getLastInputTime(obj)).toBe(sampleTime);
        expect(mockFn).toHaveBeenCalledTimes(1);
    });
});
