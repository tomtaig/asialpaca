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
      METHOD_ADD(Camera::action, "/{1}/action", Put);
      METHOD_ADD(Camera::commandBlind, "/{1}/commandblind", Put);
      METHOD_ADD(Camera::commandBool, "/{1}/commandbool", Put);
      METHOD_ADD(Camera::commandString, "/{1}/commandstring", Put);
      METHOD_ADD(Camera::getConnected, "/{1}/connected", Get);
      METHOD_ADD(Camera::setConnected, "/{1}/connected", Put);
      METHOD_ADD(Camera::getDescription, "/{1}/description", Get);
      METHOD_ADD(Camera::getDriverInfo, "/{1}/driverinfo", Get);
      METHOD_ADD(Camera::getDriverVersion, "/{1}/driverversion", Get);
      METHOD_ADD(Camera::getInterfaceVersion, "/{1}/interfaceversion", Get);
      METHOD_ADD(Camera::getName, "/{1}/name", Get);
      METHOD_ADD(Camera::getSupportedActions, "/{1}/supportedactions", Get);

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
      METHOD_ADD(Camera::getMaxAdu, "/{1}/maxadu", Get);
      METHOD_ADD(Camera::getMaxBinX, "/{1}/maxbinx", Get);
      METHOD_ADD(Camera::getMaxBinY, "/{1}/maxbiny", Get);
      METHOD_ADD(Camera::getNumX, "/{1}/numx", Get);
      METHOD_ADD(Camera::setNumX, "/{1}/numx", Put);
      METHOD_ADD(Camera::getNumY, "/{1}/numy", Get);
      METHOD_ADD(Camera::setNumY, "/{1}/numy", Put);
      METHOD_ADD(Camera::getOffset, "/{1}/offset", Get);
      METHOD_ADD(Camera::setOffset, "/{1}/offset", Put);
      METHOD_ADD(Camera::getOffsetMax, "/{1}/offsetmax", Get);
      METHOD_ADD(Camera::getOffsetMin, "/{1}/offsetmin", Get);
      METHOD_ADD(Camera::getOffsets, "/{1}/offsets", Get);
      METHOD_ADD(Camera::getPercentCompleted, "/{1}/percentcompleted", Get);
      METHOD_ADD(Camera::getPixelSizeX, "/{1}/pixelsizex", Get);
      METHOD_ADD(Camera::getPixelSizeY, "/{1}/pixelsizey", Get);
      METHOD_ADD(Camera::getReadoutModes, "/{1}/readoutmodes", Get);
      METHOD_ADD(Camera::getReadoutMode, "/{1}/readoutmode", Get);
      METHOD_ADD(Camera::setReadoutMode, "/{1}/readoutmode", Put);
      METHOD_ADD(Camera::getSensorName, "/{1}/sensorname", Get);
      METHOD_ADD(Camera::getSensorType, "/{1}/sensortype", Get);
      METHOD_ADD(Camera::getSetCcdTemperature, "/{1}/setccdtemperature", Get);
      METHOD_ADD(Camera::setSetCcdTemperature, "/{1}/setccdtemperature", Put);
      METHOD_ADD(Camera::getStartX, "/{1}/startx", Get);
      METHOD_ADD(Camera::setStartX, "/{1}/startx", Put);
      METHOD_ADD(Camera::getStartY, "/{1}/starty", Get);
      METHOD_ADD(Camera::setStartY, "/{1}/starty", Put);
      METHOD_ADD(Camera::getSubexposureDuration, "/{1}/subexposureduration", Get);
      METHOD_ADD(Camera::setSubexposureDuration, "/{1}/subexposureduration", Put);
      METHOD_ADD(Camera::abortExposure, "/{1}/abortexposure", Put);
      METHOD_ADD(Camera::pulseGuide, "/{1}/pulseguide", Put);
      METHOD_ADD(Camera::startExposure, "/{1}/startexposure", Put);
      METHOD_ADD(Camera::stopExposure, "/{1}/stopexposure", Put);
      METHOD_LIST_END
      
      void action(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void commandBlind(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void commandBool(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void commandString(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getConnected(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setConnected(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getDescription(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getDriverInfo(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getDriverVersion(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getInterfaceVersion(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getName(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getSupportedActions(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);


      void getBayerOffsetX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getBayerOffsetY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getBinX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getBinY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setBinX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setBinY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCameraState (const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
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
      void getMaxAdu(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getMaxBinX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getMaxBinY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getNumX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setNumX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getNumY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setNumY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getOffset(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setOffset(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getOffsetMax(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getOffsetMin(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getOffsets(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getPercentCompleted(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getPixelSizeX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getPixelSizeY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getReadoutModes(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getReadoutMode(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setReadoutMode(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getSensorName(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getSensorType(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getSetCcdTemperature(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setSetCcdTemperature(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getStartX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setStartX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getStartY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setStartY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getSubexposureDuration(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setSubexposureDuration(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void abortExposure(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void pulseGuide(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void startExposure(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void stopExposure(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
  };
}