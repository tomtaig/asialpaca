#include <drogon/drogon.h>
#include <zwo/ASICamera2.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "ASIAlpaca_Camera.h"

using namespace drogon;

int main()
{
    app().registerHandler("/management/apiversions", [](const HttpRequestPtr& req,
                       std::function<void (const HttpResponsePtr &)> &&callback)
                    {
                        boost::optional<int> clientId = req->getOptionalParameter<int>("ClientID");
                        boost::optional<int> clientTransactionId = req->getOptionalParameter<int>("ClientTransactionID");

                        Json::Value json;
                        json["ClientTransactionID"]= clientTransactionId.has_value() ? clientTransactionId.value() : 0;
                        json["ServerTransactionID"]= clientTransactionId.has_value() ? clientTransactionId.value() : 0;

                        Json::Value versions;

                        versions[0] = 1;

                        json["Value"]=versions;

                        auto resp=HttpResponse::newHttpJsonResponse(json);

                        callback(resp);
                    });

    app().registerHandler("/management/v1/description", [](const HttpRequestPtr& req,
                       std::function<void (const HttpResponsePtr &)> &&callback)
                    {
                        boost::optional<int> clientId = req->getOptionalParameter<int>("ClientID");
                        boost::optional<int> clientTransactionId = req->getOptionalParameter<int>("ClientTransactionID");

                        Json::Value json;
                        json["ClientTransactionID"]= clientTransactionId.has_value() ? clientTransactionId.value() : 0;
                        json["ServerTransactionID"]= clientTransactionId.has_value() ? clientTransactionId.value() : 0;

                        Json::Value description;

                        description["ServerName"] = "ASI Alpaca";
                        description["Manufacturer"] = "Tom Taig";
                        description["ManufacturerVersion"] = "0.1";
                        description["Location"] = "Terminus";

                        json["Value"]= description;

                        auto resp=HttpResponse::newHttpJsonResponse(json);

                        callback(resp);
                    });

    app().registerHandler("/management/v1/configureddevices", [](const HttpRequestPtr& req,
                       std::function<void (const HttpResponsePtr &)> &&callback)
                    {
                        boost::optional<int> clientId = req->getOptionalParameter<int>("ClientID");
                        boost::optional<int> clientTransactionId = req->getOptionalParameter<int>("ClientTransactionID");

                        Json::Value json;
                        json["ClientTransactionID"]= clientTransactionId.has_value() ? clientTransactionId.value() : 0;
                        json["ServerTransactionID"]= clientTransactionId.has_value() ? clientTransactionId.value() : 0;

                        Json::Value devices = Json::arrayValue;

	                    int numDevices = ASIGetNumOfConnectedCameras();

                        if (numDevices > 0) {    
                            ASI_CAMERA_INFO info;
                            ASI_ERROR_CODE infoResult;
                            
                            infoResult = ASIGetCameraProperty(&info, 0);

                            if (infoResult == ASI_SUCCESS)
                            {
                                Json::Value device;

                                device["DeviceName"] = info.Name;
                                device["DeviceType"] = "Camera";
                                device["DeviceNumber"] = info.CameraID;
                                device["UniqueID"] = boost::uuids::to_string(boost::uuids::random_generator()());

                                devices[0] = device;
                            }
                            else
                            {
                                // return error
                            }
                        }

                        json["Value"] = devices;

                        auto resp=HttpResponse::newHttpJsonResponse(json);

                        callback(resp);
                    });
    
    app().setLogPath("./")
         .setLogLevel(trantor::Logger::kDebug)
         .addListener("0.0.0.0", 8080)
         .setThreadNum(16)
         .registerPreSendingAdvice([](const HttpRequestPtr& req, const HttpResponsePtr& resp) { 
                            auto &query = req->query();
                            if (query.empty())
                            {
                                LOG_DEBUG << req->methodString() << " " << req->path() << " "
                                    << req->versionString();
                            }
                            else
                            {
                                LOG_DEBUG << req->methodString() << " " << req->path() << '?' << query
                                    << " " << req->versionString();
                            }
                       })
         //.enableRunAsDaemon()
         .run();
}
