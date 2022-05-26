/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
* Copyright (C) 2014-2015, Sergey Radionov <rsatom_gmail.com>
* Copyright (C) 2011 Harald Sitter <sitter@kde.org>
*
* This file is based on QmlVlc and Phonon multimedia library
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include "rendering/VideoMaterial.h"
#include "rendering/VideoMaterialShader.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

#include <QOffscreenSurface>

#include <iostream>

VideoMaterialShader::VideoMaterialShader()
{
std::cout << " **************** VideoMaterialShader::VideoMaterialShader() calling" << std::endl;
    QOpenGLFunctions *_glF;
    _glF = QOpenGLContext::currentContext()->functions();
    Q_ASSERT(_glF);
    _glF->initializeOpenGLFunctions();

/*

QSurfaceFormat format;
format.setMajorVersion( 4 );
format.setMinorVersion( 1 );
format.setProfile( QSurfaceFormat::CompatibilityProfile );
auto *surface = new QOffscreenSurface;
surface->setFormat(format);
surface->create();
QOpenGLContext::currentContext()->makeCurrent(surface);
*/

/*

    if (!_program)
        _program = new QOpenGLShaderProgram();

    Q_ASSERT(_program); 
    bool inited = _program->create();
std::cout << " **************** QOpenGLShaderProgram init(): " << inited << std::endl;

    //setShaderFileName(VertexStage, QLatin1String(":/scenegraph/custommaterial/shaders/mandelbrot.vert.qsb"));
    //setShaderFileName(FragmentStage, QLatin1String(":/scenegraph/custommaterial/shaders/mandelbrot.frag.qsb"));
    _program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader());
    _program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader());
    _program->link();

*/

/*
    if (!_program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader()))
        qFatal("couldnt add vertex shader");
    else if (!_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader()))
        qFatal("couldnt add fragment shader");
    else if (!_program->link())
        qFatal("couldnt link shader");
*/
    setShaderFileName(VertexStage, QLatin1String(":/qml/shaders/videomaterial.vert.qsb"));
    setShaderFileName(FragmentStage, QLatin1String(":/qml/shaders/videomaterial.frag.qsb"));
std::cout << " **************** VideoMaterialShader::VideoMaterialShader() shader DONE." << std::endl;

}

VideoMaterialShader::~VideoMaterialShader()
{
/*
    if (_program && QOpenGLContext::currentContext()) {
        _program->removeAllShaders();
        _program->deleteLater();
    }
*/
}

char const *const *VideoMaterialShader::attributeNames() const
{
    static const char *names[] = {
        "targetVertex",
        "textureCoordinates",
        0};
    return names;
}

const char *VideoMaterialShader::vertexShader() const
{
std::cout << " **************** VideoMaterialShader::vertexShader() called" << std::endl;

    return "attribute highp vec4 targetVertex;"
           "attribute highp vec2 textureCoordinates;"
           "uniform highp mat4 positionMatrix;"
           "varying highp vec2 textureCoord;"
           "void main(void)"
           "{"
           "    gl_Position = positionMatrix * targetVertex;"
           "    textureCoord = textureCoordinates;"
           "}";
}

const char *VideoMaterialShader::fragmentShader() const
{
std::cout << " **************** VideoMaterialShader::fragmentShader() called" << std::endl;
    return "uniform sampler2D texY;"
           "uniform sampler2D texU;"
           "uniform sampler2D texV;"
           "uniform mediump mat4 colorMatrix;"
           "varying highp vec2 textureCoord;"
           "uniform lowp float opacity;"
           "void main(void)"
           "{"
           "    highp vec4 color = vec4("
           "           texture2D(texY, textureCoord.st).r,"
           "           texture2D(texU, textureCoord.st).r,"
           "           texture2D(texV, textureCoord.st).r,"
           "           1.0);"
           "    gl_FragColor = colorMatrix * color * opacity;"
           "}";
}

void VideoMaterialShader::initialize()
{
std::cout << " **************** VideoMaterialShader::initialize() called" << std::endl;
/*
    _positionMatrixId = program()->uniformLocation("positionMatrix");
    _colorMatrixId = program()->uniformLocation("colorMatrix");
    _opacityId = program()->uniformLocation("opacity");
    _texYId = program()->uniformLocation("texY");
    _texUId = program()->uniformLocation("texU");
    _texVId = program()->uniformLocation("texV");
*/
}

void VideoMaterialShader::updateState(const RenderState &state,
                                      QSGMaterial *newMaterial,
                                      QSGMaterial *oldMaterial)
{
std::cout << " **************** VideoMaterialShader::updateState() called" << std::endl;
/*
    Q_UNUSED(oldMaterial)

    if (state.isOpacityDirty())
        program()->setUniformValue(_opacityId, GLfloat(state.opacity()));

    if (state.isMatrixDirty())
        program()->setUniformValue(_positionMatrixId, state.combinedMatrix());

    static const QMatrix4x4 colorMatrix(
        1.164383561643836, 0.000000000000000, 1.792741071428571, -0.972945075016308,
        1.164383561643836, -0.213248614273730, -0.532909328559444, 0.301482665475862,
        1.164383561643836, 2.112401785714286, 0.000000000000000, -1.133402217873451,
        0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000);

    program()->setUniformValue(_colorMatrixId, colorMatrix);

    VideoMaterial *material = static_cast<VideoMaterial *>(newMaterial);

    program()->setUniformValue(_texYId, 0);
    program()->setUniformValue(_texUId, 1);
    program()->setUniformValue(_texVId, 2);

    material->bindPlanes();
*/
}

bool VideoMaterialShader::updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial *oldMaterial)
{
std::cout << " **************** VideoMaterialShader::updateUniformData() called" << std::endl;
    bool changed = false;
    QByteArray *buf = state.uniformData();
    //Q_ASSERT(buf->size() >= 64);
std::cout << " **************** VideoMaterialShader::updateUniformData() buf size=" << buf->size() << std::endl;

    if (state.isMatrixDirty()) {
        const QMatrix4x4 m = state.combinedMatrix();
        memcpy(buf->data(), m.constData(), 64);
        changed = true;
std::cout << " ------ VideoMaterialShader::updateUniformData() isMatrixDirty" << std::endl;
    }

    if (state.isOpacityDirty()) {
        const float opacity = state.opacity();
        memcpy(buf->data() + 64, &opacity, 4);
        changed = true;
std::cout << " ------ VideoMaterialShader::updateUniformData() isOpacityDirty" << std::endl;
    }

    static const QMatrix4x4 colorMatrix(
        1.164383561643836, 0.000000000000000, 1.792741071428571, -0.972945075016308,
        1.164383561643836, -0.213248614273730, -0.532909328559444, 0.301482665475862,
        1.164383561643836, 2.112401785714286, 0.000000000000000, -1.133402217873451,
        0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000);

    auto *material = static_cast<VideoMaterial *>(newMaterial);
    if (oldMaterial != newMaterial || material->uniforms.dirty) {
        memcpy(buf->data() + 68, material->uniforms.colorMatrix.constData(), 64);
        memcpy(buf->data() + 132, &material->uniforms._texYId, 4);
        memcpy(buf->data() + 136, &material->uniforms._texUId, 4);
        memcpy(buf->data() + 140, &material->uniforms._texVId, 4);

        memcpy(buf->data() + 132, material->_planeTexIds, 12);

std::cout << " ------ VideoMaterialShader::updateUniformData() _texYId=" << material->uniforms._texYId << std::endl;
std::cout << " ------ VideoMaterialShader::updateUniformData() _texYId=" << material->uniforms._texUId << std::endl;
std::cout << " ------ VideoMaterialShader::updateUniformData() _texYId=" << material->uniforms._texVId << std::endl;

        material->uniforms.dirty = false;
        changed = true;
   }

   return changed;
}

void VideoMaterialShader::updateSampledImage(RenderState &state,
                                    int binding, 
                                    QSGTexture **texture, 
                                    QSGMaterial *newMaterial, 
                                    QSGMaterial *oldMaterial)
{
std::cout << "+++++++++++++++++++++++ VideoMaterialShader::updateSampledImage() called(binding=" << binding << ")" << std::endl;
std::cout << "+++++++++++++++++++++++ VideoMaterialShader::updateSampledImage() *texture" << *texture << std::endl;
    Q_UNUSED(state);
    Q_UNUSED(oldMaterial);
    if (binding < 1 || binding > 3)
        return;

//    auto m = static_cast<VideoMaterial *>(newMaterial);
//    *texture = m->m_textures[binding - 1].data();

/*
    switch (binding) { // the binding for the sampler2Ds in the fragment shader
    case 1:
        *texture = material->state.texture1;
        break;
    case 2:
        *texture = material->state.texture2;
        break;
    default:
        return;
    }
*/
}
