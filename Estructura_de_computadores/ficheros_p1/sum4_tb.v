// Testbench para modulo semisumador visto antes

`timescale 1 ns / 10 ps //Directiva que fija la unidad de tiempo de simulaci�n y el paso de simulaci�n

module fa_v1_tb;
//declaracion de se�ales

reg[3:0] test_a, test_b; //las se�ales de entrada al semisumador. Se han declarado reg porque queremos inicializarlas
reg  test_cin;
wire[3:0] test_sum; //se�ales de salida, se declaran como wire porque sus valores se fijan por el semisumador
wire  test_carry;

//instancia del modulo a testear, con notaci�n de posiciones de argumentos 
sum4 fa1(test_sum, test_carry, test_a, test_b, test_cin);


initial
begin
  $monitor("tiempo=%0d a=%b b=%b c_in=%b suma=%b acarreo=%b", $time, test_a, test_b, test_cin, test_sum, test_carry);
  $dumpfile("sum4_tb.vcd");        //fichero de salida donde vuelca los datos
  $dumpvars;

  // vector de test 0
  test_a = 4'b0001;
  test_b = 4'b1101;
  test_cin = 1'b0;
  #20;

  test_a = 4'b0101;
  test_b = 4'b0101;
  test_cin = 1'b0;
  #20;

  test_a = 4'b1101;
  test_b = 4'b1101;
  test_cin = 1'b1;
  #20;

  test_a = 4'b0101;
  test_b = 4'b1100;
  test_cin = 1'b0;
  #20;

  test_a = 4'b1101;
  test_b = 4'b1111;
  test_cin = 1'b1;
  #20;

  $finish;
end

endmodule