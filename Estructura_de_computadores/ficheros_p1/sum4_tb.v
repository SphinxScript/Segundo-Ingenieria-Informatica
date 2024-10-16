// Testbench para modulo semisumador visto antes

`timescale 1 ns / 10 ps //Directiva que fija la unidad de tiempo de simulaci�n y el paso de simulaci�n

module fa_v1_tb;
//declaracion de se�ales

reg test_a, test_b, test_cin; //las se�ales de entrada al semisumador. Se han declarado reg porque queremos inicializarlas
wire test_sum, test_carry; //se�ales de salida, se declaran como wire porque sus valores se fijan por el semisumador

//instancia del modulo a testear, con notaci�n de posiciones de argumentos 
sum4_v2 fa1(test_carry, test_sum, test_a, test_b, test_cin);


initial
begin


end

endmodule