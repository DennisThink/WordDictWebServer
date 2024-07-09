#include "CAsioHttpServer.hpp"
int main() {
    auto dictPtr = std::make_shared<CDictDatabaseMysql>();
    auto userWordPtr = std::make_shared<CUserWordDatabaseMysql>();
    {
      {
           MysqlDatabaseConfig cfg;
           cfg.m_strMysqlServerIp = "localhost";
           cfg.m_nMysqlServerPort = 3306;
           cfg.m_strMysqlUserName = "test";
           cfg.m_strMysqlPassoword = "test@1990";
           cfg.m_strDataBase = "json_dict";
           dictPtr->SetDictDatabaseConfig(&cfg);
       }

      {
          {
              UserWordDatabaseConfigMysql cfg;
              cfg.m_strMysqlServerIp = "localhost";
              cfg.m_nMysqlServerPort = 3306;
              cfg.m_strMysqlUserName = "test";
              cfg.m_strMysqlPassoword = "test@1990";
              cfg.m_strDataBase = "json_dict";
              userWordPtr->SetUserWordDatabaseConfig(&cfg);
          }
      }
    }
    CAsioHttpServer server;
    server.SetDictAndUserWord(dictPtr, userWordPtr);
    server.Start();
}
