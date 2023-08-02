#include <drogon/drogon.h>
#include <zwo/ASICamera2.h>

using namespace drogon;

int main()
{
    app().registerHandler("/management/apiversions", [](const HttpRequestPtr& req,
                       std::function<void (const HttpResponsePtr &)> &&callback)
                    {
                        boost::optional<int> clientId = req->getOptionalParameter<int>("ClientID");
                        boost::optional<int> clientTransactionId = req->getOptionalParameter<int>("ClientTransactionID");

                        Json::Value json;
                        json["ClientTransactionID"]=0;
                        json["ServerTransactionID"]=0;

                        Json::Value versions;

                        versions[0] = 1;

                        json["Value"]=versions;

                        auto resp=HttpResponse::newHttpJsonResponse(json);

                        callback(resp);
                    });

    app().registerHandler("/test?username={name}",
                    [](const HttpRequestPtr& req,
                       std::function<void (const HttpResponsePtr &)> &&callback,
                       const std::string &name)
                    {
                        Json::Value json;
                        json["result"]="ok";
                        json["message"]=std::string("hello,")+name;
                        auto resp=HttpResponse::newHttpJsonResponse(json);
                        callback(resp);
                    });
    
    app().setLogPath("./")
         .setLogLevel(trantor::Logger::kInfo)
         .addListener("0.0.0.0", 8080)
         .setThreadNum(16)
         //.enableRunAsDaemon()
         .run();
}
