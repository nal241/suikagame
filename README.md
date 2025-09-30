# glgame

OpenGLとGLUTで作成されたシンプルなゲームです。

## 依存関係

このプロジェクトをビルドして実行するには、以下のライブラリが必要です。

*   OpenGL
*   Bullet Physics

Debian/Ubuntuベースのシステムでは、次のコマンドでインストールできます。

```bash
sudo apt-get update
sudo apt-get install -y build-essential freeglut3-dev libbullet-dev
```

## ビルド

ゲームをビルドするには、次のコマンドを使用します。

```bash
make
```

## 実行

ゲームを実行するには、次のコマンドを使用します。

```bash
./bin/glgame
```

## クリーン

ビルドファイルをクリーンアップするには、次のコマンドを使用します。

```bash
make clean
```
