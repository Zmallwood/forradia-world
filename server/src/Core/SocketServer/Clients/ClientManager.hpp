#pragma once

typedef websocketpp::lib::weak_ptr<void> connection_hdl;

namespace FW
{
    class Client;

    class ClientManager
    {
      public:
        void AddClient(connection_hdl* handle);
        std::shared_ptr<Client> GetClient(connection_hdl* handle) const;

      private:
        std::map<connection_hdl*, std::shared_ptr<Client>> m_clients;
    };
}
