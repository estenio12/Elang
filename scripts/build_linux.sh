cd .

# Compile elang compiler
cd ./elangc
make

# copy binary result to realease folder
cd ..
cp -r ./elangc/Bin/elc ./released/linux/elang/tools/

# Compiler manager
cd ./source
make

# copy binary result to realease folder
cd ..
cp -r ./source/bin/elangc ./released/linux/elang/

# Compress
cd ./released/linux/
zip -r elang.zip ./elang/

# Notify
echo 'Compile finished!'