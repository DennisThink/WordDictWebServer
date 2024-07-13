# WordDictWebServer

WordDictWebServer是一个提供单词翻译服务的程序，目前仅支持英文单词翻译为中文。



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
### 1.5.2 请求方法
### 1.5.3 请求
### 1.5.4 回复


1. 表设计

1. 记录所有单词的翻译，LEVEL。
2. 记录每个token的level。
3. 记录每个Token的已知单词。
4. 记录每个Token的未知单词。
5. 记录每个用户的单词频率。

