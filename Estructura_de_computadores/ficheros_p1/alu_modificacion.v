module alu(output wire [3:0] R, output wire zero, carry, sign, input wire [3:0] A, B, input wire c_in, input wire [2:0] Op);

  wire [3:0] op1, op2;

  preprocess preprocesador(op1, op2, A, B, Op);

  sum4_ul4 modificacion(R, carry, op1, op2, c_in, Op[1:0], Op[2]);

  assign zero = (R == 4'b0000) ? 1 : 0;
  assign sign = R[3];

endmodule