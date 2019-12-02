LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;


ENTITY knn is 
	PORT (
		CLOCK_50							: IN STD_LOGIC;
		
		
		KNN_DADOS_VALOR				: IN 		STD_LOGIC_VECTOR(15 DOWNTO 0) 	:= "0000000000000000";	--Valor do atributo a ser pasada para o KNN.
		KNN_DADOS_ATRIBUTO_N			: IN 		STD_LOGIC_VECTOR(7 DOWNTO 0) 		:= "00000000";				--Numero do atributo (0 a 255);
		KNN_DADOS_PRONTO 				: IN 		STD_LOGIC :='0';														--Setar para 1 quando a passagem os dados de atributos estiver pronto.
		
		KNN_CLASSE_PREVISTA			: OUT 	STD_LOGIC_VECTOR(15 DOWNTO 0);									--Classe de objeto que o KNN previu.
		KNN_CLASSE_PREVISTA_PRONTO	: OUT 	STD_LOGIC := '0';														--Dados prontos para serem lidos.
		
		KNN_TREINAMENTO				: IN 		STD_LOGIC := '0';														--Indica se o modulo KNN esta em modo de treinamento.
		KNN_RESET						: IN		STD_LOGIC := '0';														--Reseta o modulo KNN para uma nova entrada de dados.
		
		KNN_MAQUINA_ESTADO			: OUT 	STD_LOGIC_VECTOR(4 DOWNTO 0) := "00000";
		KNN_DEBUG_SINAIS				: OUT    STD_LOGIC_VECTOR(4 DOWNTO 0) := "00000";
 		--LED_1								: OUT 	STD_LOGIC := '0';
		--LED_2								: OUT 	STD_LOGIC := '0'
		KNN_DEBUG_KEY0					: IN		STD_LOGIC := '0'
	);
END ENTITY knn;

ARCHITECTURE knn_a of knn IS

/*
	--An example of how to use the function.
	signal a : unsigned(31 downto 0) :="00000000000000000000000000110010";   --50
	signal b : unsigned(15 downto 0) :=(others => '0');
	b <= sqrt ( a );  --function is "called" here.
	--b will contain the value "00000111" ( equals to 7) once the operation is done.
*/
	function  sqrt  ( d : UNSIGNED ) return UNSIGNED is
		variable a : unsigned(31 downto 0):=d;  --original input.
		variable q : unsigned(15 downto 0):=(others => '0');  --result.
		variable left,right,r : unsigned(17 downto 0):=(others => '0');  --input to adder/sub.r-remainder.
		variable i : integer:=0;

	begin
		for i in 0 to 15 loop
			right(0):='1';
			right(1):=r(17);
			right(17 downto 2):=q;
			left(1 downto 0):=a(31 downto 30);
			left(17 downto 2):=r(15 downto 0);
			a(31 downto 2):=a(29 downto 0);  --shifting by 2 bit.
			if ( r(17) = '1') then
				r := left + right;
			else
				r := left - right;
			end if;
			q(15 downto 1) := q(14 downto 0);
			q(0) := not r(17);
		end loop; 
		
		return q;

	end sqrt;

	type knn_registro_SLV_T	is array (integer range<>) OF STD_LOGIC_VECTOR(15 DOWNTO 0); 	-- Armazena dados do objeto ser classificado.
	type knn_registros_A_T 	is array (integer range<>) OF knn_registro_SLV_T; 					-- Armazena um array de objetos.
	
	/*type distancia_euclidiana_R_T is 
		record
			classe		: natural range 0 to 255;
			distancia 	: integer;
	
	end record;
	*/
	type distancia_euclidiana_R_T is
		record
			classe		: unsigned(15 downto 0);
			distancia 	: unsigned(15 downto 0);
	end record;
	
	type k_proximos_R_T is
		record
			classe		: integer;
			total			: integer;
	end record;
	
	type distancia_euclidiana_AR_T is array (integer range <>) of distancia_euclidiana_R_T;
	type k_proximos_AR_T is array (integer range <>) of k_proximos_R_T;
	
	type estado_T is (CARGA, CALCULAR, ORDENAR, RANQUEAR, PRONTO);  

	constant NUMERO_DE_ATRIBUTOS : integer := 7; -- Iniciando de 0, logo 8 atributos.
	
	constant MAX_KNN_K : integer := 16;				-- Maior valor possivel para K.
	
	constant KNN_K : STD_LOGIC_VECTOR(4 downto 0) := "00001"; -- provisoriamente definido.
	
	
	signal sng_estado : estado_T := CARGA;  
	
	shared variable kr_dados_treinamento 				: knn_registro_SLV_T(0 to NUMERO_DE_ATRIBUTOS);				--Dados de treinamento.
	shared variable kr_dados_teste						: knn_registro_SLV_T(0 to NUMERO_DE_ATRIBUTOS); 			--Dados da classe a ser prevista.
	shared variable krs_registros_treinamento			: knn_registros_A_T(0 to 15)(0 to NUMERO_DE_ATRIBUTOS); 	-- Recorset com registros de dados de treinameto.
	
	
	--shared variable r_distancia_euclidiana				: distancia_euclidiana_AR_T(0 to 255); --Armazena a distancia euclideana e sua classe. 
	--shared variable r_distancia_euclidiana_ordenada	: distancia_euclidiana_AR_T(0 to 255);	--Armazena a distancia euclideana em ordem crescente de distancia;
	
	--signal sng_distancia_euclidiana							: distancia_euclidiana_AR_T(0 to 15); 	--Armazena a distancia euclideana e sua classe. 
	shared variable vs_distancia_euclidiana				: distancia_euclidiana_AR_T(0 to 15); 	--Armazena a distancia euclideana e sua classe. 
	--signal sng_distancia_euclidiana_ordenada				: distancia_euclidiana_AR_T(0 to 15); 	--Armazena a distancia euclideana e sua classe. 
	shared variable vs_distancia_euclidiana_ordenada	: distancia_euclidiana_AR_T(0 to 15); 	--Armazena a distancia euclideana e sua classe. 

	
	signal sng_knn_calcular_distancia						: std_logic := '0';
	signal sng_knn_calcular_distancia_pronto				: std_logic := '0';

	signal sng_knn_ordenar 										: std_logic := '0';
	signal sng_knn_ordenar_pronto								: std_logic := '0';
	
	signal sng_knn_ranquear										: std_logic := '0';
	signal sng_knn_ranquear_pronto							: std_logic := '0';
	
	signal sng_knn_feito											: std_logic := '0';
	
	signal sng_knn_teste_pronto								: std_logic := '0';

	--signal sng_knn_classe_prevista_pronto					: std_logic := '0';
	
	signal sng_knn_classe_prevista							: std_logic_vector (15 downto 0);
	
	signal sng_reset												: std_logic := '0';
	
	signal sng_reset_p_knn_treinamento						: std_logic := '0';		
	signal sng_reset_p_knn_distancia_euclidiana			: std_logic := '0';
	signal sng_reset_p_knn_ordenar							: std_logic := '0';
	signal sng_reset_p_knn_proximos							: std_logic := '0';
	
	--signal sng_reset_treinamento								: std_logic := '0';
	
	--signal sng_leitura_pronta									: std_logic := '0';
	
	signal sng_int_total_registros							: integer;

	--signal sng_knn_classe_prevista_pronto				: std_logic;	
	
	
	
	
BEGIN

	/*
	PROCESSO 					: CARGA DE DADOS E TREINAMENTO
	
	SINAIS MONITORADOS		: 	sng_reset 							- Reset global do processo.
										sng_reset_p_knn_treinamento 	- Reset local do processo.
										KNN_DADOS_PRONTO 					- Sinal indicativo de quando os dadosenviados estao prontos.
	
	SINAIS NAO MONITORADOS	:	KNN_TREINAMENTO 					- Sinal utilizado para indicar treinamento ou teste.
										sng_knn_teste_pronto 			- Indica que os dados de teste ja foram carregados e estao prontos.
										
	OBJETIVO 					: 	O Objetivo deste processo e prover meios para entrar com os dados de treinamento
										e dados de teste para o algoritimo de KNN.
	
	*/
	p_knn_treinamento : process (sng_reset,  sng_reset_p_knn_treinamento, KNN_DADOS_PRONTO)
		
	begin
			
			if (sng_reset = '1') then
				
				sng_int_total_registros<= 0;
				sng_knn_teste_pronto <= '0';
				
			elsif (sng_reset_p_knn_treinamento = '1') then
				
				sng_knn_teste_pronto <= '0';
				
			else
			
				if (KNN_DADOS_PRONTO'event and KNN_DADOS_PRONTO = '1') then
					
					if (KNN_TREINAMENTO = '1') then
						
						sng_knn_teste_pronto <= '0';
						
						kr_dados_treinamento(to_integer(unsigned(KNN_DADOS_ATRIBUTO_N))) := KNN_DADOS_VALOR;
						
						if (KNN_DADOS_ATRIBUTO_N = "00000111") then -- Ultimo atributo do registro guarda a classe e armazena os valores no registro.
							
							krs_registros_treinamento(sng_int_total_registros) := kr_dados_treinamento;	
							sng_int_total_registros <= sng_int_total_registros + 1;
							
						end if;
					
					else
					
						kr_dados_teste(to_integer(unsigned(KNN_DADOS_ATRIBUTO_N))) := KNN_DADOS_VALOR;
						
						if (KNN_DADOS_ATRIBUTO_N = "00000111") then -- Ultimo atributo do registro guarda a classe.
							
							sng_knn_teste_pronto <= '1';
						
						else
							
							sng_knn_teste_pronto <= '0';
							
						end if;
						
					end if;
					
				end if;
			
			end if;
			
	end process;
	
	/*
	PROCESSO 					: CALCULO DA DISTANCIA EUCLIDIANA
	
	SINAIS MONITORADOS		: 	sng_reset 									- Reset global do processo.
										sng_reset_p_knn_treinamento 			- Reset local do processo.
										sng_knn_calcular_distancia				- Indca o momento de inicar o calculo.
	
	SINAIS NAO MONITORADOS	:	sng_knn_calcular_distancia_pronto	- Indica que o calculo da distancia esta pronto.
										
	OBJETIVO 					: 	O objetivo deste processo e efetuar o calculo da distancia euclidiana com base nas informacoes
										carregadas em kr_dados_teste e krs_registros_treinamento.
	
	*/
	
	p_knn_distancia_euclidiana : process (sng_reset, sng_reset_p_knn_distancia_euclidiana, sng_knn_calcular_distancia)

		variable int_atributo							: integer range 0 to NUMERO_DE_ATRIBUTOS	:=0;
		variable int_registro							: integer range 0 to 15 						:=0;
		variable uns_distancia							: unsigned(31 downto 0);
		--variable uns_distancia							: integer;
		variable v_distancia_euclidiana				: distancia_euclidiana_AR_T(0 to 15);
	
	begin
	
	
			if (sng_reset = '1') or (sng_reset_p_knn_distancia_euclidiana = '1') then
			
				sng_knn_calcular_distancia_pronto<= '0';
				uns_distancia := to_unsigned(0, 32);
			
			else
				
				--uns_distancia := 0;
				
				if (sng_knn_calcular_distancia'event and sng_knn_calcular_distancia = '1') then
				
					for int_registro in 0 to 15 loop
						
						v_distancia_euclidiana(int_registro).classe := 		"0000000000000000";
						v_distancia_euclidiana(int_registro).distancia := 	"1111111111111111";

					end loop;

					for int_registro in 0 to 15 loop	
							
							if int_registro = sng_int_total_registros then 
							
								exit;
							
							end if;
							
							v_distancia_euclidiana(int_registro).classe 	:= unsigned(krs_registros_treinamento(int_registro)(NUMERO_DE_ATRIBUTOS));
							uns_distancia := to_unsigned(0, 32);
							
							for int_atributo in 0 to (NUMERO_DE_ATRIBUTOS - 1) loop
								
								if ((to_integer(unsigned(kr_dados_teste(int_atributo)))) > (to_integer(unsigned(krs_registros_treinamento(int_registro)(int_atributo))))) then
										
									uns_distancia := uns_distancia + ((to_integer(unsigned(kr_dados_teste(int_atributo))) - (to_integer(unsigned(krs_registros_treinamento(int_registro)(int_atributo)))))**2);
								
								elsif ((to_integer(unsigned(kr_dados_teste(int_atributo)))) < (to_integer(unsigned(krs_registros_treinamento(int_registro)(int_atributo))))) then
								
									uns_distancia := uns_distancia + ((to_integer(unsigned(krs_registros_treinamento(int_registro)(int_atributo))) - (to_integer(unsigned(kr_dados_teste(int_atributo)))))**2);
									
								end if;
								
							end loop;
							
							v_distancia_euclidiana(int_registro).distancia := sqrt(uns_distancia);	
							--v_distancia_euclidiana(int_registro).distancia := sqrt(to_unsigned(uns_distancia, 32));
							--v_distancia_euclidiana(int_registro).distancia := uns_distancia(15 downto 0);
						
						--end if;
						
					end loop;
						
					--sng_distancia_euclidiana <= v_distancia_euclidiana;
					
					vs_distancia_euclidiana :=	 v_distancia_euclidiana;
					
					--sng_distancia_euclidiana <= v_distancia_euclidiana;
					
					sng_knn_calcular_distancia_pronto <= '1';
						
				end if;
	
			end if;
			
			
	end process;
	
	
	/*
	PROCESSO 					: ORDENACAO PARALLEL BUBLE SORT
	
	SINAIS MONITORADOS		: 	sng_reset 									- Reset global do processo.
										sng_reset_p_knn_treinamento 			- Reset local do processo.
										sng_knn_ordenar							- Indca o momento de inicar a ordenacao.
	
	SINAIS NAO MONITORADOS	:	sng_knn_ordenar_pronto					- Indica que a ordenacao esta pronta.
										
	OBJETIVO 					: 	o objetivo e ordenar as distancias euclicianas atraves de um algoritimo um pouco
										melhor que o buble sort.
	
	*/
	
	p_knn_ordenar : process(sng_reset, sng_reset_p_knn_ordenar, sng_knn_ordenar) 
	
		variable int_o, int_p, int_i	  				: integer;
		variable r_distancia_armazenada 				: distancia_euclidiana_AR_T (0 to 1);
		variable v_distancia_euclidiana				: distancia_euclidiana_AR_T (0 to 15);
		--variable v_temp									: distancia_euclidiana_R_T;
		

	begin
	
			if (sng_reset = '1') or (sng_reset_p_knn_ordenar = '1')then
				
				sng_knn_ordenar_pronto <= '0';
				
			else
				
				if (sng_knn_ordenar'event and sng_knn_ordenar = '1') then
					
--					for int_o in 0 to 15 loop
						
--						v_distancia_euclidiana(int_o).classe := "0000000000000000";
--						v_distancia_euclidiana(int_o).distancia := "1111111111111111";
						
--					end loop;

					v_distancia_euclidiana := vs_distancia_euclidiana;
					
/*					
					for int_o in 0 to 15 loop
					
						for int_i in 0 to 14 loop
							
							v_temp := v_distancia_euclidiana(int_i);
							
							if (v_distancia_euclidiana(int_i + 1).distancia < v_temp.distancia) then
									
									v_distancia_euclidiana(int_i) := v_distancia_euclidiana(int_i + 1);
									v_distancia_euclidiana(int_i + 1) := v_temp;
								
							end if;
						
						end loop;
						
					end loop;
			*/		
					

					for int_o in 0 to 15 loop
						
						for int_i in 0 to 6 loop
						
							r_distancia_armazenada(0).classe					:= v_distancia_euclidiana(((2 * int_i) + 1)).classe;
							r_distancia_armazenada(0).distancia				:= v_distancia_euclidiana(((2 * int_i) + 1)).distancia;
							
							r_distancia_armazenada(1).classe					:= v_distancia_euclidiana(((2 * int_i) + 2)).classe;
							r_distancia_armazenada(1).distancia				:= v_distancia_euclidiana(((2 * int_i) + 2)).distancia;

							
							if (to_integer(r_distancia_armazenada(0).distancia)) > (to_integer(r_distancia_armazenada(1).distancia)) then
								
								v_distancia_euclidiana(((2 * int_i) + 1)).classe		:= r_distancia_armazenada(1).classe;
								v_distancia_euclidiana(((2 * int_i) + 1)).distancia	:= r_distancia_armazenada(1).distancia;
								
								v_distancia_euclidiana(((2 * int_i) + 2)).classe		:= r_distancia_armazenada(0).classe;
								v_distancia_euclidiana(((2 * int_i) + 2)).distancia	:= r_distancia_armazenada(0).distancia;

							
							end if;
							
						end loop;
						
						for int_p in 0 to 7 loop
						
							r_distancia_armazenada(0).classe			:= v_distancia_euclidiana((2 * int_p)).classe;
							r_distancia_armazenada(0).distancia		:= v_distancia_euclidiana((2 * int_p)).distancia;
							
							r_distancia_armazenada(1).classe			:= v_distancia_euclidiana(((2 * int_p) + 1)).classe;
							r_distancia_armazenada(1).distancia		:= v_distancia_euclidiana(((2 * int_p) + 1)).distancia;

							if (to_integer(r_distancia_armazenada(0).distancia)) > (to_integer(r_distancia_armazenada(1).distancia)) then
								
								v_distancia_euclidiana((2 * int_p)).classe				:= r_distancia_armazenada(1).classe;
								v_distancia_euclidiana((2 * int_p)).distancia			:= r_distancia_armazenada(1).distancia;
								
								v_distancia_euclidiana(((2 * int_p) + 1)).classe		:= r_distancia_armazenada(0).classe;
								v_distancia_euclidiana(((2 * int_p) + 1)).distancia	:= r_distancia_armazenada(0).distancia;

							
							end if;
							
						end loop;
					
					end loop;

					
					--sng_distancia_euclidiana_ordenada <= v_distancia_euclidiana;
					--sng_distancia_euclidiana_ordenada <= sng_distancia_euclidiana;
					
--					for int_o in 0 to 15 loop
						
--						vs_distancia_euclidiana_ordenada(int_o).classe := v_distancia_euclidiana(int_o).classe;
--						vs_distancia_euclidiana_ordenada(int_o).distancia := v_distancia_euclidiana(int_o).distancia;
						
--					end loop;					
					vs_distancia_euclidiana_ordenada := v_distancia_euclidiana;
					
					sng_knn_ordenar_pronto <= '1';
					
				end if;
			
			end if;
			
	
	end process;
	
	p_knn_proximos	: process (sng_reset, sng_reset_p_knn_proximos, sng_knn_ranquear)
		variable	int_a 							: integer range 0 to MAX_KNN_K - 1;
		variable v_k_proximos					: k_proximos_AR_T(0 to MAX_KNN_K - 1);
		variable v_classe							: integer := 0;
		variable int_b								: integer := 0;
		variable bit_achou						: boolean := false;
		variable int_k_proximos_posicao 		: integer := 0;
		variable int_k_proximor_maior_total	: integer := 0;
		
	begin
		
		if (sng_reset = '1') or (sng_reset_p_knn_proximos = '1') then
		
			sng_knn_ranquear_pronto <= '0';
			
			v_classe := 0;
			int_b := 0;
			bit_achou := false;
			int_k_proximos_posicao := 0;
			int_k_proximor_maior_total := 0;
			--bln_totais_iguais := true;
			
			for int_a in 0 to (MAX_KNN_K - 1) loop
				v_k_proximos(int_a).classe := 0;
				v_k_proximos(int_a).total  := 0;
			end loop;
			
			int_a := 0;
			
		else

			if (sng_knn_ranquear'event and sng_knn_ranquear = '1') then
				
				--sng_knn_classe_prevista <= std_logic_vector(sng_distancia_euclidiana_ordenada(0).classe);
				
				--LOOP PARA CONTAR O TOTAL DE CADA CLASSE E COLOCAR EM UM VETOR DE TOTAIS DE CLASSE.
				for int_a in 0 to (to_integer(unsigned(KNN_K)) - 1) loop
					
					bit_achou := false;
					v_classe := to_integer(unsigned(vs_distancia_euclidiana_ordenada(int_a).classe));
					--v_classe := to_integer(unsigned(sng_distancia_euclidiana_ordenada(int_a).classe));
					
					for int_b in 0 to (MAX_KNN_K - 1) loop
						
						if v_classe = v_k_proximos(int_b).classe then
						
							v_k_proximos(int_b).total := v_k_proximos(int_b).total + 1;
							bit_achou := true;
							exit;
							
						end if;
						
					end loop;
					
					if bit_achou = false then
						
						v_k_proximos(int_k_proximos_posicao).classe := v_classe;
						v_k_proximos(int_k_proximos_posicao).total := 1;
						int_k_proximos_posicao := int_k_proximos_posicao + 1;
						
					end if;
					
				end loop;
				
				--LOOP PARA DEFINIR QUAL CLASSE POSSUI MAIOR CONTAGEM.
				for int_a in 0 to (v_k_proximos'length - 1) loop
					
					if v_k_proximos(int_a).total > int_k_proximor_maior_total then
						
						int_k_proximor_maior_total := v_k_proximos(int_a).total;
						v_classe := v_k_proximos(int_a).classe;
						
					end if;
					
--					if (bln_totais_iguais = true) then
						
--						if v_k_proximos(0).total /= v_k_proximos(int_a).total then
--							bln_totais_iguais := false;
--						end if;
						
--					end if;
				end loop;
				
				--sng_knn_classe_prevista <="0000000000000000";
				
				if (KNN_K = "00001" ) then
						--sng_knn_classe_prevista <= std_logic_vector(vs_distancia_euclidiana(int_debug).classe);		
 					 sng_knn_classe_prevista <= std_logic_vector(vs_distancia_euclidiana_ordenada(0).classe);
					 --sng_knn_classe_prevista <= "0000000000000000";
					--sng_knn_classe_prevista <= std_logic_vector(sng_distancia_euclidiana_ordenada(0).classe);
					--int_debug := int_debug + 1;
				else
					sng_knn_classe_prevista <= std_logic_vector(to_unsigned(v_classe,sng_knn_classe_prevista'length));
					--sng_knn_classe_prevista <= "1111111111111111";
				end if;
				
				sng_knn_ranquear_pronto <= '1';
				
				
			end if;
				

		end if;
		
	end process;
	
	/* MAQUINA DE ESTADOS DO K NEAREST NEIGHBORHOOD */
	--p_knn_maquina_de_estado	: process (sng_reset, sng_estado, CLOCK_50)
	--p_knn_maquina_de_estado	: process (sng_reset, sng_estado, CLOCK_50, KNN_RESET)
	p_knn_maquina_de_estado	: process (sng_reset, sng_estado, KNN_RESET, sng_knn_teste_pronto, sng_knn_calcular_distancia_pronto, sng_knn_ordenar_pronto, sng_knn_ranquear_pronto, CLOCK_50)
	--p_knn_maquina_de_estado	: process 
	variable int_espera	:integer :=0;
	begin
		
			
		if (sng_reset = '1') then
		
			sng_estado <= CARGA;
			sng_knn_calcular_distancia <= '0';
			sng_knn_ordenar <= '0';
			sng_knn_ranquear <= '0';
			sng_reset <= '0';
			
		else
			if KNN_RESET'event and KNN_RESET = '1' then
		
				sng_reset <= '1';
			
			end if;						
				
			if rising_edge(CLOCK_50) then

				case sng_estado is
					when CARGA =>
						
						sng_knn_calcular_distancia <= '0';
						sng_knn_ordenar <= '0';
						sng_knn_ranquear <= '0';
						
						sng_reset_p_knn_treinamento <= '0';
						sng_reset_p_knn_distancia_euclidiana <= '0';
						sng_reset_p_knn_ordenar <= '0';
						sng_reset_p_knn_proximos <= '0';
							
						if (sng_knn_teste_pronto'stable and sng_knn_teste_pronto = '1') then
							
							sng_knn_feito <= '0';	
							sng_estado <= CALCULAR;
							
						end if;
					
					when CALCULAR =>
					
						if (sng_knn_calcular_distancia_pronto'stable and sng_knn_calcular_distancia_pronto = '1') then
							
							sng_estado <= ORDENAR;
							
						else
							 
							sng_knn_calcular_distancia <= '1';
							
						end if;
						
					when ORDENAR =>
						
						if (sng_knn_ordenar_pronto'stable and sng_knn_ordenar_pronto = '1') then
						
							sng_estado <= RANQUEAR;
						
						else
							
							sng_knn_ordenar <= '1';
						
						end if;
					
					when RANQUEAR =>
					
						if (sng_knn_ranquear_pronto'stable and sng_knn_ranquear_pronto = '1') then
							
							sng_estado <= PRONTO;
						
						else
						
							sng_knn_ranquear <= '1';
							
						end if;
					
					when PRONTO =>

						sng_reset_p_knn_distancia_euclidiana <= '1';
						sng_reset_p_knn_ordenar <= '1';
						sng_reset_p_knn_proximos <= '1';
						sng_reset_p_knn_treinamento <= '1';
						
						sng_knn_feito <= '1';
						sng_estado <= CARGA;
					
				end case;
			
			end if;
			

			
			
		end if;
	
	end process p_knn_maquina_de_estado;

	KNN_CLASSE_PREVISTA <= sng_knn_classe_prevista;
	--KNN_CLASSE_PREVISTA_PRONTO <= sng_knn_feito when KNN_DEBUG_KEY0 = '1' else '1';	
	KNN_CLASSE_PREVISTA_PRONTO <= sng_knn_feito;
	
	--KNN_CLASSE_PREVISTA <= std_logic_vector(sng_distancia_euclidiana(to_integer(unsigned(KNN_DADOS_ATRIBUTO_N))).distancia);
	
--	KNN_CLASSE_PREVISTA <= std_logic_vector(vs_distancia_euclidiana_ordenada(to_integer(unsigned(KNN_DADOS_ATRIBUTO_N))).distancia);
	
	KNN_MAQUINA_ESTADO(4) <= '1' when (sng_estado = CARGA) else '0';
	KNN_MAQUINA_ESTADO(3) <= '1' when (sng_estado = CALCULAR) else '0';
	KNN_MAQUINA_ESTADO(2) <= '1' when (sng_estado = ORDENAR) else '0';
	KNN_MAQUINA_ESTADO(1) <= '1' when (sng_estado = RANQUEAR) else '0';
	KNN_MAQUINA_ESTADO(0) <= '1' when (sng_estado = PRONTO) else '0';

	KNN_DEBUG_SINAIS(0) <= sng_knn_feito;
	KNN_DEBUG_SINAIS(1) <= sng_reset;
	KNN_DEBUG_SINAIS(2) <= sng_reset_p_knn_distancia_euclidiana;
	KNN_DEBUG_SINAIS(3) <= sng_reset_p_knn_ordenar;
	KNN_DEBUG_SINAIS(4) <= sng_reset_p_knn_proximos;
	
	
--		LED_0 <= sng_knn_calcular_distancia_pronto;
--		LED_1 <= sng_knn_ordenar_pronto;
--		LED_2 <= sng_knn_ranquear_pronto;
		
	--KNN_CLASSE_PREVISTA <= sng_knn_classe_prevista;
	--KNN_CLASSE_PREVISTA <= "11111111";
	--KNN_CLASSE_PREVISTA <= std_logic_vector(sng_distancia_euclidiana_ordenada(to_integer(unsigned(KNN_DADOS_ATRIBUTO_N))).distancia)(7 downto 0);
	--KNN_CLASSE_PREVISTA_PRONTO <= '1' when sng_estado = PRONTO else '0';
	
	
		--KNN_CLASSE_PREVISTA <= kr_dados_treinamento(to_integer(unsigned(KNN_DADOS_ATRIBUTO_N)))(7 downto 0);
		
		--KNN_CLASSE_PREVISTA <= std_logic_vector(krs_registros_treinamento(to_integer(unsigned(KNN_DADOS_ATRIBUTO_N)))(7 downto 0));
		--KNN_CLASSE_PREVISTA <= krs_registros_treinamento(to_integer(unsigned(KNN_DADOS_ATRIBUTO_N)))(15)(7 downto 0);
		--KNN_CLASSE_PREVISTA <= kr_dados_teste(to_integer(unsigned(KNN_DADOS_ATRIBUTO_N)))(7 downto 0);
		--KNN_CLASSE_PREVISTA <= std_logic_vector(r_distancia_euclidiana(to_integer(unsigned(KNN_DADOS_ATRIBUTO_N))).distancia)(7 downto 0);
		

END ARCHITECTURE knn_a;
