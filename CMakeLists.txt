cmake_minimum_required(VERSION 3.16)

project(glgame)

# C++17を使用
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# コンパイラフラグ
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

# インクルードディレクトリ
include_directories(include)
include_directories(/usr/include/bullet)

# ソースファイル
file(GLOB SOURCES "src/*.cpp")

# 実行可能ファイル
add_executable(game ${SOURCES})

# 静的ライブラリのパス
target_link_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/_lib)

# 必要なパッケージを見つける
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# リンクライブラリ
target_link_libraries(game 
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
    glut
    GL
    GLU
    BulletDynamics
    BulletCollision
    LinearMath
)

# 実行可能ファイルの出力先（buildディレクトリ内に統一）
set_target_properties(game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# ビルドディレクトリの作成
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/tmp)

# クリーンターゲット
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/build
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/tmp
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/tmp
    COMMENT "Cleaning all build artifacts"
)