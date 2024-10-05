//Sumador completo (full-adder) de tres entradas de 1 bit realizado a partir de puertas l�gicas 
module fa_v1(output wire sum, output wire c_out, input wire a, input wire b, input wire c_in);

  wire sum1, carry1, carry2;

  ha_v1 hal(sum1, carry1, a, b);
  ha_v1 ha2(sum, carry2, sum1, c_in);
  or    or1(c_out, carry1, carry2);

endmodule
