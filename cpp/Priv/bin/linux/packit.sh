#!/bin/sh
DAOLDPWD=`pwd`
cd bin/linux
./upx -9 agobot3
./upx -9 crypt
./upx -9 getmd5
cd $DAOLDPWD
