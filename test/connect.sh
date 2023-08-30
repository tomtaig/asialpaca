echo http://localhost:8080/api/v1/camera/0/connected

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/connected" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&Connected=true"

echo $'\n'http://localhost:8080/api/v1/camera/0/bayerOffsetX

curl -X GET \
"http://localhost:8080/api/v1/camera/0/bayerOffsetX" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=" 

echo $'\n'http://localhost:8080/api/v1/camera/0/bayerOffsetY

curl -X GET \
"http://localhost:8080/api/v1/camera/0/bayerOffsetY" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/binX

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/binX" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&BinX=2"

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/binY

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/binY" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&BinY=2"

echo $'\n'http://localhost:8080/api/v1/camera/0/binX

curl -X GET \
"http://localhost:8080/api/v1/camera/0/binX" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/binY

curl -X GET \
"http://localhost:8080/api/v1/camera/0/binY" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/cameraxsize

curl -X GET \
"http://localhost:8080/api/v1/camera/0/cameraxsize" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/cameraysize

curl -X GET \
"http://localhost:8080/api/v1/camera/0/cameraysize" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/canabortexposure

curl -X GET \
"http://localhost:8080/api/v1/camera/0/canabortexposure" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/canasymmetricbin

curl -X GET \
"http://localhost:8080/api/v1/camera/0/canasymmetricbin" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/canfastreadout

curl -X GET \
"http://localhost:8080/api/v1/camera/0/canfastreadout" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/cangetcoolerpower

curl -X GET \
"http://localhost:8080/api/v1/camera/0/cangetcoolerpower" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/canpulseguide

curl -X GET \
"http://localhost:8080/api/v1/camera/0/canpulseguide" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/cansetccdtemperature

curl -X GET \
"http://localhost:8080/api/v1/camera/0/cansetccdtemperature" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/canstopexposure

curl -X GET \
"http://localhost:8080/api/v1/camera/0/canstopexposure" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/ccdtemperature

curl -X GET \
"http://localhost:8080/api/v1/camera/0/ccdtemperature" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/cooleron

curl -X GET \
"http://localhost:8080/api/v1/camera/0/cooleron" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/cooleron

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/cooleron" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&CoolerOn=True"

echo $'\n'http://localhost:8080/api/v1/camera/0/coolerpower

curl -X GET \
"http://localhost:8080/api/v1/camera/0/coolerpower" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/exposuremax

curl -X GET \
"http://localhost:8080/api/v1/camera/0/exposuremax" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/exposuremin

curl -X GET \
"http://localhost:8080/api/v1/camera/0/exposuremin" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/exposureresolution

curl -X GET \
"http://localhost:8080/api/v1/camera/0/exposureresolution" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/fastreadout

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/fastreadout" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&FastReadout=True"

echo $'\n'http://localhost:8080/api/v1/camera/0/fastreadout

curl -X GET \
"http://localhost:8080/api/v1/camera/0/fastreadout" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/fastreadout

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/fastreadout" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&FastReadout=False"

echo $'\n'http://localhost:8080/api/v1/camera/0/fastreadout

curl -X GET \
"http://localhost:8080/api/v1/camera/0/fastreadout" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/gain

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/gain" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&Gain=0"

echo $'\n'http://localhost:8080/api/v1/camera/0/gain

curl -X GET \
"http://localhost:8080/api/v1/camera/0/gain" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/electronsperadu

curl -X GET \
"http://localhost:8080/api/v1/camera/0/electronsperadu" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/gainmax

curl -X GET \
"http://localhost:8080/api/v1/camera/0/gainmax" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/gainmin

curl -X GET \
"http://localhost:8080/api/v1/camera/0/gainmin" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/fullwellcapacity

curl -X GET \
"http://localhost:8080/api/v1/camera/0/fullwellcapacity" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/gains

curl -X GET \
"http://localhost:8080/api/v1/camera/0/gains" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/hasshutter

curl -X GET \
"http://localhost:8080/api/v1/camera/0/hasshutter" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/heatsinktemperature

curl -X GET \
"http://localhost:8080/api/v1/camera/0/heatsinktemperature" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/imageready

curl -X GET \
"http://localhost:8080/api/v1/camera/0/imageready" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/ispulseguiding

curl -X GET \
"http://localhost:8080/api/v1/camera/0/ispulseguiding" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/lastexposureduration

curl -X GET \
"http://localhost:8080/api/v1/camera/0/lastexposureduration" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/lastexposurestarttime

curl -X GET \
"http://localhost:8080/api/v1/camera/0/lastexposurestarttime" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/maxadu

curl -X GET \
"http://localhost:8080/api/v1/camera/0/maxadu" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/maxbinx

curl -X GET \
"http://localhost:8080/api/v1/camera/0/maxbinx" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/maxbiny

curl -X GET \
"http://localhost:8080/api/v1/camera/0/maxbiny" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/numx

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/numx" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&NumX=32"

echo $'\n'http://localhost:8080/api/v1/camera/0/numx

curl -X GET \
"http://localhost:8080/api/v1/camera/0/numx" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/numy

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/numy" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&NumY=32"

echo $'\n'http://localhost:8080/api/v1/camera/0/numy

curl -X GET \
"http://localhost:8080/api/v1/camera/0/numy" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/offset

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/offset" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&Offset=10"

echo $'\n'http://localhost:8080/api/v1/camera/0/offset

curl -X GET \
"http://localhost:8080/api/v1/camera/0/offset" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/offsetmax

curl -X GET \
"http://localhost:8080/api/v1/camera/0/offsetmax" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/offsetmin

curl -X GET \
"http://localhost:8080/api/v1/camera/0/offsetmin" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/offsets

curl -X GET \
"http://localhost:8080/api/v1/camera/0/offsets" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/percentcompleted

curl -X GET \
"http://localhost:8080/api/v1/camera/0/percentcompleted" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/pixelsizex

curl -X GET \
"http://localhost:8080/api/v1/camera/0/pixelsizex" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/pixelsizey

curl -X GET \
"http://localhost:8080/api/v1/camera/0/pixelsizey" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/readoutmodes

curl -X GET \
"http://localhost:8080/api/v1/camera/0/readoutmodes" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/readoutmode

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/readoutmode" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&ReadoutMode=0"

echo $'\n'http://localhost:8080/api/v1/camera/0/readoutmode

curl -X GET \
"http://localhost:8080/api/v1/camera/0/readoutmode" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/sensorname

curl -X GET \
"http://localhost:8080/api/v1/camera/0/sensorname" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'http://localhost:8080/api/v1/camera/0/sensortype

curl -X GET \
"http://localhost:8080/api/v1/camera/0/sensortype" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/setccdtemperature

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/setccdtemperature" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&SetCCDTemperature=-5"

echo $'\n'http://localhost:8080/api/v1/camera/0/setccdtemperature

curl -X GET \
"http://localhost:8080/api/v1/camera/0/setccdtemperature" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/startx

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/startx" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&StartX=32"

echo $'\n'http://localhost:8080/api/v1/camera/0/startx

curl -X GET \
"http://localhost:8080/api/v1/camera/0/startx" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/starty

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/starty" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&StartY=32"

echo $'\n'http://localhost:8080/api/v1/camera/0/starty

curl -X GET \
"http://localhost:8080/api/v1/camera/0/starty" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/starty

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/subexposureduration" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&SubexposureDuration=5.1234561"

echo $'\n'http://localhost:8080/api/v1/camera/0/subexposureduration

curl -X GET \
"http://localhost:8080/api/v1/camera/0/subexposureduration" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/abortexposure

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/abortexposure" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/pulseguide

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/pulseguide" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/startexposure

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/startexposure" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&Duration=1&Light=False"

echo $'\n'PUT http://localhost:8080/api/v1/camera/0/stopexposure

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/stopexposure" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="