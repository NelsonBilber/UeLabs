#include <QtGui/QGuiApplication>
#include <QtGui/QKeyEvent>

#include <QtGui/QOpenGLWindow>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLFunctions>
#include <QtGUi/QOpenGLVertexArrayObject>

struct Window : QOpenGLWindow, QOpenGLFunctions
{
    Window() :
        m_vbo(QOpenGLBuffer::VertexBuffer)
    {
    }

    void createGeometry()
    {
        // Initialize and bind the VAO that's going to capture all this vertex state
        m_vao.create();
        m_vao.bind();

        // interleaved data -- https://www.opengl.org/wiki/Vertex_Specification#Interleaved_arrays
        struct Vertex {
            GLfloat position[3],
                    color[3];
        } attribs[3] = {
            { {   -1.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 } },  // left-bottom,  red
            { {    0.0,  1.0, 0.0 }, { 0.0, 1.0, 0.0 } },  // center-top,   blue
            { {    1.0, -1.0, 0.0 }, { 0.0, 0.0, 1.0 } },  // right-bottom, green
        };

        // Put all the attribute data in a FBO
        m_vbo.create();
        m_vbo.setUsagePattern( QOpenGLBuffer::StaticDraw );
        m_vbo.bind();
        m_vbo.allocate(attribs, sizeof(attribs));

        // Okay, we've finished setting up the vao
        m_vao.release();
    }

    void initializeGL()
    {
        QOpenGLFunctions::initializeOpenGLFunctions();
        createGeometry();
    }

    void resizeGL(int w, int h)
    {
        glViewport(0, 0, w, h);
        update();
    }

    void paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        m_vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void keyPressEvent(QKeyEvent * ev)
    {
        switch (ev->key()) {
           case Qt::Key_Escape:
              exit(0);
              break;
           default:
              QWindow::keyPressEvent(ev);
              break;
        }

    }

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer            m_vbo;
};

int main(int argc, char *argv[])
{
    QGuiApplication a(argc,argv);
    Window w;
    QSurfaceFormat f = w.requestedFormat(); f.setMajorVersion(3); f.setMinorVersion(3); w.setFormat(f);
    w.setWidth(640); w.setHeight(480);
    w.show();
    return a.exec();
}
