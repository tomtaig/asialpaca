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
      //METHOD_ADD(Camera::getCameraState, "/{1}/camerastate", Get);
      METHOD_ADD(Camera::getCameraXSize, "/{1}/cameraxsize", Get);
      METHOD_ADD(Camera::getCameraYSize, "/{1}/cameraysize", Get);
      METHOD_ADD(Camera::getCanAbortExposure, "/{1}/canabortexposure", Get);
      METHOD_ADD(Camera::getCanAbortExposure, "/{1}/canasymmetricbin", Get);
      METHOD_ADD(Camera::getCanFastReadout, "/{1}/canfastreadout", Get);
      METHOD_LIST_END
      
      void getConnected(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setConnected(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getBayerOffsetX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getBayerOffsetY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getBinX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getBinY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setBinX(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void setBinY(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCameraXSize(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCameraYSize(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCanAbortExposure(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
      void getCanFastReadout(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int deviceNumber);
  };
}