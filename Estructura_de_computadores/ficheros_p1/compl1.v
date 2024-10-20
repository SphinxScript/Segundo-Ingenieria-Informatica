module compl1(output wire [3:0] Out, input wire [3:0] Inp, input wire cpl);

  always @(cpl, Inp)
  begin 
    assign {Out} = cpl ? ~Inp : Inp;
  end
endmodule