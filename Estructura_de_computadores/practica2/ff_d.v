module ffd (output reg q, input wire clk, reset, carga, d);

  // reset asíncrono, ya que es independiente del flanco del reloj
  always @(posedge clk, posedge reset)
  // --> cuando se de el flanco en clk o reset
    if (reset)
      q <= 1'b0; // asignación no bloqueante q = 0
    else
      if (carga)
        q <= d; // asignación no bloqueante q = d

endmodule


// <= es un operador de asignaion no bloqueante