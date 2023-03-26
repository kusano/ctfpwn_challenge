# Malleus CTF Pwn Challenge

CTFのPwn問題を解説する本「[Malleus CTF Pwn](https://sanya.sweetduet.info/ctfpwn/)」の教材です。
Dockerで動作します。

## 利用方法

利用しているOSに応じた[Docker](https://www.docker.com/)をインストールしてください。

Docker Hubからインストールする場合。

```
docker run --rm -it -p 10081:80 -p 10001-10013:10001-10013 kusanok/ctfpwn
```

※10080ポートのアクセスがunsafe portとしてブラウザにブロックされるようになったため、10081ポートを使用しています。

このGitHubリポジトリからダウンロードしてビルドする場合。

```
git clone https://github.com/kusano/ctfpwn_challenge.git
cd ctfpwn_challenge
docker build -t ctfpwn .
docker run --rm -it -p 10081:80 -p 10001-10013:10001-10013 ctfpwn
```

ブラウザで http://localhost:10081 を開いてください。

最後のコマンドを実行している間だけ動きます。
解答状況はブラウザのlocal storageに保存されます。

**当然、脆弱性のあるイメージなので、ポートを外部に公開しないでください。**

## 更新履歴

旧バージョンはこのリポジトリの同名のタグで参照することができます。また、Docker Hubでは、`kusanok/ctfpwn:1`のようにバージョンの整数部分をタグとして旧バージョンを公開しています。

### v1.0

- 「Malleus CTF Pwn」用に作成

### v2.0

- 「Malleus CTF Pwn Second Edition」用に問題を追加
- サーバーのOSのバージョンアップと問題バイナリの再コンパイルより、v1.0から存在する問題でも、v1.0用の攻略コードでは攻撃が成功しない場合があります。その場合にはv1.0を使用してください

### v3.0

- 「解題pwnable」用に問題を追加

### v4.0

- ホストOSがLinux 5.8以降の場合にshellsortでシェルコードが実行できない問題を修正
- 問題のソースコードを修正していますが、本に記載の攻略コードはそのまま用いることができます

## スクリーンショット

![screen shot](https://raw.githubusercontent.com/kusano/ctfpwn_challenge/master/screenshot.png)
