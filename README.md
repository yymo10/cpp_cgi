# C++ CGI Library [English]

This library provides a simple interface for creating CGI (Common Gateway Interface) applications in C++. It enables the handling of GET and POST requests, parsing query strings and POST data, and managing session IDs.

## Features

- **Parse Query String**: Easily parse query strings from GET requests into a `std::map` for convenient access to parameters.
- **Parse POST Data**: Handle POST request data, parsing it into a `std::map` for easy parameter retrieval.
- **Session Management**: Generate and manage session IDs to maintain session state across requests.
- **Request Handling**: Retrieve values from either GET or POST requests based on the current request method.

## Usage

### Including the Library

Include the CGI library in your project by adding `#include "CGI.h"` to your source file.

### Creating an Instance
Instantiate the CGI class in your application to start using its features.

```cpp
CGI cgi;
```

### Handling Requests
Retrieve a specific parameter value from either GET or POST requests:

```cpp
std::string value = cgi.REQUEST_("paramName");
```

### Session ID
Retrieve the current session ID:
```cpp
std::string sessionId = cgi.SESSION_ID();
```

## Contributing
Contributions to the CGI library are welcome. Please ensure that your code adheres to the project's coding standards and include unit tests for new features or bug fixes.

## License
This library is open-source and licensed under MIT License. Feel free to use it in your projects as per the license agreement.

# C++ CGI ライブラリ [日本語]

このライブラリは、C++でCGI（Common Gateway Interface）アプリケーションを作成するためのシンプルなインターフェースを提供します。GETとPOSTのリクエストの処理、クエリ文字列とPOSTデータの解析、セッションIDの管理を可能にします。

## 特徴

- **クエリ文字列の解析**: GETリクエストからクエリ文字列を簡単に解析し、パラメータへのアクセスを容易にするための`std::map`に格納します。
- **POSTデータの解析**: POSTリクエストデータを扱い、パラメータの取得を容易にするための`std::map`に解析します。
- **セッション管理**: セッションIDを生成および管理し、リクエスト間でのセッション状態を維持します。
- **リクエスト処理**: 現在のリクエストメソッドに基づいてGETまたはPOSTリクエストから特定のパラメータ値を取得します。

## 使い方

### ライブラリのインクルード

ソースファイルに`#include "CGI.h"`を追加してプロジェクトにCGIライブラリを含めます。

### インスタンスの作成

アプリケーションでCGIクラスをインスタンス化し、その機能を使用開始します。

```cpp
CGI cgi;
```

### リクエストの処理
GETまたはPOSTリクエストから特定のパラメータ値を取得するには：
```cpp
std::string value = cgi.REQUEST_("paramName");
```
### セッションID
現在のセッションIDを取得するには：
```cpp
std::string sessionId = cgi.SESSION_ID();
```

## 貢献について 
CGIライブラリに対する貢献を心から歓迎いたします。ご提供いただくコードがプロジェクトのコーディング規約に準拠していることをご確認の上、新たな機能追加やバグ修正には必ずユニットテストを添付してください。

## ライセンス
本ライブラリはMITライセンスのもとでオープンソースとして公開されています。ライセンス契約の条件に従って、皆様のプロジェクトで自由にご利用いただけます。