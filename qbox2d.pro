TEMPLATE = subdirs
# Needed to ensure that things are built right, which you have to do yourself :(
CONFIG += ordered

# All the projects in your application are sub-projects of your solution
SUBDIRS = \
        lib \
        app \

lib.file = src/lib/qbox2d-lib.pro
app.file = src/app/qbox2d-app.pro

# Use .depends to specify that a project depends on another.
app.depends = lib
