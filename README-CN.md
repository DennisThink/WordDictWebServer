# WordDictWebServer

WordDictWebServer是一个提供单词翻译服务的程序，目前仅支持英文单词翻译为中文。该程序在制作的过程中使用了一些Github的字典和相应软件，在此表示感谢。

字典部分

目前的词汇分级参考
1. https://github.com/KyleBing/english-vocabulary

全部的词汇参考
2. https://github.com/skywind3000/ECDICT

3. https://github.com/KyleBing/dict


# 1 API设计
## 1.1 获取英文单词的中文翻译

### 1.1.1 URL
```
https://${IP:PORT}/v1/english_to_chinese
```
### 1.1.2
Method:
POST
### 1.1.3 请求
REQUEST：
```json
{
    "token":"not used now",
    "english":""
}
```

### 1.1.4 回复

```json
{
    "code":0,
    "message":"success",
    "data":{
        "english":"apple",
        "chinese":"苹果"
    }
}
```

## 1.2  英文句子中的未知单词的翻译
### 1.2.1 URL
```
https://${IP:PORT}/v1/sentence_to_words
```
### 1.2.2 请求方法
POST
### 1.2.3 请求
```json
{
    "token":"{USER_TOKEN}",
    "english":"This is a sentence"
}
```
### 1.2.4 回复
```json
{
    "code":0,
    "message":"succeed",
    "data":[
        {
            "english":"This",
            "chinese":"这个"
        },
        {
            "english":"sentence",
            "chinese":"句子"
        }
    ]
}
```

## 1.3  某个用户添加未知单词

### 1.3.1 URL
```
https://${IP:PORT}/v1/add_word_to_unknown
```
### 1.3.2 请求方法
POST

### 1.3.3 请求
```json
{
    "token":"{USER_TOKEN}",
    "english":"banana"
}
```
### 1.3.4 回复
```json
{
    "code":0,
    "message":"success"
}
```

## 1.4  某个用户添加已知单词
### 1.4.1 URL
```
https://${IP:PORT}/v1/add_word_to_known
```
### 1.4.2 请求方法

POST

### 1.4.3 请求

```json
{
    "token":"{USER_TOKEN}",
    "english":"apple"
}
```

### 1.4.4 回复
```json
{
    "code":0,
    "message":"success"
}
```


## 1.5  某个用户设置自己的英语水平级别
### 1.5.1 URL
```
https://${IP:PORT}/v1/set_user_language_level
```
### 1.5.2 请求方法
```
POST
```
### 1.5.3 请求
```json
{
    "token":"test@test.com",
    "level":10
}
```
### 1.5.4 回复
```json
{
    "code":0,
    "message":"success"
}
```


## 2 表格设计

### 1. T_ENGLISH_CHINESE
> 记录所有单词的翻译，LEVEL。

|列名称|列类型|备注|
|-----|-----|----|
|F_ID|唯一ID|整数，自增|
|F_ENGLISH|英文单词||
|F_CHINESE|中文翻译||
|F_LEVEL|单词级别||


2. `t_user_language_level`记录每个token的level。

|列名称|列类型|备注|
|-----|-----|----|
|F_ID|唯一ID|整数，自增|
|F_TOKEN|用户Token||
|F_LEVEL|用户词汇量级别||

3. `t_known_words`;记录每个Token的已知单词。
|列名称|列类型|备注|
|-----|-----|----|
|F_ID|唯一ID|整数，自增|
|F_TOKEN|用户Token||
|F_ENGLISH|用户已知单词||


4. `t_unknown_words`;记录每个Token的未知单词。

|列名称|列类型|备注|
|-----|-----|----|
|F_ID|唯一ID|整数，自增|
|F_TOKEN|用户Token||
|F_ENGLISH|用户未知单词||

5. t_word_frequency——记录每个用户的单词频率。

|列名称|列类型|备注|
|-----|-----|----|
|F_ID|唯一ID|整数，自增|
|F_TOKEN|用户Token||
|F_ENGLISH|用户未知单词||
|F_TIMES|单词频率|

