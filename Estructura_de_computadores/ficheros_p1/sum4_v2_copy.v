module sum4_v2(output wire[3:0] S, output wire c_out, input wire[3:0] A, input wire[3:0] B, input wire c_in);

  assign {S, c_out} = A + B + c_in;

endmodule