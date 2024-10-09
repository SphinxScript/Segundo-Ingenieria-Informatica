module cl(output wire out, input wire a, b, input wire [1:0] S);

  wire sa,so,sx,sn;

  and aa(outa, a, b);
  or  o(outo, a, b);
  xor x(outx, a, b);
  not n(outn, a);
  mux4_1  m(muxout, outa, outo, outx, outn, S);


endmodule