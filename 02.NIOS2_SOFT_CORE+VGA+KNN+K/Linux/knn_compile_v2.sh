#!/bin/sh
source ./nios2-environment.sh
cp -rvf ../Software/Machine\ Learning/knn.v02/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn/v1
cp -rvf ../Software/Machine\ Learning/fpga_knn_treinamento/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn/v1
cp -rvf ../Software/Machine\ Learning/fpga_knn_teste/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn/v1
cp -rvf ../Software/Machine\ Learning/nios2_knn_treinamento_teste/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn/v1
cp -rvf ../Software/Machine\ Learning/fpga_knn_iris_teste/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn/v1
cp -rvf ../Software/Machine\ Learning/fpga_knn_iris_treinamento/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn/v1
cp -rvf ../Software/Machine\ Learning/nios2_knn_iris_treinamento_teste/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn/v1

cp -rvf ../Software/Machine\ Learning/fpga_knn_treinamento_v2/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn/v2
cp -rvf ../../03.NIOS2_SOFT_CORE+VGA+KNN+K+F/Software/Machine\ Learning/nios2_knn_iris_treinamento_teste/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn/v2
# cp -rvf ../Software/Machine\ Learning/fpga_knn_treinamento_v2/Build/NIOS2/bin/Debug/iris_treinamento.txt ./buildroot-2019.02.3/output/target/root/knn/v2/data
# cp -rvf ../Software/Machine\ Learning/fpga_knn_treinamento_v2/Build/NIOS2/bin/Debug/skin_nonskin_treinamento.txt ./buildroot-2019.02.3/output/target/root/knn/v2/data
# cp -rvf ../Software/Machine\ Learning/fpga_knn_treinamento_v2/Build/NIOS2/bin/Debug/skin_nonskin_treinamento_1.txt ./buildroot-2019.02.3/output/target/root/knn/v2/data
# cp -rvf ../Software/Machine\ Learning/fpga_knn_treinamento_v2/Build/NIOS2/bin/Debug/skin_nonskin_treinamento_2.txt ./buildroot-2019.02.3/output/target/root/knn/v2/data

cp -rvf ../Software/Machine\ Learning/fpga_knn_teste_v2/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn/v2
# cp -rvf ../Software/Machine\ Learning/fpga_knn_teste_v2/Build/NIOS2/bin/Debug/iris_teste.txt ./buildroot-2019.02.3/output/target/root/knn/v2/data
# cp -rvf ../Software/Machine\ Learning/fpga_knn_teste_v2/Build/NIOS2/bin/Debug/skin_nonskin_teste.txt ./buildroot-2019.02.3/output/target/root/knn/v2/data

cp -rvf ../Software/Machine\ Learning/nios2_knn_treinamento_teste_bertini_a/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn/bertini
cp -rvf ../Software/Machine\ Learning/nios2_knn_treinamento_teste_bertini_b/Build/NIOS2/bin/Debug/* ./buildroot-2019.02.3/output/target/root/knn/bertini

cp -rvf ../Software/Machine\ Learning/fpga_knn_treinamento_limitado/Build/NIOS2/bin/Debug/*     ./buildroot-2019.02.3/output/target/root/knn/v3
cp -rvf ../Software/Machine\ Learning/fpga_knn_treinamento_limitado/Build/NIOS2/bin/Release/*   ./buildroot-2019.02.3/output/target/root/knn/v3

cd buildroot-2019.02.3/
make
cd ../linux-socfpga/
make zImage
cd ..
nios2-download ./linux-socfpga/arch/nios2/boot/zImage -g
nios2-terminal
