import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
import QtQuick.Scene3D 2.15
import QtQuick.Window 2.12 as Win

import QtMultimedia 5.12

import Qt3D.Core 2.0
import Qt3D.Extras 2.15
import Qt3D.Input 2.0
import Qt3D.Render 2.15

import Application.Video 1.0 as Video
import CustomTexture 1.0
import CustomTextureImage 1.0

Win.Window {
    id: rootwindow
    width: 640
    height: 480
    visible: true
    title: qsTr("3D Player")

    property bool useGLTexture: true
    property bool useFrames: true

    Scene3D {
        id: scene3dInstance

        anchors.fill: parent
        focus: true
        aspects: ["input", "logic"]
        cameraAspectRatioMode: Scene3D.AutomaticAspectRatio
        multisample: true
    }

    Rectangle {
        id: root

        width: parent.width
        height: parent.height
        color: "darkRed"

        Scene3DView
        {
            scene3D: scene3dInstance
            anchors.fill: parent

            Entity {
                id: sceneRoot

                property color sceneColor
                property bool clearColor: true

                Camera {
                    id: camera

                    projectionType: CameraLens.PerspectiveProjection
                    fieldOfView: 90
                    nearPlane: 0.1
                    farPlane: 1000.0
                    position: Qt.vector3d(0.0, 0.0, 0.1)
                    upVector: Qt.vector3d(0.0, 1.0, 0.0)
                    viewCenter: Qt.vector3d(0.0, 0.0, 0.0)
                }

                FirstPersonCameraController {
                    camera: camera
                    }

                components: [
                    RenderSettings {
                        id: renderSettings

                        activeFrameGraph: ForwardRenderer {
                            camera: camera
                            clearColor: "transparent"
                            buffersToClear: sceneRoot.clearColor ? ClearBuffers.ColorDepthBuffer : ClearBuffers.DepthBuffer
                        }
                    },
                    InputSettings {}
                ]

                SphereMesh {
                    id: sphereMesh
                    radius: -100.0
                    slices: 180
                    rings: 180
                }

                Texture2D {
                    id: texture

                    CustomTextureImage {
                        id: textureImage
                    }
                }

                CustomTexture {
                    id: textureGL

                    onTextureIdChanged: {
                        console.log("Texture id changed to " + textureId)
                    }
                }

                DiffuseMapMaterial {
                    id: diffuseMaterial
                    diffuse: textureGL
                }

                Connections {
                    target: Video.Player
                    function onNextFrame(frame){
                        if(useGLTexture)
                            textureGL.setFrame(frame)
                        else
                            textureImage.setFrame(frame)
//                        frame.destroy()
                        update()
                    }

                    function onNextImage(image){
                        textureImage.setImage(image)
                    }
                }

                TextureMaterial {
                    id: material
                    texture: rootwindow.useGLTexture ? textureGL : texture
                }

                Entity {
                    id: sphereEntity
                    components: [sphereMesh, diffuseMaterial]
                }
            }
        }

        Component.onCompleted: {
            Video.Player.useFrames = rootwindow.useFrames
        }

    }
}
