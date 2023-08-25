#pragma once

#include <drogon/HttpController.h>
#include <zwo/ASICamera2.h>

using namespace drogon;

namespace api::v1
{
  class Camera : public drogon::HttpController<Camera>
  {
    private:
      bool connected;
      ASI_CAMERA_INFO info;

    public:
      METHOD_LIST_BEGIN
      // device generic methods
      METHOD_ADD(Camera::getConnected, "/{1}/connected", Get);
      METHOD_ADD(Camera::setConnected, "/{1}/connected", Put);

      //camera methods
      METHOD_ADD(Camera::getBayerOffsetX, "/{1}/bayerOffsetX", Get);
      METHOD_ADD(Camera::getBayerOffsetY, "/{1}/bayerOffsetY", Get);
      METHOD_ADD(Camera::getBinX, "/{1}/binX", Get);
      METHOD_ADD(Camera::getBinY, "/{1}/binY", Get);
      METHOD_ADD(Camera::setBinX, "/{1}/binX", Put);
      METHOD_ADD(Camera::setBinY, "/{1}/binY", Put);
      METHOD_ADD(Camera::getCameraState, "/{1}/camerastate", Get);
      METHOD_ADD(Camera::getCameraXSize, "/{1}/cameraxsize", Get);
      METHOD_ADD(Camera::getCameraYSize, "/{1}/cameraysize", Get);
      METHOD_ADD(Camera::getCanAbortExposure, "/{1}/canabortexposure", Get);
      METHOD_ADD(Camera::getCanAsymmetricBin, "/{1}/canasymmetricbin", Get);
      METHOD_ADD(Camera::getCanFastReadout, "/{1}/canfastreadout", Get);
      METHOD_ADD(Camera::getCanGetCoolerPower, "/{1}/cangetcoolerpower", Get);
      METHOD_ADD(Camera::getCanPulseGuide, "/{1}/canpulseguide", Get);
      METHOD_ADD(Camera::getCanSetCcdTemperature, "/{1}/cansetccdtemperature", Get);
      METHOD_ADD(Camera::getCanStopExposure, "/{1}/canstopexposure", Get);
      METHOD_ADD(Camera::getCcdTemperature, "/{1}/ccdtemperature", Get);
      METHOD_ADD(Camera::getCoolerOn, "/{1}/cooleron", Get);
      METHOD_ADD(Camera::setCoolerOn, "/{1}/cooleron", Put);
      METHOD_ADD(Camera::getCoolerPower, "/{1}/coolerpower", Get);
      METHOD_ADD(Camera::getElectronsPerAdu, "/{1}/electronsperadu", Get);
      METHOD_ADD(Camera::getExposureMax, "/{1}/exposuremax", Get);
      METHOD_ADD(Camera::getExposureMin, "/{1}/exposuremin", Get);
      METHOD_ADD(Camera::getExposureResolution, "/{1}/exposureresolution", Get);
      METHOD_ADD(Camera::getFastReadout, "/{1}/fastreadout", Get);
      METHOD_ADD(Camera::setFastReadout, "/{1}/fastreadout", Put);
      METHOD_ADD(Camera::getFullWellCapacity, "/{1}/fullwellcapacity", Get);
      METHOD_ADD(Camera::getGain, "/{1}/gain", Get);
      METHOD_ADD(Camera::setGain, "/{1}/gain", Put);
      METHOD_ADD(Camera::getGainMax, "/{1}/gainmax", Get);
      METHOD_ADD(Camera::getGainMin, "/{1}/gainmin", Get);
      METHOD_ADD(Camera::getGains, "/{1}/gains", Get);
      METHOD_ADD(Camera::getHasShutter, "/{1}/hasshutter", Get);
      METHOD_ADD(Camera::getHeatsinkTemperature, "/{1}/heatsinktemperature", Get);
      METHOD_ADD(Camera::getImageReady, "/{1}/imageready", Get);
      METHOD_ADD(Camera::getIsPulseGuiding, "/{1}/ispulseguiding", Get);
      METHOD_ADD(Camera::getLastExposureDuration, "/{1}/lastexposureduration", Get);
      METHOD_ADD(Camera::getLastExposureStartTime, "/{1}/lastexposurestarttime", Get);
      METHOD_LIST_END
      
      void getConnected(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setConnected(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getBayerOffsetX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getBayerOffsetY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getBinX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getBinY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setBinX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setBinY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCameraState(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCameraXSize(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCameraYSize(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCanAbortExposure(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCanAsymmetricBin(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCanFastReadout(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCanGetCoolerPower(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCanPulseGuide(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCanSetCcdTemperature(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCanStopExposure(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCcdTemperature(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCoolerOn(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setCoolerOn(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCoolerPower(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getElectronsPerAdu(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getExposureMax(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getExposureMin(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getExposureResolution(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getFastReadout(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setFastReadout(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getFullWellCapacity(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getGain(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setGain(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getGainMax(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getGainMin(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getGains(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getHasShutter(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getHeatsinkTemperature(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getImageReady(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getIsPulseGuiding(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getLastExposureDuration(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getLastExposureStartTime(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
  };
}