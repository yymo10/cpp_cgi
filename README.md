# C++ CGI Library [English]

This library provides a simple interface for creating CGI (Common Gateway Interface) applications in C++. It enables the handling of GET and POST requests, parsing query strings and POST data, and managing session IDs.

## Features

- **Parse Query String**: Easily parse query strings from GET requests into a `std::map` for convenient access to parameters.
- **Parse POST Data**: Handle POST request data, parsing it into a `std::map` for easy parameter retrieval.
- **Session Management**: Generate and manage session IDs to maintain session state across requests.
- **Request Handling**: Retrieve values from either GET or POST requests based on the current request method.

## About the source code
### CGI Class Description

This CGI class is written in C++ and offers basic CGI (Common Gateway Interface) processing capabilities for web applications. By using this class, you can easily handle GET or POST requests from web forms and manage session IDs. Below is an overview of each method in the class.

### Constructor
- `CGI()`: Automatically generates a session ID when an instance of the class is created.

### Methods
- `parseQueryString()`: Parses GET parameters from the URL's query string and returns them in a `std::map<std::string, std::string>` format, allowing access to query parameters as key-value pairs.
- `parse_post_data()`: Reads POST data from the standard input and returns it in a similar `std::map<std::string, std::string>` format.
- `POST_(std::string param)`: Retrieves the value of a specified POST parameter. Undefined behavior if the parameter does not exist.
- `GET_(std::string param)`: Retrieves the value of a specified GET parameter. Returns an empty string if the parameter does not exist.
- `REQUEST_(std::string param)`: Determines whether the request is a GET or POST using the `REQUEST_METHOD` environment variable and retrieves the parameter value accordingly.
- `GenerateSessionId()`: Randomly generates a session ID. This ID serves as a consistent identifier for a user throughout their visit to the site.
- `SESSION_ID()`: Retrieves the current session ID.

### Usage Example
This class is useful for handling user input and managing sessions in web applications. For instance, when a user submits information through a form, this class can be used to parse and process the data. Additionally, the session ID can be used to identify a user's session for authentication or state management purposes.

### Compilation Guide
To compile a C++ program that includes the CGI class, you need a C++ compiler such as `g++` or `clang++`. Here is a basic example of how to compile a program with `g++`:

1. Save your program that includes the CGI class to a file, for example, `main.cpp`.
2. Open your terminal or command prompt.
3. Navigate to the directory where `main.cpp` is located.
4. Compile the program using the following command:
```sh
g++ main.cpp -std=c++11 -o ./cgi/main.cgi
```
This command tells `g++` to compile `main.cpp` and output an executable named `./cgi/main.cgi`.


### Notes
- The `parse_post_data()` method uses `std::cin` to read POST data, so it only works in a CGI environment.
- The `POST_` method can result in undefined behavior if the key is not found, so it's important to either verify the key's existence beforehand or implement proper exception handling in actual use.
- The `SESSION_ID` method only returns the value if the session ID is not empty, but it's unlikely to encounter a situation where a session ID has not been generated.

This class provides a foundation for developing CGI-based web applications in C++, making it easier to process form data and manage sessions.

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
## ソースコード
### CGIクラス
このCGIクラスは、C++で記述されたWebアプリケーションのための基本的なCGI (Common Gateway Interface) 処理機能を提供します。このクラスを使用することで、WebフォームからのGETまたはPOSTリクエストを簡単に処理し、セッションIDを生成して管理することができます。以下に、各メソッドの概要を説明します。
#### コンストラクタ
- CGI(): クラスのインスタンスが生成されると自動的にセッションIDを生成します。
#### メソッド
- `parseQueryString()`: URLのクエリストリングからGETパラメータを解析し、std::map<std::string, std::string>形式で返します。これにより、キーと値のペアでクエリパラメータにアクセスできます。
- `parse_post_data()`: 標準入力からPOSTデータを読み取り、同様にstd::map<std::string, std::string>形式で返します。
- `POST_(std::string param)`: 指定されたPOSTパラメータの値を取得します。存在しない場合は未定義の動作をします。
- `GET_(std::string param)`: 指定されたGETパラメータの値を取得します。パラメータが存在しない場合、空文字列を返します。
- `REQUEST_(std::string param)`: 環境変数REQUEST_METHODを使用して、リクエストがGETまたはPOSTのどちらであるかを判断し、適切な方法でパラメータの値を取得します。
- `GenerateSessionId()`: セッションIDをランダムに生成します。このIDは、ユーザーがサイトを訪問している間、一貫した識別子として機能します。
- `SESSION_ID()`: 現在のセッションIDを取得します。
#### 使用例
このクラスは、Webアプリケーションでユーザーからの入力を扱い、セッション管理を行う際に便利です。例えば、ユーザーがフォームを通じて情報を送信した場合、このクラスを使用してデータを解析し、処理することができます。さらに、セッションIDを使用して、ユーザーのセッションを特定し、認証や状態の管理に利用することが可能です。

#### 注意点
parse_post_data()メソッドは、std::cinを使用してPOSTデータを読み取るため、CGI環境でのみ動作します。
POST_メソッドは、キーが見つからない場合に未定義の動作をしますので、実際の使用ではキーの存在を先に確認するか、例外処理を適切に行う必要があります。

SESSION_IDメソッドは、セッションIDが空でない場合にのみその値を返しますが、通常はセッションIDが生成されていない状況は発生しません。
このクラスは、C++でCGIベースのWebアプリケーションを開発する際の基盤として利用でき、フォームデータの処理やセッション管理を容易にします。

### コンパイル手順について
C++で記述されたCGIクラスを含むプログラムをコンパイルするには、`g++`や`clang++`などのC++コンパイラが必要です。以下に`g++`を使用したプログラムのコンパイル例を示します。

1. CGIクラスを含むプログラムを`main.cpp`というファイルに保存します。
2. ターミナルまたはコマンドプロンプトを開きます。
3. `main.cpp`が存在するディレクトリにナビゲートします。
4. 以下のコマンドを使用してプログラムをコンパイルします。
```sh
g++ main.cpp -std=c++11 -o ./cgi/main.cgi
```
このコマンドは`g++`に`main.cpp`をコンパイルし、実行可能ファイル`./cgi/main.cgi`を出力するよう指示します。

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