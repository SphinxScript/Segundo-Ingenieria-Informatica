// Testbench para modulo semisumador visto antes

`timescale 1 ns / 10 ps //Directiva que fija la unidad de tiempo de simulaci�n y el paso de simulaci�n

module fa_v1_tb;
//declaracion de se�ales

reg test_a, test_b, test_cin; //las se�ales de entrada al semisumador. Se han declarado reg porque queremos inicializarlas
wire test_sum, test_carry; //se�ales de salida, se declaran como wire porque sus valores se fijan por el semisumador

//instancia del modulo a testear, con notaci�n de posiciones de argumentos 
fa_v1 fa1(test_sum, test_carry, test_a, test_b, test_cin);


initial
begin
  $monitor("tiempo=%0d a=%b b=%b c_in=%b suma=%b acarreo=%b", $time, test_a, test_b, test_cin, test_sum, test_carry);
  $dumpfile("fa_v1_tb.vcd");        //fichero de salida donde vuelca los datos
  $dumpvars;

  //vector de test 0
  test_a = 1'b0;
  test_b = 1'b0;
  test_cin = 1'b0;
  #20;

  //vector de test 1
  test_a = 1'b0;
  test_b = 1'b1;
  test_cin = 1'b0;
  #20;

  //vector de test 2
  test_a = 1'b1;
  test_b = 1'b0;
  test_cin = 1'b1;
  #20;
  //vector de test 3
  test_a = 1'b1;
  test_b = 1'b1;
  test_cin = 1'b1;
  #20;

  $finish;  //fin simulacion

end
endmodule

