# Malleus CTF Pwn Challenge

CTFのPwn問題を解説する本「[Malleus CTF Pwn](https://sanya.sweetduet.info/ctfpwn/)」の教材です。
Dockerで動作します。

## 利用方法

利用しているOSに応じた[Docker](https://www.docker.com/)をインストールしてください。

Docker Hubからインストールする場合。

```
docker run --rm -it -p 10080:80 -p 10001-10013:10001-10013 kusanok/ctfpwn
```

このGitHubリポジトリからダウンロードしてビルドする場合。

```
git clone https://github.com/kusano/ctfpwn_challenge.git
cd ctfpwn_challenge
docker build -t ctfpwn .
docker run --rm -it -p 10080:80 -p 10001-10013:10001-10013 ctfpwn
```

ブラウザで http://localhost:10080 を開いてください。

最後のコマンドを実行している間だけ動きます。
解答状況はブラウザのlocal storageに保存されます。

**当然、脆弱性のあるイメージなので、ポートを外部に公開しないでください。**

## 旧バージョン

サーバーのOSのバージョンアップと問題バイナリの再コンパイルによって、本の第1版に記載の攻略コードなど、旧バージョン向けに作成されたものでは攻撃が成功しない問題があります。Docker Hubのタグ`kusanok/ctfpwn:1`と、このリポジトリのタグ`v1.0`で旧バージョンを公開しています。

## スクリーンショット

![screen shot](https://raw.githubusercontent.com/kusano/ctfpwn_challenge/master/screenshot.png)
