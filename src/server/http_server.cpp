#include "CAsioHttpServer.hpp"
#include "clipp.h"
#include "version_base.hpp"
int main(int argc,char * argv[]) {
    using namespace clipp;
    std::string strCfgFileName;
    auto cli = (
        required("-cfg", "--config").doc("the config of DictWebServerCfg") & value("config", strCfgFileName)
        );

    if (!parse(argc, argv, cli))
    {
        std::cout << make_man_page(cli, argv[0]) << std::endl;
        return 0;
    }
    else
    {
        auto serverConfig = FromJsonFile(strCfgFileName);
        CAsioHttpServer server;
        server.SetServerCfg(serverConfig);
        server.Start();
        return 0;
    }
}
