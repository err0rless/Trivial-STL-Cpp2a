#/bin/sh
echo "------------------------------ [BUILD] ------------------------------"
rm -rf build
mkdir build
cd build/
CC=/usr/local/opt/llvm/bin/clang CXX=/usr/local/opt/llvm/bin/clang++ cmake ../
cmake --build .

if [ ! -f src/main ]; then
  echo "------------------------------ [ FAILED ] ------------------------------"
  exit -1
fi

echo "------------------------------ [ RUN ] ------------------------------"
src/main
cd .. ; rm -rf build
