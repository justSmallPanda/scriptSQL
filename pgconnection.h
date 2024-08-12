#ifndef PGCONNECTION_H
#define PGCONNECTION_H

#include <memory>
#include <mutex>
#include <libpq-fe.h>


class PGConnection
{
public:
    PGConnection();

    std::shared_ptr<PGconn> connection() const;

private:
    void establish_connection();

    std::string m_dbhost = "192.168.8.143";
    int         m_dbport = 5432;
    std::string m_dbname = "leo_db";
    std::string m_dbuser = "leo";
    std::string m_dbpass = "klsj6un1";

    std::shared_ptr<PGconn>  m_connection;

};


#endif //PGCONNECTION_H

