// modificacion de la evaluación de la práctica

module sum4_ul4(output reg[3:0] Out, output reg c_out, input wire[3:0] OP1, input wire[3:0] OP2, input wire c_in, input wire [1:0] S, input wire L);

  always @*
    begin
      if (L == 0)
        {c_out, Out} = OP1 + OP2 + c_in;
      else
        case(S)
          2'b00     : Out = OP1 & OP2;
          2'b01     : Out = OP1 | OP2;
          2'b10     : Out = OP1 ^ OP2;
          2'b11     : Out = ~OP1;
          default   : Out = 4'bxxxx;
        endcase
    end

endmodule