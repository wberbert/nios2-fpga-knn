
module nios2_sopc (
	clk50_0_clk,
	knn_classe_prevista_in_export,
	knn_classe_prevista_pronto_in_export,
	knn_dados_atributo_out_export,
	knn_dados_pronto_out_export,
	knn_dados_valor_out_export,
	knn_k_export,
	knn_reset_out_export,
	knn_treinamento_out_export,
	pio_0_external_connection_export,
	reset_clk50_0_reset_n,
	rs232_0_external_interface_RXD,
	rs232_0_external_interface_TXD,
	sdram_0_wire_addr,
	sdram_0_wire_ba,
	sdram_0_wire_cas_n,
	sdram_0_wire_cke,
	sdram_0_wire_cs_n,
	sdram_0_wire_dq,
	sdram_0_wire_dqm,
	sdram_0_wire_ras_n,
	sdram_0_wire_we_n,
	usb_0_external_interface_INT1,
	usb_0_external_interface_DATA,
	usb_0_external_interface_RST_N,
	usb_0_external_interface_ADDR,
	usb_0_external_interface_CS_N,
	usb_0_external_interface_RD_N,
	usb_0_external_interface_WR_N,
	usb_0_external_interface_INT0,
	vga_0_external_interface_CLK,
	vga_0_external_interface_HS,
	vga_0_external_interface_VS,
	vga_0_external_interface_BLANK,
	vga_0_external_interface_SYNC,
	vga_0_external_interface_R,
	vga_0_external_interface_G,
	vga_0_external_interface_B);	

	input		clk50_0_clk;
	input	[15:0]	knn_classe_prevista_in_export;
	input		knn_classe_prevista_pronto_in_export;
	output	[7:0]	knn_dados_atributo_out_export;
	output		knn_dados_pronto_out_export;
	output	[15:0]	knn_dados_valor_out_export;
	output	[3:0]	knn_k_export;
	output		knn_reset_out_export;
	output		knn_treinamento_out_export;
	output	[7:0]	pio_0_external_connection_export;
	input		reset_clk50_0_reset_n;
	input		rs232_0_external_interface_RXD;
	output		rs232_0_external_interface_TXD;
	output	[12:0]	sdram_0_wire_addr;
	output	[1:0]	sdram_0_wire_ba;
	output		sdram_0_wire_cas_n;
	output		sdram_0_wire_cke;
	output		sdram_0_wire_cs_n;
	inout	[31:0]	sdram_0_wire_dq;
	output	[3:0]	sdram_0_wire_dqm;
	output		sdram_0_wire_ras_n;
	output		sdram_0_wire_we_n;
	input		usb_0_external_interface_INT1;
	inout	[15:0]	usb_0_external_interface_DATA;
	output		usb_0_external_interface_RST_N;
	output	[1:0]	usb_0_external_interface_ADDR;
	output		usb_0_external_interface_CS_N;
	output		usb_0_external_interface_RD_N;
	output		usb_0_external_interface_WR_N;
	input		usb_0_external_interface_INT0;
	output		vga_0_external_interface_CLK;
	output		vga_0_external_interface_HS;
	output		vga_0_external_interface_VS;
	output		vga_0_external_interface_BLANK;
	output		vga_0_external_interface_SYNC;
	output	[7:0]	vga_0_external_interface_R;
	output	[7:0]	vga_0_external_interface_G;
	output	[7:0]	vga_0_external_interface_B;
endmodule
