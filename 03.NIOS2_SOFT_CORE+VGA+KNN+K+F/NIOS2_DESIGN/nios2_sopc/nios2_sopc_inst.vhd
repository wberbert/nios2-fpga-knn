	component nios2_sopc is
		port (
			clk50_0_clk                          : in    std_logic                     := 'X';             -- clk
			knn_classe_prevista_in_export        : in    std_logic_vector(15 downto 0) := (others => 'X'); -- export
			knn_classe_prevista_pronto_in_export : in    std_logic                     := 'X';             -- export
			knn_dados_atributo_out_export        : out   std_logic_vector(7 downto 0);                     -- export
			knn_dados_pronto_out_export          : out   std_logic;                                        -- export
			knn_dados_valor_out_export           : out   std_logic_vector(15 downto 0);                    -- export
			knn_k_export                         : out   std_logic_vector(3 downto 0);                     -- export
			knn_reset_out_export                 : out   std_logic;                                        -- export
			knn_treinamento_out_export           : out   std_logic;                                        -- export
			pio_0_external_connection_export     : out   std_logic_vector(7 downto 0);                     -- export
			reset_clk50_0_reset_n                : in    std_logic                     := 'X';             -- reset_n
			rs232_0_external_interface_RXD       : in    std_logic                     := 'X';             -- RXD
			rs232_0_external_interface_TXD       : out   std_logic;                                        -- TXD
			sdram_0_wire_addr                    : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_0_wire_ba                      : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_0_wire_cas_n                   : out   std_logic;                                        -- cas_n
			sdram_0_wire_cke                     : out   std_logic;                                        -- cke
			sdram_0_wire_cs_n                    : out   std_logic;                                        -- cs_n
			sdram_0_wire_dq                      : inout std_logic_vector(31 downto 0) := (others => 'X'); -- dq
			sdram_0_wire_dqm                     : out   std_logic_vector(3 downto 0);                     -- dqm
			sdram_0_wire_ras_n                   : out   std_logic;                                        -- ras_n
			sdram_0_wire_we_n                    : out   std_logic;                                        -- we_n
			usb_0_external_interface_INT1        : in    std_logic                     := 'X';             -- INT1
			usb_0_external_interface_DATA        : inout std_logic_vector(15 downto 0) := (others => 'X'); -- DATA
			usb_0_external_interface_RST_N       : out   std_logic;                                        -- RST_N
			usb_0_external_interface_ADDR        : out   std_logic_vector(1 downto 0);                     -- ADDR
			usb_0_external_interface_CS_N        : out   std_logic;                                        -- CS_N
			usb_0_external_interface_RD_N        : out   std_logic;                                        -- RD_N
			usb_0_external_interface_WR_N        : out   std_logic;                                        -- WR_N
			usb_0_external_interface_INT0        : in    std_logic                     := 'X';             -- INT0
			vga_0_external_interface_CLK         : out   std_logic;                                        -- CLK
			vga_0_external_interface_HS          : out   std_logic;                                        -- HS
			vga_0_external_interface_VS          : out   std_logic;                                        -- VS
			vga_0_external_interface_BLANK       : out   std_logic;                                        -- BLANK
			vga_0_external_interface_SYNC        : out   std_logic;                                        -- SYNC
			vga_0_external_interface_R           : out   std_logic_vector(7 downto 0);                     -- R
			vga_0_external_interface_G           : out   std_logic_vector(7 downto 0);                     -- G
			vga_0_external_interface_B           : out   std_logic_vector(7 downto 0)                      -- B
		);
	end component nios2_sopc;

	u0 : component nios2_sopc
		port map (
			clk50_0_clk                          => CONNECTED_TO_clk50_0_clk,                          --                       clk50_0.clk
			knn_classe_prevista_in_export        => CONNECTED_TO_knn_classe_prevista_in_export,        --        knn_classe_prevista_in.export
			knn_classe_prevista_pronto_in_export => CONNECTED_TO_knn_classe_prevista_pronto_in_export, -- knn_classe_prevista_pronto_in.export
			knn_dados_atributo_out_export        => CONNECTED_TO_knn_dados_atributo_out_export,        --        knn_dados_atributo_out.export
			knn_dados_pronto_out_export          => CONNECTED_TO_knn_dados_pronto_out_export,          --          knn_dados_pronto_out.export
			knn_dados_valor_out_export           => CONNECTED_TO_knn_dados_valor_out_export,           --           knn_dados_valor_out.export
			knn_k_export                         => CONNECTED_TO_knn_k_export,                         --                         knn_k.export
			knn_reset_out_export                 => CONNECTED_TO_knn_reset_out_export,                 --                 knn_reset_out.export
			knn_treinamento_out_export           => CONNECTED_TO_knn_treinamento_out_export,           --           knn_treinamento_out.export
			pio_0_external_connection_export     => CONNECTED_TO_pio_0_external_connection_export,     --     pio_0_external_connection.export
			reset_clk50_0_reset_n                => CONNECTED_TO_reset_clk50_0_reset_n,                --                 reset_clk50_0.reset_n
			rs232_0_external_interface_RXD       => CONNECTED_TO_rs232_0_external_interface_RXD,       --    rs232_0_external_interface.RXD
			rs232_0_external_interface_TXD       => CONNECTED_TO_rs232_0_external_interface_TXD,       --                              .TXD
			sdram_0_wire_addr                    => CONNECTED_TO_sdram_0_wire_addr,                    --                  sdram_0_wire.addr
			sdram_0_wire_ba                      => CONNECTED_TO_sdram_0_wire_ba,                      --                              .ba
			sdram_0_wire_cas_n                   => CONNECTED_TO_sdram_0_wire_cas_n,                   --                              .cas_n
			sdram_0_wire_cke                     => CONNECTED_TO_sdram_0_wire_cke,                     --                              .cke
			sdram_0_wire_cs_n                    => CONNECTED_TO_sdram_0_wire_cs_n,                    --                              .cs_n
			sdram_0_wire_dq                      => CONNECTED_TO_sdram_0_wire_dq,                      --                              .dq
			sdram_0_wire_dqm                     => CONNECTED_TO_sdram_0_wire_dqm,                     --                              .dqm
			sdram_0_wire_ras_n                   => CONNECTED_TO_sdram_0_wire_ras_n,                   --                              .ras_n
			sdram_0_wire_we_n                    => CONNECTED_TO_sdram_0_wire_we_n,                    --                              .we_n
			usb_0_external_interface_INT1        => CONNECTED_TO_usb_0_external_interface_INT1,        --      usb_0_external_interface.INT1
			usb_0_external_interface_DATA        => CONNECTED_TO_usb_0_external_interface_DATA,        --                              .DATA
			usb_0_external_interface_RST_N       => CONNECTED_TO_usb_0_external_interface_RST_N,       --                              .RST_N
			usb_0_external_interface_ADDR        => CONNECTED_TO_usb_0_external_interface_ADDR,        --                              .ADDR
			usb_0_external_interface_CS_N        => CONNECTED_TO_usb_0_external_interface_CS_N,        --                              .CS_N
			usb_0_external_interface_RD_N        => CONNECTED_TO_usb_0_external_interface_RD_N,        --                              .RD_N
			usb_0_external_interface_WR_N        => CONNECTED_TO_usb_0_external_interface_WR_N,        --                              .WR_N
			usb_0_external_interface_INT0        => CONNECTED_TO_usb_0_external_interface_INT0,        --                              .INT0
			vga_0_external_interface_CLK         => CONNECTED_TO_vga_0_external_interface_CLK,         --      vga_0_external_interface.CLK
			vga_0_external_interface_HS          => CONNECTED_TO_vga_0_external_interface_HS,          --                              .HS
			vga_0_external_interface_VS          => CONNECTED_TO_vga_0_external_interface_VS,          --                              .VS
			vga_0_external_interface_BLANK       => CONNECTED_TO_vga_0_external_interface_BLANK,       --                              .BLANK
			vga_0_external_interface_SYNC        => CONNECTED_TO_vga_0_external_interface_SYNC,        --                              .SYNC
			vga_0_external_interface_R           => CONNECTED_TO_vga_0_external_interface_R,           --                              .R
			vga_0_external_interface_G           => CONNECTED_TO_vga_0_external_interface_G,           --                              .G
			vga_0_external_interface_B           => CONNECTED_TO_vga_0_external_interface_B            --                              .B
		);

