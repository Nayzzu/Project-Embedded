library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity gerbang is
    Port ( 
        A, B : in STD_LOGIC;
        Y1   : out STD_LOGIC;
        Y2   : out STD_LOGIC;
        Y3   : out STD_LOGIC
    );
end gerbang;

architecture Dataflow of gerbang is

    signal D1 : STD_LOGIC;
    signal D2 : STD_LOGIC;
    signal D3 : STD_LOGIC;

begin

    D1 <= A or B;
    D2 <= A and B;
    D3 <= A xor B;

    Y1 <= D1 xor D2;
    Y2 <= B xor D2;
    Y3 <= D1 xor D3;

end Dataflow;