#/bin/sh
echo "------------------------------ [BUILD] ------------------------------"
cd build/
rm -rf ./*
CC=/usr/local/opt/llvm/bin/clang CXX=/usr/local/opt/llvm/bin/clang++ cmake ../
cmake --build .

if [ ! -f main ]; then
  echo "------------------------------ [ FAILED ] ------------------------------"
  exit -1
fi

echo "------------------------------ [ RUN ] ------------------------------"
./main
