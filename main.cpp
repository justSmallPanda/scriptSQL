#include <thread>
#include <iostream>
#include "pgbackend.h"
#include "pgconnection.h"

void testConnection(std::shared_ptr<PGBackend> pgbackend)
{
    auto conn = pgbackend->connection();

    std::string demo = "SELECT max(id) FROM test; " ;
    PQsendQuery( conn->connection().get(), demo.c_str() );

    while ( auto res_ = PQgetResult( conn->connection().get()) ) {
        if (PQresultStatus(res_) == PGRES_TUPLES_OK && PQntuples(res_)) {
            auto ID = PQgetvalue (res_ ,0, 0);
            std::cout<< ID<<std::endl;
        }

        if (PQresultStatus(res_) == PGRES_FATAL_ERROR){
            std::cout<< PQresultErrorMessage(res_)<<std::endl;
        }

        PQclear( res_ );
    }

    pgbackend->freeConnection(conn);

}


int main(int argc, char const *argv[])
{
    std::string demo = "SELECT text FROM test WHERE id=500001; ";
    PGConnection con;


    PQsendQuery(con.connection().get(), demo.c_str());

    while (auto res_ = PQgetResult(con.connection().get())) {
        if (PQresultStatus(res_) == PGRES_TUPLES_OK && PQntuples(res_)) {
            auto ID = PQgetvalue(res_, 0, 0);
            std::cout << ID << std::endl;
        }

        if (PQresultStatus(res_) == PGRES_FATAL_ERROR) {
            std::cout << PQresultErrorMessage(res_) << std::endl;
        }

        PQclear(res_);
    }
    //auto pgbackend = std::make_shared<PGBackend>();

    //auto pgbackend = std::make_shared<PGBackend>();

    // std::vector<std::shared_ptr<std::thread>> vec;

    //for ( size_t i = 0; i< 1 ; ++i ){

    //    vec.push_back(std::make_shared<std::thread>(std::thread(testConnection, pgbackend)));
    // }

    //  for(auto &i : vec) {
    //      i.get()->join();
    //  }

    //testConnection(pgbackend);

    return 0;
}
