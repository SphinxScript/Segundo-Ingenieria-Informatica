`timescale 1ns/1ps

module microc_tb;
    // declaracion de variables
    reg clk, reset;
    reg s_inc, s_inm, we3, wez;
    reg [2:0] Op;
    wire [5:0] Opcode;
    wire z;

    // Instancia del módulo microc a testear
    microc uut (Opcode, z, clk, reset, s_inc, s_inm, we3, wez, Op);

    // Reloj: 20 ns por ciclo (sube a los 10 ns, baja a los 20 ns)
    initial
    begin
        $dumpfile("microc_tb.vcd");
        $dumpvars;
        clk = 0;
        #10 clk = ~clk;
    end

    // Procedimiento de inicialización
    initial
      begin

        // Inicialización de señales
        reset = 1; s_inc = 0; s_inm = 0; we3 = 0; wez = 0; Op = 3'b000;

        // Inicio del programa: Reset activo durante los primeros 5 ns
        #5
        reset = 1;

        // Ciclo 1: `j Start`
        #5 
        s_inc = 0; we3 = 0; wez = 0; 
        
        #5
        s_inc = 0;                   

        // Ciclo 2: `nop`
        #10
        s_inc = 1;                   

        // Ciclo 3: `li #0 R2`
        #10
        s_inm = 1; we3 = 1;          

        // Ciclo 4: `li #2 R1`
        #10
        s_inm = 1; we3 = 1;          

        // Ciclo 5: `li #4 R3`
        #10
        s_inm = 1; we3 = 1;          

        // Ciclo 6: `li #1 R4`
        #10
        s_inm = 1; we3 = 1;          

        // Ciclo 7: `add R2 R3 R2`
        #10
        s_inm = 0; we3 = 1; wez = 1; 

        // Ciclo 8: `sub R1 R4 R1`
        #10
        s_inm = 0; we3 = 1; wez = 1; 

        // Ciclo 9: `jnz Iter`
        #10
        if (z == 0) s_inc = 0; else s_inc = 1; 

        // Ciclo 10-14: Repetir o finalizar (bucle `Fin`)
        #10
        s_inc = 1;                   

        // Terminar simulación
        #300
        $finish; 
    end
endmodule