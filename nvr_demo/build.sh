export LD_LIBRARY_PATH=/home/liushangyang/dev/consoleDemo/lib:/home/liushangyang/dev/consoleDemo/lib/HCNetSDKCom:$LD_LIBRARY_PATH;
cd nvr_demo
rm -rf build out
mkdir build out
cd ./build
cmake ..
make -j
cd ../out
./nvr_demo
