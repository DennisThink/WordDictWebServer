#include "CAsioHttpServer.hpp"
int main() {
    auto dataBasePtr = std::make_shared<CDictDatabaseMysql>();
    {
      {
           MysqlDatabaseConfig cfg;
           cfg.m_strMysqlServerIp = "localhost";
           cfg.m_nMysqlServerPort = 3306;
           cfg.m_strMysqlUserName = "test";
           cfg.m_strMysqlPassoword = "test@1990";
           cfg.m_strDataBase = "json_dict";
           dataBasePtr->SetDictDatabaseConfig(&cfg);
       }
    }
    CAsioHttpServer server;
    server.SetDictAndUserWord(dataBasePtr, nullptr);
    server.Start();
}
