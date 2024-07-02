1. 英汉基础字典的设计

|字段名|字段类型|含义|备注|
|----|----|---|------|
|F_ID|INT|自增|
|F_ENGLISH|varchar(64)|英语|
|F_CHINESE|varchar(128)|中文含义|
|F_LEVEL|int|词语等级|

```SQL
CREATE TABLE T_ENGLISH_CHINESE(
    F_ID int NOT NULL AUTO_INCREMENT,
    F_ENGISH varchar(64),
    F_CHINESE varchar(128),
    F_LEVEL int,
    PRIMARY KEY (F_ID)
);
```

2. 词频统计表

|字段名|字段类型|含义|备注|
|----|----|---|------|
|F_ID|INT|唯一标识，自增|
|F_ENGLISH|varchar(64)|英文单词|
|F_TOKEN|varchar(64)|用来标识用户|
|F_TIMES|int|遇到这个单词几次了|

```SQL
CREATE TABLE T_WORD_FREQUENCY(
    F_ID int NOT NULL AUTO_INCREMENT,
    F_ENGISH varchar(64),
    F_TOKEN varchar(128),
    F_TIMES int,
    PRIMARY KEY (F_ID)
);
```

3. 未知单词表

|字段名|字段类型|含义|备注|
|----|----|---|------|
|F_ID|INT|唯一标识，自增|
|F_ENGLISH|varchar(64)|英文单词|
|F_TOKEN|varchar(64)|用来标识用户|
```SQL
CREATE TABLE T_UNKNOWN_WORDS(
    F_ID int NOT NULL AUTO_INCREMENT,
    F_ENGISH varchar(64),
    F_TOKEN varchar(128),
    PRIMARY KEY (F_ID)
)
```


4. 已知单词表

|字段名|字段类型|含义|备注|
|----|----|---|------|
|F_ID|INT|唯一标识，自增|
|F_ENGLISH|varchar(64)|英文单词|
|F_TOKEN|varchar(64)|用来标识用户|

```SQL
CREATE TABLE T_KNOWN_WORDS(
    F_ID int NOT NULL AUTO_INCREMENT,
    F_ENGISH varchar(64),
    F_TOKEN varchar(128),
    PRIMARY KEY (F_ID)
)
```