#ifndef TRIANGLEWINDOW_H
#define TRIANGLEWINDOW_H

#include "myopenglwindow.h"
#include <QtGui/QGuiApplication>

#include <QtGui/QKeyEvent>
#include <QtGui/QOpenGLWindow>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLVertexArrayObject>
class TriangleWindow : public MyOpenGLWindow
{
public:
    TriangleWindow();

    void createShaderProgram();
    void createGeometry();
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *ev);


    QMatrix4x4 m_projection, m_view;
    QOpenGLShaderProgram     m_pgm;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer            m_vbo;
    QOpenGLBuffer            m_ibo;
    GLsizei                  m_cnt;
};

#endif // TRIANGLEWINDOW_H
