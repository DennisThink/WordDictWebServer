# WordDictWebServer

WordDictWebServer是一个提供单词翻译服务的程序，目前仅支持英文单词翻译为中文。






1. API设计
(1) 获取英文单词的中文翻译

URL:
https://URL/v1/english_to_chinese

Method:
POST

REQUEST：
{
    "token":"not used now",
    "english":""
}

RESPONSE:
{
    "code":0,
    "message":"",
    "data":{
        "english":"",
        "chinese":""
    }
}

1. 表设计

1. 记录所有单词的翻译，LEVEL。
2. 记录每个token的level。
3. 记录每个Token的已知单词。
4. 记录每个Token的未知单词。