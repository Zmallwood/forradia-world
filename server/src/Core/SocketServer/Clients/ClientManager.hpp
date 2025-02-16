#pragma once

typedef websocketpp::lib::weak_ptr<void> connection_hdl;

namespace FW
{
    class Client;

    class ClientManager
    {
      public:
      private:
        std::map<connection_hdl*, std::shared_ptr<Client>> m_clients;
    };
}
