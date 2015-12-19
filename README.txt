========================================
           COMMS FRAMEWORK
========================================

1. Intro

CommsFramework is a framework project that contains all kind of classes used
to program a game. The project started as a framework for network 
communications using the ZeroMQ library. It has since then, stopped using
that library and started being a game framework.

2. Major Functions

The current major functionality of the framework is the graphic engine 
and the game engine. Those functionalities are exposed in the GraphicEngine
and GameEngine classes. The GameEngine actually contains the Graphic engine I
will probably make them independant at some point.

3. GraphicEngine

The GraphicEngine is an abstract class that needs to be implemented by an
intermediate provider. That provider needs to implement all the classes in
the "Graphic/Base Classes". The requestor can then create an instance of 
BaseGraphicEngine implemented as whetever the provider wanted. The backing
classes can be DirectX or OpenGL or whatever. Currently, the framework has
a graphic provider with the SFML graphic library, it's an OpenGL wrapper.

4. GameEngine

The GameEngine is a class containing the game loop mechanic and the BaseActor
repository. BaseActor's are the classes that are implemented by the game
itself and inserted in the game. Their Update loop will run and can interact
with other actors in the game.