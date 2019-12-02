#!/bin/sh
source ./nios2-environment.sh
cp -rvf ../../../../../CodeBlocks/01.Machine\ Learning/knn.v02/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn/
cp -rvf ../../../../../CodeBlocks/01.Machine\ Learning/fpga_knn_treinamento/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn
cp -rvf ../../../../../CodeBlocks/01.Machine\ Learning/fpga_knn_teste/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn
cp -rvf ../../../../../CodeBlocks/01.Machine\ Learning/nios2_knn_treinamento_teste/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn
cp -rvf ../../../../../CodeBlocks/01.Machine\ Learning/fpga_knn_iris_teste/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn
cp -rvf ../../../../../CodeBlocks/01.Machine\ Learning/fpga_knn_iris_treinamento/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn
cp -rvf ../../../../../CodeBlocks/01.Machine\ Learning/nios2_knn_iris_treinamento_teste/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn
cd buildroot-2019.02.3/
make
cd ../linux-socfpga/
make zImage
cd ..
nios2-download ./linux-socfpga/arch/nios2/boot/zImage -g
nios2-terminal
