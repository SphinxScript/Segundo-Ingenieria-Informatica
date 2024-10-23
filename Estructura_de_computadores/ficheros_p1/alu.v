module alu(output wire [3:0] R, output wire zero, carry, sign, input wire [3:0] A, B, input wire c_in, input wire [2:0] Op);

  wire[3:0] op1, op2, sum4_out, ul4_out;

  preprocess preprocesador(op1, op2, A, B, Op);

  sum4 sumador(sum4_out, carry, op1, op2, c_in);

  ul4 modulo_logico(ul4_out, op1, op2, Op[1:0]);

  mux2_4 selector(R, sum4_out, ul4_out, Op[2]);

  assign zero = (R == 4'b0000) ? 1 : 0;
  assign sign = R[3];

endmodule