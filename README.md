# Hello, I used Box2D library to attach body to QGraphicsObject's objects.

 qbox2d library is a wrapper for Box2d library, which adds physics engine to the QGraphicsScene.

You can see an example application in `src/app ` folder

`QB2Fixture` - class, which is used to add shape to a body. It contains `b2Fixutre`. You can set friction, density and resitution.

`QB2Body` - wrapper for `b2Body` class. It inherits `QGraphicsObject`

`QB2World` - wrapper for `b2World` class. It inherits QGraphicsScene, so you can add it to the QGraphicsView. `QB2World::Start()` method starts timer, which call `b2World::Step()` method on every timeout

`QB2EventFilter` - this class allows you to react on some scene event for example key event. It can be use to control body or bodies. Install this object to the `QB2World`.

`QB2ContactEvent` - Contact event is sent when contact occurs. It uses `b2ContactListener` class. If you wanna to handle this event, inherit `QB2EventFilter` class and override for example `OnBeginContact()` method (see methods which can be override in `QB2Object` class).

## Compilation remarks
### You have to have Box2D library installed. If qt cannot find it try to add `LIBS += -L"your library path" -lBox2D` to the `src/lib/qbox2d-lib.pro` file