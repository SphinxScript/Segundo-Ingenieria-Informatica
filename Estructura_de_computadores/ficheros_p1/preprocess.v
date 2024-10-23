module preprocess(output wire [3:0] AMod, output wire [3:0] BMod, input wire [3:0] A, input wire [3:0] B, input wire [2:0] Op);

  wire [3:0] add1_out, op2_BOut;

  wire add1;
  assign add1 = Op[0];
  mux2_4 MuxAdd1(add1_out, 4'b0000, 4'b0001, add1);

  wire op1_a;
  assign op1_a = Op[2] | (Op[1] & ~Op[0]);
  mux2_4 Muxop1_A(AMod, add1_out, A, op1_a);

  wire op2_B;
  assign op2_B = Op[2] | (Op[1] & ~Op[0]);
  mux2_4 Muxop2_B(op2_BOut, A, B, op2_B);

  wire cpl;
  assign cpl = ~Op[2] & ~Op[1] & Op[0];
  compl1 complementador(BMod, op2_BOut, cpl);

endmodule