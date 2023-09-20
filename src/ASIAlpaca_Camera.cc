#include "ASIAlpaca_Camera.h"
#include <zwo/ASICamera2.h>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/assign.hpp>
#include <boost/date_time.hpp>

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
std::unique_ptr<unsigned char[]> buffer;
unsigned int bufferSize;

void Camera::abortExposure(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    auto errorCode=ASIStopExposure(info.CameraID);

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::startExposure(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    auto durationValue = std::stod(req->getParameter("Duration"));
    auto lightValue = req->getParameter("Light");

    memset(buffer.get(), 0, bufferSize*sizeof(char));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set Duration="<<durationValue<< ", Light="<< lightValue;

    auto light = lightValue == "True" ? ASI_TRUE : ASI_FALSE;
    auto duration = (long)floor(durationValue * 1000000.0);

    auto errorCode=ASISetControlValue(info.CameraID, ASI_EXPOSURE, duration, ASI_FALSE);

    if (errorCode == ASI_SUCCESS) 
    {
        errorCode=ASIStartExposure(info.CameraID, light);
    }

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::stopExposure(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    auto errorCode=ASIStopExposure(info.CameraID);

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getImageArray(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    if (info.IsColorCam == ASI_TRUE)
    {
        json["ErrorCode"] = "-1";
        json["ErrorMessage"] = "Color camera not supported";
    }
    else
    {
        int width;
        int height;
        int bin;
        ASI_IMG_TYPE imageType;

        auto errorCode=ASIGetROIFormat(deviceNumber, &width, &height, &bin, &imageType);
        
        if (errorCode == ASI_SUCCESS)
        {
            LOG_DEBUG<<"Camera "<< deviceNumber<< ": Width="<<width<< ", Height="<< height<< ",Bin="<<bin;

            if (imageType != ASI_IMG_RAW8) 
            {
                json["ErrorCode"] = "-1";
                json["ErrorMessage"] = "Only RAW8 supported";
            }
            else
            {
                unsigned char* pBuffer = buffer.get();

                errorCode = ASIGetDataAfterExp(info.CameraID, pBuffer, bufferSize);

                if (errorCode == ASI_SUCCESS)
                {
                    json["Type"] = 2;
                    json["Rank"] = 2;

                    Json::Value rows;
                    
                    for (int x=0; x<width; x++) 
                    { 
                        Json::Value column;

                        for (int y=0; y<height; y++)
                        {
                            column.append((uint32_t)pBuffer[y*width+x]);
                        }

                        rows.append(column);
                    }

                    json["Value"] = rows;
                }
            }
        }

        if (errorCode !=  ASI_SUCCESS)
        {
            json["ErrorCode"] = errorCode;
            json["ErrorMessage"] = asiErrorCodeMap[errorCode];
        }
    }

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getImageArray2(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    int width;
    int height;
    int bin;
    ASI_IMG_TYPE imageType;
    bool success=false;

    auto errorCode=ASIGetROIFormat(deviceNumber, &width, &height, &bin, &imageType);
    
    if (errorCode == ASI_SUCCESS)
    {
        LOG_DEBUG<<"Camera "<< deviceNumber<< ": Width="<<width<< ", Height="<< height<< ",Bin="<<bin;

        if (imageType == ASI_IMG_RAW8) 
        {
            LOG_DEBUG<<"Downloading image";

            unsigned char* imageBuffer = buffer.get();

            errorCode = ASIGetDataAfterExp(info.CameraID, imageBuffer, bufferSize);

            if (errorCode == ASI_SUCCESS)
            {
                LOG_DEBUG<<"Downloaded image";

                auto resp = drogon::HttpResponse::newStreamResponse(
                    [imageBuffer,width,height,x = 0,pos = 0,content = std::string("{ \"Type\": 2, \"Rank\": 2, \"Value\": [")](char *pBuffer, std::size_t nBuffSize) mutable -> std::size_t
                {                    
                    if (!pBuffer) 
                    {
                        LOG_INFO << "Connection closed or buffer is null.";
                        return 0;
                    }

                    if (x < width-1 && pos == content.size())
                    {
                        pos = 0;
                        content = "[";

                        for (int y=0; y<height-1; y++)
                        {
                            content += std::to_string(imageBuffer[y*width+x]) + ",";
                        }
                        
                        content += std::to_string(imageBuffer[(height-1)*width+x]) + "],";

                        x++;
                    }

                    if (x == width-1 && pos == content.size())
                    {
                        pos = 0;
                        content = "[";

                        for (int y=0; y<height-1; y++)
                        {
                            content += std::to_string(imageBuffer[y*width+x]) + ",";
                        }
                        
                        content += std::to_string(imageBuffer[(height-1)*width+x])  + "]] }";

                        x++;
                    }

                    if (x == width && pos == content.size()) 
                    {
                        return 0;
                    }

                    std::size_t copyLength = std::min(nBuffSize, content.size()-pos);

                    memcpy(pBuffer, content.data()+pos, copyLength);

                    pos += copyLength;

                    return copyLength;
                }, "", ContentType::CT_APPLICATION_JSON);
                
                callback(resp);

                success = truncate64;
            }
        }
    }

    if (!success) 
    {
        auto resp = HttpResponse::newHttpResponse(k204NoContent, ContentType::CT_NONE);
        callback(resp);
    }
}

void Camera::getImageReady(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    ASI_EXPOSURE_STATUS status;

    auto errorCode=ASIGetExpStatus(info.CameraID, &status);

    if (errorCode == ASI_SUCCESS) 
    {
        json["Value"] = status == ASI_EXP_SUCCESS ? true : false;
    }
    
    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::action(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    // TODO
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::commandBlind(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    // TODO
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::commandBool(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    // TODO
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::commandString(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    // TODO
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getConnected(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    LOG_DEBUG<<"User "<<deviceNumber<<" login";
    
    Json::Value json;
    json["Value"]= connected;
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

            if (asiErrorCode == ASI_SUCCESS)
            {
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": ID="<<info.CameraID;
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": Name="<<info.Name;
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": BitDepth="<<info.BitDepth;
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": eADU="<<info.ElecPerADU;
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": Color="<<info.IsColorCam;
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": Cooler="<<info.IsCoolerCam;
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": Trigger="<<info.IsTriggerCam;
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": USB3="<<info.IsUSB3Camera;
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": USB3Host="<<info.IsUSB3Host;
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": MaxHeight="<<info.MaxHeight;
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": MaxWidth="<<info.MaxWidth;
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": Shutter="<<info.MechanicalShutter;
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": PixelSize="<<info.PixelSize;
                LOG_DEBUG<<"Camera "<< deviceNumber<< ": ST4="<<info.ST4Port;

                bufferSize = info.MaxWidth*info.MaxHeight*2;
                buffer = std::make_unique<unsigned char[]>(bufferSize);

                for ( const auto bin : info.SupportedBins) 
                {
                    if (bin > 0) 
                    {
                        LOG_DEBUG<<"Camera "<< deviceNumber<< ": Supported bin="<<bin;
                    }
                }

                for ( const auto video : info.SupportedVideoFormat) 
                {
                    if (video > 0) 
                    {
                        LOG_DEBUG<<"Camera "<< deviceNumber<< ": Supported video="<<video;
                    }
                }

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

                            LOG_DEBUG<<"Camera "<< deviceNumber<< ", ID="<<info.CameraID<< " ,Name="<<controlCaps.Name;
                            LOG_DEBUG<<"Camera "<< deviceNumber<< ", ID="<<info.CameraID<< " ,Description="<<controlCaps.Description;
                            LOG_DEBUG<<"Camera "<< deviceNumber<< ", ID="<<info.CameraID<< " ,MinValue="<<controlCaps.MinValue;
                            LOG_DEBUG<<"Camera "<< deviceNumber<< ", ID="<<info.CameraID<< ", MaxValue="<<controlCaps.MaxValue;
                        }

                        connected = true;
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

void Camera::getDescription(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    json["Value"]= info.Name;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getDriverInfo(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    json["Value"]= "ASIAlpaca";
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}


void Camera::getDriverVersion(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    json["Value"]= "0.1"; // TODO: version this API
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getInterfaceVersion(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    json["Value"]= 3;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getName(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    json["Value"]= info.Name;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getSupportedActions(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    json["Value"]= Json::arrayValue;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

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

    int width;
    int height;
    int bin;
    ASI_IMG_TYPE imageType;

    auto errorCode=ASIGetROIFormat(deviceNumber, &width, &height, &bin, &imageType);

    if (errorCode == ASI_SUCCESS) 
    {
        json["Value"]=bin;
    }

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

    int width;
    int height;
    int bin;
    ASI_IMG_TYPE imageType;

    auto errorCode=ASIGetROIFormat(deviceNumber, &width, &height, &bin, &imageType);

    if (errorCode == ASI_SUCCESS) 
    {
        json["Value"]=bin;
    }

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setBinX(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    int controlValue = std::stoi(req->getParameter("BinX"));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set BinX="<<controlValue;

    Json::Value json;
    
    int width;
    int height;
    int bin;
    ASI_IMG_TYPE imageType;

    auto errorCode=ASIGetROIFormat(deviceNumber, &width, &height, &bin, &imageType);

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": width="<<width<<",height="<<height<<",bin="<<bin;

    if (errorCode == ASI_SUCCESS) 
    {
        errorCode=ASISetROIFormat(deviceNumber, width, height, controlValue, imageType);
    }

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}


void Camera::setBinY(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    int controlValue = std::stoi(req->getParameter("BinY"));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set BinY="<<controlValue;

    Json::Value json;
    
    int width;
    int height;
    int bin;
    ASI_IMG_TYPE imageType;

    auto errorCode=ASIGetROIFormat(deviceNumber, &width, &height, &bin, &imageType);

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": width="<<width<<",height="<<height<<",bin="<<bin;

    if (errorCode == ASI_SUCCESS) 
    {
        errorCode=ASISetROIFormat(deviceNumber, width, height, controlValue, imageType);
    }

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getCameraState(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    // 0 = CameraIdle , 1 = CameraWaiting , 2 = CameraExposing , 3 = CameraReading , 4 = CameraDownload , 5 = CameraError
    json["Value"]= 1;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

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

    json["Value"]= true;
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

    json["Value"]= caps[ASI_HIGH_SPEED_MODE].MaxValue == 1 ? true : false;
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

    json["Value"]= info.IsCoolerCam ? true : false;
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

    json["Value"]= info.ST4Port ? true : false;
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

    json["Value"]= caps.count(ASI_TARGET_TEMP) ? true : false;
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

    json["Value"]= false;
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

    json["Value"]= true;
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

    json["Value"] = controlValue == caps[ASI_COOLER_ON].MaxValue ? true : false;
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

    json["Value"]=controlValue == 1 ? true : false;
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

void Camera::getFullWellCapacity(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    ASI_BOOL controlAuto;
    long gain;
    long offset;

    auto errorCode = ASIGetControlValue(info.CameraID, ASI_GAIN, &gain, &controlAuto);
    
    if (errorCode != ASI_SUCCESS)
    {
        json["ErrorCode"] = errorCode;
        json["ErrorMessage"] = asiErrorCodeMap[errorCode];
    }
    else 
    {
        errorCode = ASIGetControlValue(info.CameraID, ASI_OFFSET, &offset, &controlAuto);

        if (errorCode != ASI_SUCCESS)
        {
            json["ErrorCode"] = errorCode;
            json["ErrorMessage"] = asiErrorCodeMap[errorCode];
        }
        else 
        {   
            auto maxPixelValue = 1<<info.BitDepth;
            
            // TODO: cap at sensors max FWC 
            json["Value"] = (maxPixelValue-offset)*info.ElecPerADU;
            json["ErrorCode"] = "0";
            json["ErrorMessage"] = "";
        }
    }
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getGain(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    ASI_BOOL controlAuto;
    long controlValue;

    auto errorCode = ASIGetControlValue(info.CameraID, ASI_GAIN, &controlValue, &controlAuto);

    json["Value"] = controlValue;
    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setGain(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    long controlValue = std::stoi(req->getParameter("Gain"));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set Gain="<<controlValue;

    auto errorCode = ASISetControlValue(info.CameraID, ASI_GAIN, controlValue, ASI_FALSE);

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getGainMax(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = caps[ASI_GAIN].MaxValue;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getGainMin(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = caps[ASI_GAIN].MinValue;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getGains(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = Json::arrayValue;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getHasShutter(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = "False";
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getHeatsinkTemperature(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = "";
    json["ErrorCode"] = "-1";
    json["ErrorMessage"] = "Heatsink temperature not readable";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getIsPulseGuiding(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    if (info.ST4Port) {
        json["Value"] = false; // TODO: track pulse guiding on/off state
    } else {
        json["Value"] = false;
    }

    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getLastExposureDuration(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = 0.0;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getLastExposureStartTime(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    std::time_t t = std::time(nullptr);
    std::string datetime(100,0);

    // TODO: not the right format
    datetime.resize(std::strftime
        (&datetime[0], datetime.size(), "%a %d %b %Y - %I:%M:%S%p", std::localtime(&t)));

    Json::Value json;
    
    json["Value"] = 0.0;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = datetime;

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getMaxAdu(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    int width;
    int height;
    int bin;
    ASI_IMG_TYPE imageType;
    auto errorCode=ASIGetROIFormat(deviceNumber, &width, &height, &bin, &imageType);

    if (imageType == ASI_IMG_RAW8) 
    {
        json["Value"] = 255;
        json["ErrorCode"] = "0";
        json["ErrorMessage"] = "";
    }
    else if (imageType == ASI_IMG_RAW16)
    {
        json["Value"] = 65535;
        json["ErrorCode"] = "0";
        json["ErrorMessage"] = "";
    }
    else 
    {
        json["ErrorCode"] = "-1";
        json["ErrorMessage"] = "Unsupported image format";
    }

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getMaxBinX(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = caps[ASI_HARDWARE_BIN].MaxValue;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getMaxBinY(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = caps[ASI_HARDWARE_BIN].MaxValue;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getNumX(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    int width;
    int height;
    int bin;
    ASI_IMG_TYPE imageType;

    ASIGetROIFormat(deviceNumber, &width, &height, &bin, &imageType);

    json["Value"] = width;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setNumX(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    int controlValue = std::stoi(req->getParameter("NumX"));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set NumX="<<controlValue;

    Json::Value json;
    
    int width;
    int height;
    int bin;
    ASI_IMG_TYPE imageType;

    auto errorCode=ASIGetROIFormat(deviceNumber, &width, &height, &bin, &imageType);

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": width="<<width<<",height="<<height<<",bin="<<bin;

    if (errorCode == ASI_SUCCESS) 
    {
        errorCode=ASISetROIFormat(deviceNumber, controlValue, height, bin, imageType);
    }

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getNumY(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    int width;
    int height;
    int bin;
    ASI_IMG_TYPE imageType;

    ASIGetROIFormat(deviceNumber, &width, &height, &bin, &imageType);

    json["Value"] = height;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setNumY(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    int controlValue = std::stoi(req->getParameter("NumY"));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set NumY="<<controlValue;

    Json::Value json;
    
    int width;
    int height;
    int bin;
    ASI_IMG_TYPE imageType;

    auto errorCode=ASIGetROIFormat(deviceNumber, &width, &height, &bin, &imageType);

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": width="<<width<<",height="<<height<<",bin="<<bin;

    if (errorCode == ASI_SUCCESS) 
    {
        errorCode=ASISetROIFormat(deviceNumber, width, controlValue, bin, imageType);
    }

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getOffset(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    ASI_BOOL controlAuto;
    long controlValue;

    auto errorCode = ASIGetControlValue(info.CameraID, ASI_OFFSET, &controlValue, &controlAuto);

    json["Value"]=controlValue;
    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setOffset(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{   
    Json::Value json;

    long controlValue = std::stol(req->getParameter("Offset"));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set Offset="<<controlValue;

    auto errorCode = ASISetControlValue(info.CameraID, ASI_OFFSET, controlValue, ASI_FALSE);

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getOffsetMax(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = caps[ASI_OFFSET].MaxValue;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getOffsetMin(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = caps[ASI_OFFSET].MinValue;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getOffsets(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = Json::arrayValue;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getPercentCompleted(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    // TODO
    json["Value"] = 0;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getPixelSizeX(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = info.PixelSize;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getPixelSizeY(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    json["Value"] = info.PixelSize;
    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getReadoutModes(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    json["Value"] = Json::arrayValue;

    auto errorCode=ASI_SUCCESS;

    if (info.IsTriggerCam)
    {        
        json["ErrorCode"] = "-1";
        json["ErrorMessage"] = "IsTriggerCam=TRUE not implemented";
    }
    else
    {
        json["Value"][0] = "Default";
        json["ErrorCode"] = "0";
        json["ErrorMessage"] = "";
    }

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getReadoutMode(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    if (info.IsTriggerCam == ASI_FALSE)
    {
        json["Value"] = 0;
        json["ErrorCode"] = "0";
        json["ErrorMessage"] = "";
    }
    else
    {
        json["Value"] = 0;
        json["ErrorCode"] = "-1";
        json["ErrorMessage"] = "IsTriggerCam=TRUE not implemented";
    }
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setReadoutMode(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    int controlValue = std::stol(req->getParameter("ReadoutMode"));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set ReadoutMode="<<controlValue;
    
    if (info.IsTriggerCam == ASI_FALSE)
    {
        if (controlValue == 0) 
        {
            json["ErrorCode"] = "0";
            json["ErrorMessage"] = "";
        }
        else
        {
            json["ErrorCode"] = "-1";
            json["ErrorMessage"] = "Readout mode not supported";
        }
    }
    else
    {
        json["Value"] = 0;
        json["ErrorCode"] = "-1";
        json["ErrorMessage"] = "IsTriggerCam=TRUE not implemented";
    }
    

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getSensorName(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    if (std::string(info.Name) == "ZWO ASI120MM")
    {
        json["Value"] = "AR0130CS";
    }
    else
    {
        json["Value"] = "";
    }

    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getSensorType(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    // 0 = Monochrome,
    // 1 = Colour not requiring Bayer decoding
    // 2 = RGGB Bayer encoding
    // 3 = CMYG Bayer encoding
    // 4 = CMYG2 Bayer encoding
    // 5 = LRGB TRUESENSE Bayer encoding.

    if (info.IsCoolerCam == ASI_FALSE) 
    {
        json["Value"] = 0;
    }
    else
    {
        json["Value"] = 2; // TODO
    }

    json["ErrorCode"] = "0";
    json["ErrorMessage"] = "";
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getSetCcdTemperature(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    if (info.IsCoolerCam == ASI_FALSE)
    {
        json["ErrorCode"] = "-1";
        json["ErrorMessage"] = "Camera has no cooler";
    }
    else
    {
        ASI_BOOL controlAuto;
        long controlValue;

        auto errorCode = ASIGetControlValue(info.CameraID, ASI_TARGET_TEMP, &controlValue, &controlAuto);
        
        if (errorCode == ASI_SUCCESS) 
        {
            json["Value"] = (double)controlValue;
        }
        
        json["ErrorCode"] = errorCode;
        json["ErrorMessage"] = asiErrorCodeMap[errorCode];
    }
    
    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setSetCcdTemperature(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;

    auto controlValue = std::stod(req->getParameter("SetCCDTemperature"));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set SetCCDTemperature="<<controlValue;
        
    if (info.IsCoolerCam == ASI_FALSE)
    {
        json["ErrorCode"] = "-1";
        json["ErrorMessage"] = "Camera has no cooler";
    }
    else
    {
        long celsius = (int)floor(controlValue);

        auto errorCode = ASISetControlValue(info.CameraID, ASI_TARGET_TEMP, celsius, ASI_FALSE);

        if (errorCode == ASI_SUCCESS) 
        {
            json["Value"] = controlValue;
        }
        
        json["ErrorCode"] = errorCode;
        json["ErrorMessage"] = asiErrorCodeMap[errorCode];
    }

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getStartX(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    int startX;
    int startY;

    auto errorCode=ASIGetStartPos(deviceNumber, &startX, &startY);

    if (errorCode == ASI_SUCCESS) 
    {
        json["Value"] = startX;
    }

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setStartX(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    int controlValue = std::stoi(req->getParameter("StartX"));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set StartX="<<controlValue;

    Json::Value json;
    
    int startX;
    int startY;

    auto errorCode=ASIGetStartPos(deviceNumber, &startX, &startY);

    if (errorCode == ASI_SUCCESS) 
    {
        errorCode = ASISetStartPos(deviceNumber, controlValue, startY);
    }

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getStartY(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    int startX;
    int startY;

    auto errorCode=ASIGetStartPos(deviceNumber, &startX, &startY);

    if (errorCode == ASI_SUCCESS) 
    {
        json["Value"] = startY;
    }

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setStartY(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    int controlValue = std::stoi(req->getParameter("StartY"));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set StartY="<<controlValue;

    Json::Value json;
    
    int startX;
    int startY;

    auto errorCode=ASIGetStartPos(deviceNumber, &startX, &startY);

    if (errorCode == ASI_SUCCESS) 
    {
        errorCode = ASISetStartPos(deviceNumber, startX, controlValue);
    }

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::getSubexposureDuration(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    Json::Value json;
    
    ASI_BOOL controlAuto;
    long controlValue;

    auto errorCode = ASIGetControlValue(info.CameraID, ASI_EXPOSURE, &controlValue, &controlAuto);

    if (errorCode == ASI_SUCCESS) 
    {
        json["Value"] = controlValue / 1000000.0;
    }

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::setSubexposureDuration(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{    
    auto controlValue = std::stod(req->getParameter("SubexposureDuration"));

    LOG_DEBUG<<"Camera "<< deviceNumber<< ": Set SubexposureDuration="<<controlValue;

    long microseconds = floor(controlValue * 1000000.0);

    Json::Value json;
        
    auto errorCode=ASISetControlValue(info.CameraID, ASI_EXPOSURE, microseconds, ASI_FALSE);

    json["ErrorCode"] = errorCode;
    json["ErrorMessage"] = asiErrorCodeMap[errorCode];

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}

void Camera::pulseGuide(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 int deviceNumber)
{
    Json::Value json;

    json["ErrorCode"] = "-1";
    json["ErrorMessage"] = "Pulse guiding not implemented";

    auto resp=HttpResponse::newHttpJsonResponse(json);

    callback(resp);
}