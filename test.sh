docker rm -f uri &>/dev/null || true
docker run -d -it --name uri --privileged octopusprime/test
docker exec uri mkdir uri
docker cp . uri:/uri
docker exec uri bash -c "
	cd uri; 
	bjam toolset=$1 debug -j$2
"
docker cp uri:/uri/bin .
