# WordDictWebServer
a webserver support English word translate to Chinese word.




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



