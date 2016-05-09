#include <QtGui/QGuiApplication>
#include <QtGui/QKeyEvent>

#include <QtGui/QOpenGLWindow>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLVertexArrayObject>

static QString vertexShader =
        "#version 120\n"
        "\n"
        "attribute vec3 position;\n"
        "attribute vec3 color;\n"
        "\n"
        "varying vec3 v_color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    v_color = color;\n"
        "    gl_Position = vec4(position, 1);\n"
        "}\n"
        ;

static QString fragmentShader =
        "#version 120\n"
        "\n"
        "varying vec3 v_color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(v_color, 1);\n"
        "}\n"
        ;

struct Window : QOpenGLWindow, QOpenGLFunctions
{
    Window() :
        m_vbo(QOpenGLBuffer::VertexBuffer)
    {
    }

    void createShaderProgram()
    {
        if ( !m_pgm.addShaderFromSourceCode( QOpenGLShader::Vertex, vertexShader)) {
            qDebug() << "Error in vertex shader:" << m_pgm.log();
            exit(1);
        }
        if ( !m_pgm.addShaderFromSourceCode( QOpenGLShader::Fragment, fragmentShader)) {
            qDebug() << "Error in fragment shader:" << m_pgm.log();
            exit(1);
        }
        if ( !m_pgm.link() ) {
            qDebug() << "Error linking shader program:" << m_pgm.log();
            exit(1);
        }
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

        // Configure the vertex streams for this attribute data layout
        m_pgm.enableAttributeArray("position");
        m_pgm.setAttributeBuffer("position", GL_FLOAT, offsetof(Vertex, position), 3, sizeof(Vertex) );
        m_pgm.enableAttributeArray("color");
        m_pgm.setAttributeBuffer("color",  GL_FLOAT, offsetof(Vertex, color), 3, sizeof(Vertex) );

        // Okay, we've finished setting up the vao
        m_vao.release();
    }

    void initializeGL()
    {
        QOpenGLFunctions::initializeOpenGLFunctions();
        createShaderProgram(); m_pgm.bind();
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
        m_pgm.bind();
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

    QOpenGLShaderProgram     m_pgm;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer            m_vbo;
};

int main(int argc, char *argv[])
{
    QGuiApplication a(argc,argv);
    Window w;
    w.setWidth(640); w.setHeight(480);
    w.show();
    return a.exec();
}
