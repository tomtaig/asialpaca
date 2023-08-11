curl -X PUT \
"http://localhost:8080/api/v1/camera/0/connected" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&Connected=true" 

curl -X GET \
"http://localhost:8080/api/v1/camera/0/bayerOffsetX" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=" 

curl -X GET \
"http://localhost:8080/api/v1/camera/0/bayerOffsetY" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/binX" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&BinX=2"

curl -X PUT \
"http://localhost:8080/api/v1/camera/0/binY" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID=&BinY=2"

curl -X GET \
"http://localhost:8080/api/v1/camera/0/binX" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

curl -X GET \
"http://localhost:8080/api/v1/camera/0/binY" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

curl -X GET \
"http://localhost:8080/api/v1/camera/0/cameraxsize" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

curl -X GET \
"http://localhost:8080/api/v1/camera/0/cameraysize" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="

curl -X GET \
"http://localhost:8080/api/v1/camera/0/canabortexposure" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="


curl -X GET \
"http://localhost:8080/api/v1/camera/0/canfastreadout" \
-H "accept: application/json" \
-H "Content-Type: application/x-www-form-urlencoded" \
-d "ClientID=&ClientTransactionID="