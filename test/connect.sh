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

echo $'\n'http://localhost:8080/api/v1/camera/0/electronsperadu

curl -X GET \
"http://localhost:8080/api/v1/camera/0/electronsperadu" \
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