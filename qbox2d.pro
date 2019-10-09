TEMPLATE = subdirs
# Needed to ensure that things are built right, which you have to do yourself :(
CONFIG += ordered

# All the projects in your application are sub-projects of your solution
SUBDIRS = \
        lib \
        app \
        multiplayer-lib \
        multiplayer-app \
        smart-intersection

lib.file = src/lib/qbox2d-lib.pro
app.file = src/app/qbox2d-app.pro
multiplayer-lib.file = src/multiplayer-lib/qbox2d-multiplayer-lib.pro
multiplayer-app.file = src/multiplayer-app/qbox2d-multiplayer-app.pro
smart-intersection.file = src/smart-intersection/smart-intersection.pro

# Use .depends to specify that a project depends on another.
app.depends = lib
multiplayer-app.depends = lib
multiplayer-app.depends = multiplayer-lib
smart-intersection.depends = lib
