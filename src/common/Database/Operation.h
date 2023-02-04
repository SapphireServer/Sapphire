#pragma once

namespace Mysql
{
  class Connection;
}

namespace Sapphire::Db
{
  class DbConnection;

  class PreparedStatement;

  class Operation
  {
  public:
    Operation() :
      m_pConn( nullptr )
    {
    }

    virtual ~Operation()
    {
    }

    virtual int call()
    {
      execute();
      return 0;
    }

    virtual bool execute() = 0;

    virtual void setConnection( DbConnection* pCon )
    {
      m_pConn = pCon;
    }

    DbConnection* m_pConn;

  private:
    Operation( Operation const& right ) = delete;

    Operation& operator=( Operation const& right ) = delete;
  };
}

