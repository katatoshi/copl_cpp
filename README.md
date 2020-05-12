# copl_cpp

## Google Test のビルド手順

ビルド手順は [Google Testを導入してみた - Qiita](https://qiita.com/y-vectorfield/items/6238cfd2d9c34aefe364) の通りだが、念のためこちらにも記載しておく。

1. GitHub からソースファイルをクローン
```
$ git clone https://github.com/google/googletest.git
```
2. ビルドディレクトリ作成
```
$ cd googletest
$ mkdir build
$ cd build
```
3. CMake の実行
```
$ cmake ..
```
4. Make の実行
```
$ make
```
5. 出力された実行ファイル・ソースファイルを適切なディレクトリに移動
```
$ cd ..
$ sudo cp -r googlemock/include/gmock /usr/local/include/gmock
$ sudo cp -r googletest/include/gtest /usr/local/include/gtest
$ sudo cp build/lib/*.a /usr/local/lib/
```

以下のテストコードが実行できれば成功。
```
$ cat test.cpp
#include <gtest/gtest.h>

TEST(TestCaseName, TestName){
    EXPECT_EQ(1, 1);
}
$ g++ test.cpp -pthread -lgtest_main -lgtest
$ ./a.out
```
