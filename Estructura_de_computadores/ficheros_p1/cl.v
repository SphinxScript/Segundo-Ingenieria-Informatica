module cl(output wire out, input wire a, b, input wire [1:0] S);

  wire outa, outo, outx, outn; // Salidas de las puertas logicas

  and aa(outa, a, b);          // Operacion AND
  or  o(outo, a, b);           // Operacion OR
  xor x(outx, a, b);           // Operacion XOR
  not n(outn, a);              // Operacion NOT
  mux4_1  m(out, outa, outo, outx, outn, S); // Mux conectado a la salida del modulo

endmodule
