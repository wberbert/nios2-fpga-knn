# KNN Machine Learning Project on FPGA with NIOS II

This project implements a K-Nearest Neighbors (KNN) machine learning model using FPGA and the NIOS II processor. The goal is to demonstrate the capability of accelerating machine learning algorithms in hardware and integrating with the NIOS II processor for controlling and managing data processing.

## Overview

The KNN algorithm is a widely used supervised learning technique for classification and regression. This project adapts the KNN algorithm for hardware execution on an FPGA, using the NIOS II processor to coordinate processing and manage data.

### Features

- **KNN Algorithm Implementation**: Accelerates the KNN algorithm on FPGA hardware for efficient data processing.
- **NIOS II Processor**: Integrates the NIOS II processor for control and data flow management.
- **Communication Interface**: Facilitates communication between the FPGA and the NIOS II processor for data exchange and control.

## Requirements

- FPGA with support for the NIOS II processor (e.g., Altera DE-Series boards)
- FPGA development software (Quartus II or similar)
- IDE for NIOS II development (Eclipse with NIOS II EDS)
- Basic knowledge of VHDL/Verilog for FPGA development
- Familiarity with the KNN algorithm and machine learning

## Installation and Setup

1. **Development Environment Setup:**
   - Install Quartus II and NIOS II EDS software.
   - Configure the FPGA board and development environment according to the manufacturer's documentation.

2. **FPGA Hardware Compilation:**
   - Open the FPGA project in Quartus II.
   - Compile the design to generate the FPGA bitstream.

3. **NIOS II Processor Development and Compilation:**
   - Open the NIOS II project in the Eclipse IDE.
   - Implement control and communication code with the FPGA.
   - Compile the project to generate the firmware file.

4. **Loading and Execution:**
   - Load the FPGA bitstream onto the board using Quartus II.
   - Load the NIOS II firmware onto the board using the Eclipse IDE.
   - Run the KNN model on the FPGA and manage processing through the NIOS II.

## Usage

- **Running the KNN Algorithm**: The KNN algorithm runs on FPGA hardware. The NIOS II processor coordinates execution and manages data exchange.
- **Interaction**: Use configured communication interfaces to interact with the FPGA and NIOS II processor during processing.

## Examples

Provide sample data and code to demonstrate the execution of the KNN algorithm, if applicable.

## Contributing

Contributions are welcome! To contribute, please open a *pull request* or report issues in the *issues* section.

## License

This project is licensed under the GNU General Public License (GPL) - see the `LICENSE` file for details.

## Contact

For more information, contact Wanderson Berbert (wberbert@outlook.com).

---

# Versões em Português e Inglês

Este repositório contém informações em dois idiomas para facilitar o acesso:

- **[Versão em Português](readme.pt-br.md)**: Para usuários que preferem informações em português.
- **[English Version](readme.en.md)**: For users who prefer information in English.

Feel free to choose the version that best suits your needs!
