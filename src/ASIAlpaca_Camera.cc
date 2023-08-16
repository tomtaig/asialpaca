#include "ASIAlpaca_Camera.h"
#include <zwo/ASICamera2.h>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/assign.hpp>

using namespace api::v1;
using namespace boost::assign;

std::map<ASI_CONTROL_TYPE, ASI_CONTROL_CAPS> caps;

std::map<int, std::string> asiErrorCodeMap = map_list_of 
    (ASI_SUCCESS, "")
    (ASI_ERROR_INVALID_INDEX, "ASI_ERROR_INVALID_INDEX")
    (ASI_ERROR_INVALID_ID, "ASI_ERROR_INVALID_ID")
    (ASI_ERROR_INVALID_CONTROL_TYPE, "ASI_ERROR_INVALID_CONTROL_TYPE")
    (ASI_ERROR_CAMERA_CLOSED, "ASI_ERROR_CAMERA_CLOSED")
    (ASI_ERROR_CAMERA_REMOVED, "ASI_ERROR_CAMERA_REMOVED")
    (ASI_ERROR_INVALID_PATH, "ASI_ERROR_INVALID_PATH")
    (ASI_ERROR_INVALID_FILEFORMAT, "ASI_ERROR_INVALID_FILEFORMAT")
    (ASI_ERROR_INVALID_SIZE, "ASI_ERROR_INVALID_SIZE")
    (ASI_ERROR_INVALID_IMGTYPE, "ASI_ERROR_INVALID_IMGTYPE")
    (ASI_ERROR_OUTOF_BOUNDARY, "ASI_ERROR_OUTOF_BOUNDARY")
    (ASI_ERROR_TIMEOUT, "ASI_ERROR_TIMEOUT")
    (ASI_ERROR_INVALID_SEQUENCE, "ASI_ERROR_INVALID_SEQUENCE")
    (ASI_ERROR_BUFFER_TOO_SMALL, "ASI_ERROR_BUFFER_TOO_SMALL")
    (ASI_ERROR_VIDEO_MODE_ACTIVE, "ASI_ERROR_VIDEO_MODE_ACTIVE")
    (ASI_ERROR_EXPOSURE_IN_PROGRESS, "ASI_ERROR_EXPOSURE_IN_PROGRESS")
    (ASI_ERROR_GENERAL_ERROR, "ASI_ERROR_GENERAL_ERROR")
    (ASI_ERROR_INVALID_MODE, "ASI_ERROR_INVALID_MODE")
    (ASI_ERROR_END, "ASI_ERROR_END");

bool connected=false;
ASI_CAMERA_INFO info;

void Camera::getConnected(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    LOG_DEBUG<<"User "<<deviceNumber<<" login";
    
    Json::Value json;
    json["Value"]= connected ? "True" : "False" ;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setConnected(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    LOG_DEBUG<<"Device="<<deviceNumber<<" connecting";
    
    auto connectedStr = req->getParameter("Connected");

    LOG_DEBUG<<"Connected="<<connectedStr;

    std::string errorMessage="";
    int errorCode=0;

	int numDevices = ASIGetNumOfConnectedCameras();

	if(numDevices > deviceNumber) 
    {
        if (boost::iequals(connectedStr, "true")) 
        {
            auto asiErrorCode = ASIGetCameraProperty(&info, 0);

            for ( const auto bin : info.SupportedBins) 
            {
                if (bin > 0) 
                {
                    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Supported bin="<<bin;
                }
            }

            if (asiErrorCode == ASI_SUCCESS)
            {
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": ID="<<info.CameraID;

                asiErrorCode = ASIOpenCamera(info.CameraID);

                if (asiErrorCode == ASI_SUCCESS) 
                {
                    LOG_DEBUG<<"Camera "<< deviceNumber<< " opened: ID="<<info.CameraID;

                    asiErrorCode = ASIInitCamera(info.CameraID);

                    if (asiErrorCode == ASI_SUCCESS) 
                    {
                        LOG_DEBUG<<"Camera "<< deviceNumber<< " initialized: ID="<<info.CameraID;

                        ASI_CONTROL_CAPS controlCaps;
                        int iNumOfCtrl = 0;

                        ASIGetNumOfControls(info.CameraID, &iNumOfCtrl);

                        for(auto i = 0; i < iNumOfCtrl; i++)
                        {
                            ASIGetControlCaps(info.CameraID, i, &controlCaps);
                            
                            caps[controlCaps.ControlType] = controlCaps;

                            LOG_DEBUG<<"Camera "<< deviceNumber<< ", ID="<<info.CameraID<< " ,Name="<<controlCaps.Name<< " ,Description="<<controlCaps.Description<<" ,MinValue="<<controlCaps.MinValue<<" ,MaxValue="<<controlCaps.MaxValue;
                        }
                    }
                }
            }

            errorCode = asiErrorCode;
            errorMessage =asiErrorCodeMap[errorCode];
        } 
        else if (boost::iequals(connectedStr, "false")) 
        {
            // TODO: disconnect
        }  
        else 
        {
            auto badRequestResp=HttpResponse::newHttpResponse();
            badRequestResp->setStatusCode(k400BadRequest);
            callback(badRequestResp);
            return;
        }
    }
    else
    {
        errorCode = -1;
        errorMessage = "Device number is great than the number of connected cameras";
    }

    Json::Value response;

    response["ErrorCode"] = errorCode;
    response["ErrorMessage"] = errorMessage;

    auto resp=HttpResponse::newHttpJsonResponse(response);

    callback(resp);
}

void Camera::getBayerOffsetX(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    // TODO: research this
    json["Value"]=0;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getBayerOffsetY(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    // TODO: research this
    json["Value"]=0;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getBinX(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    ASI_BOOL controlAuto;
    long controlValue;

    auto errorCode = ASIGetControlValue(info.CameraID, ASI_HARDWARE_BIN, &controlValue, &controlAuto);

    json["Value"]=controlValue;
    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}


void Camera::getBinY(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    ASI_BOOL controlAuto;
    long controlValue;

    auto errorCode = ASIGetControlValue(info.CameraID, ASI_HARDWARE_BIN, &controlValue, &controlAuto);

    json["Value"]=controlValue;
    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setBinX(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    long controlValue = std::stol(req->getParameter("BinX"));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set BinX="<<controlValue;

    auto errorCode=ASISetControlValue(info.CameraID, ASI_HARDWARE_BIN, controlValue, ASI_FALSE);

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}


void Camera::setBinY(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    long controlValue = std::stol(req->getParameter("BinY"));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set BinY="<<controlValue;

    auto errorCode = ASISetControlValue(info.CameraID, ASI_HARDWARE_BIN, controlValue, ASI_FALSE);

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getCameraXSize(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    json["Value"]=info.MaxWidth;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}


void Camera::getCameraYSize(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    json["Value"]=info.MaxHeight;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getCanAbortExposure(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    json["Value"]="True";
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getCanFastReadout(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    json["Value"]= caps[ASI_HIGH_SPEED_MODE].MaxValue == 1 ? "True" : "False";
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getCanGetCoolerPower(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    json["Value"]= info.IsCoolerCam ? "True" : "False";
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getCanPulseGuide(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    json["Value"]= info.ST4Port ? "True" : "False";
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getCanSetCcdTemperature(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    json["Value"]= caps.count(ASI_TARGET_TEMP) ? "True" : "False";
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getCanAsymmetricBin(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    json["Value"]= "False";
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getCanStopExposure(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    json["Value"]= "True";
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getCcdTemperature(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    ASI_BOOL controlAuto;
    long controlValue;

    auto errorCode = ASIGetControlValue(info.CameraID, ASI_TEMPERATURE, &controlValue, &controlAuto);

    json["Value"] = (double)controlValue / 10.0;
    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getCoolerOn(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    ASI_BOOL controlAuto;
    long controlValue;

    auto errorCode = ASIGetControlValue(info.CameraID, ASI_COOLER_ON, &controlValue, &controlAuto);

    json["Value"] = controlValue == caps[ASI_COOLER_ON].MaxValue ? "True" : "False";
    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setCoolerOn(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    long controlValue = req->getParameter("CoolerOn") == "True" ? ASI_TRUE : ASI_FALSE;

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set CoolerOn="<<controlValue;

    auto errorCode = ASISetControlValue(info.CameraID, ASI_COOLER_ON, controlValue, ASI_FALSE);

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getCoolerPower(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    ASI_BOOL controlAuto;
    long controlValue;

    if (info.IsCoolerCam) 
    {
        auto errorCode = ASIGetControlValue(info.CameraID, ASI_COOLER_POWER_PERC, &controlValue, &controlAuto);
        auto cap = caps[ASI_COOLER_POWER_PERC];

        if (errorCode == ASI_SUCCESS) 
        {
            json["Value"] = (double)(controlValue - cap.MinValue) / (double)cap.MaxValue * 100.0;
        }

        json["ErrorCode"] = errorCode;
        json["ErrorMessage"] = asiErrorCodeMap[errorCode];
    }
    else
    {
        json["Value"] = 0;
        json["ErrorCode"] = "0";
        json["ErrorMessage"] = "";
    }
    

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getElectronsPerAdu(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = info.ElecPerADU;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getExposureMax(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    ASI_BOOL controlAuto;
    long controlValue;

    auto cap = caps[ASI_EXPOSURE];

    json["Value"] = (double)cap.MaxValue / 1000000.0;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getExposureMin(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    ASI_BOOL controlAuto;
    long controlValue;

    auto cap = caps[ASI_EXPOSURE];

    json["Value"] = (double)cap.MinValue / 1000000.0;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getExposureResolution(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = 1.0/1000000.0;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getFastReadout(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    ASI_BOOL controlAuto;
    long controlValue;

    auto errorCode = ASIGetControlValue(info.CameraID, ASI_HIGH_SPEED_MODE, &controlValue, &controlAuto);

    json["Value"]=controlValue == 1 ? "True" : "False";
    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setFastReadout(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{   
    Json::Value json;
    
    long controlValue = req->getParameter("FastReadout") == "True" ? ASI_TRUE : ASI_FALSE;

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set CoolerOn="<<controlValue;

    auto errorCode = ASISetControlValue(info.CameraID, ASI_HIGH_SPEED_MODE, controlValue, ASI_FALSE);

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}