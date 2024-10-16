module sum4_v2(output wire[3:0] S, output wire c_out, input wire[3:0] A, input wire[3:0] B, input wire c_in);

  wire c1, c2, c3;
  assign {S[3], c_out} = A[3] + B[3] + c3;
  assign {S[2], c3} = A[2] + B[2] + c2;
  assign {S[1], c2} = A[1] + B[1] + c1;
  assign {S[0], c1} = A[0] + B[0] + c_in;

endmodule