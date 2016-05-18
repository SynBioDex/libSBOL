# abort on error
set -e

# cd to restbed root dir
cd restbed

# change to openssl dir
pushd dependency/openssl
# build openssl shared libs for 64-bit
./Configure shared darwin64-x86_64-cc
make all

# configure cmake for restbed
popd
cmake -DBUILD_TESTS=YES -DBUILD_EXAMPLES=YES -DBUILD_SSL=YES -Dcrypto_LIBRARY=/Users/bryan/Dev/libSBOL/restbed/dependency/openssl/libcrypto.dylib -Dssl_LIBRARY=/Users/bryan/Dev/libSBOL/restbed/dependency/openssl/libssl.dylib -DBUILD_SHARED=YES -DCMAKE_INSTALL_PREFIX=./cmake-install .
make -j3 install
