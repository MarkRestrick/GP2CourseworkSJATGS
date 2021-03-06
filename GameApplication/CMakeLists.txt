cmake_minimum_required (VERSION 2.8)
project (GameApplication)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -l")

find_package(TinyXML REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OPENGL REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(assimp REQUIRED)

if (GLEW_FOUND)
  message("GLEW_INCLUDE_DIRS")
  message("${GLEW_INCLUDE_DIRS}")
ENDIF(GLEW_FOUND)

add_subdirectory(Utils)


add_library(GameApplication STATIC src/GameApplication.cpp src/Shader.cpp src/Texture.cpp src/GameObject.cpp src/ModelLoading.cpp src/Transform.cpp src/Renderer.cpp src/Mesh.cpp src/PostProcessBuffer.cpp src/PostProcessingEffect.cpp src/PostProcess.cpp src/ScreenAlignedQuad.cpp src/CameraController.cpp src/BoxCollider.cpp src/depthFrameBuffer.cpp include/Common.h include/GameApplication.h include/Shader.h include/Texture.h include/Vertex.h include/GameObject.h include/ModelLoading.h include/Light.h include/Transform.h include/Renderer.h include/Mesh.h include/PostProcessBuffer.h include/PostProcessingEffect.h include/PostProcess.h include/ScreenAlignedQuad.h include/CameraController.h include/BoxCollider.h include/depthFrameBuffer.h)


include_directories(GameApplication include/ Utils/include ${SDL2_INCLUDE_DIR} ${TINYXML_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${ASSIMP_INCLUDE_DIR})
target_link_libraries(GameApplication Utils ${SDL2_LIBRARY} ${TINYXML_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2IMAGE_LIBRARY} ${SDL2_TTF_LIBRARIES} ${ASSIMP_LIBRARIES} ${CMAKE_DL_LIBS})
