#include "myopenglwindow.h"
#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QtCore/qmath.h>

#include "trianglewindow.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    TriangleWindow window;
    window.resize(640, 480);
    window.show();

    return app.exec();
}
