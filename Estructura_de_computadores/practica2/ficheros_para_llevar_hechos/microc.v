module microc(output wire [5:0] Opcode, output wire z, input wire clk, reset, s_inc, s_inm, we3, wez, input wire [2:0] Op);
//Microcontrolador sin memoria de datos de un solo ciclo
  wire[9:0] salidaMUX, salidaSUM, salidaPC;
  wire[15:0] salidaMEM;
  wire[7:0] RD1, RD2, WD3;


  wire zeroALU;
  wire [7:0] salidaALU;

  sum sumador(salidaSUM, 10'b0000000001, salidaPC);

  registro #(10) PC(salidaPC, clk, reset, salidaMUX);

  mux2 #(10) multiplexor(salidaMUX, salidaMEM[9:0], salidaSUM, s_inc);

  memprog memoria(salidaMEM, clk, salidaPC);

  regfile registros(RD1, RD2, clk, we3, salidaMEM[11:08], salidaMEM[07:04], salidaMEM[03:00], WD3);

  alu ALU(salidaALU, zeroALU, RD1, RD2, Op);

  ffd flag(clk, reset, zeroALU, wez, z);

  mux2 #(8) multiplexor8(WD3, salidaALU, salidaMEM[11:04], s_inm);

  assign Opcode = salidaMEM[15:10];

endmodule