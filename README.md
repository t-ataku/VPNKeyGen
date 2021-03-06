# VPNKeyGen
VPN接続時に使う一時パスフレーズ生成プログラムです。Xcodeでビルドしてください。

*注意*

諸般の事情により今後アップデートはなされないと思います。利用者皆様でどうぞ。
Issuesなどに書かれれば、議論に参加することは吝かでないです。

## 使い方
### 使い方
!!!!初回のみ初期設定をしてください!!!!

ネットワークにつながった状態で「Get Challenge」ボタンを押す。サイトにCeedを取りに行き、現在の共有パスフレーズを生成します。
正しく生成された後に「Connect」ボタンで認証情報を既定のファイルに保存します。

なお、プログラマの知識不足でエラー発生時またはサイトダウンなどのときも特に何も言いません:-P
長時間かかるようであればエラーだと認識してください。(通常5〜10秒程度)

コマンドプロンプトから起動すると、標準エラー出力に情報を書き出しています。

### 初期設定
VPNKicker Appを置きたい場所に置き起動する。
Preferencesで以下の初期設定を行う。
- VPN ID

配布されたID。12345-67 の形式
- VPN Password

鍵配布サイトへログインするときのパスワード。
上記IDと合わせて配布されているハズ。

- VPN Site Password

鍵(再)配布時に作成するパスワード。

完了したらSaveを押す。

## ファイルの説明
全部は説明しない。概要のみ。詳細はソースを参照のこと。

- /

Xcodeのプロジェクトトップ。ここにある適切なプロジェクト定義ファイルをOPENすると、Xcodeが正しく扱えるようになる...ハズ。
- VPNKicker 2020-10-14 11-50-51
- VPNKicker 2021-11-08 15-21-15

この日にビルドしたアプリケーションを置いている。最新版がよかろうと思うが、正直自信がない。
元が怪しい振る舞い[^1]をするものなので、セキュリティ的に回避せざるを得ない。
そのために例外などを入れているが、macosのバージョンアップで追加のチェックや当該例外が省かれると動かなくなる。
- support_files

Xcodeでビルドしたバイナリに加えて、以下の環境整備することでより便利になる。
対象ファイルは以下二つ
- client-ivpn-win10.ovpn (鍵ファイル生成時に配られる)
- update-resolv-conf (接続完了時に起動されるスクリプト。client-ivpn-win10.ovpn内で指定する)

この修正の中で client-ivpn-win10.ovpn のauth-user-passの指定はVPNKickerで生成したパスワードをopenvpnに引き渡すためのファイルの置き場所である。
このため、auth-user-passのファイル・パスにはPreferencesのPath to identity fileを一致させるようにする。
このようにすることで、VPNKickerで生成したパスワードをこのファイルを介してopenvpnが利用できるようになる。

それ以外はVPNKickerとは直接関係ない。

[^1] VPNサーバ側でインチキ証明書を使っていることによる対応
